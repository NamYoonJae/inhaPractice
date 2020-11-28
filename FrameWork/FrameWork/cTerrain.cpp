#include "stdafx.h"
#include "cTerrain.h"
#include "basic.h"
cTerrain::cTerrain()
	: m_pTexture(NULL)
	, m_pTerrainMesh(NULL)
	, m_nTile(0)
	, TerrainThread(NULL)
	, m_pNewTerrainMesh(NULL)
	, IsSwapMesh(false)
	, m_pvTarget(NULL)
{
	m_CullingRect = { 0,0,0,0 };
}


cTerrain::~cTerrain()
{
	if (TerrainThread && TerrainThread->joinable())
	{
		TerrainThread->join();
	}
	SafeDelete(TerrainThread);

	SafeRelease(m_pTerrainMesh);
	SafeRelease(m_pNewTerrainMesh);
	SafeRelease(m_pTexture);
}

void cTerrain::Update()
{
	if (m_pvTarget == NULL) return;

	//if(*m_pvTarget != m_vOldPos)
	//{
	//	callThread();	
	//}

	float h = getHeight(*m_pvTarget);
	m_pvTarget->y = h;
}

void cTerrain::Render(D3DXMATRIXA16 * pmat)
{
	//if (SwapMesh())
	//{
	//	if (m_pTerrainMesh != NULL)
	//		SafeRelease(m_pTerrainMesh);

	//	if (m_pNewTerrainMesh)
	//	{
	//		m_pNewTerrainMesh->CloneMeshFVF(0, ST_PNT_VERTEX::FVF, g_pD3DDevice, &m_pTerrainMesh);

	//		SafeRelease(m_pNewTerrainMesh);
	//	}

	//}
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	if (m_pTerrainMesh)
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		g_pD3DDevice->SetTexture(0, m_pTexture);
		g_pD3DDevice->SetMaterial(&m_stMtl);
		m_pTerrainMesh->DrawSubset(0);

		g_pD3DDevice->SetTexture(0, NULL);
	}
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

void cTerrain::NewTerrain(D3DXVECTOR3 vec)
{
	EnterCriticalSection(&cs);

	if (!vecIndex.empty())
		vecIndex.clear();
	if (!vecVertex.empty())
		vecVertex.clear();

	float x = ((float)(m_nTile) / 2.0f) + vec.x;
	float z = ((float)(m_nTile) / 2.0f) - vec.z;

	float col = ::floorf(x);
	float row = ::floorf(z);

	if (col < 0 || col > m_nTile || row < 0 || row > m_nTile)
	{

		LeaveCriticalSection(&cs);
		return;
	}
	RECT InPlayArea = { 0,0,0,0 };


	InPlayArea.left = col - CullingSize < 0 ? 0 : col - CullingSize;
	InPlayArea.top = row - CullingSize < 0 ? 0 : row - CullingSize;
	InPlayArea.right = col + CullingSize > m_nTile ? m_nTile : col + CullingSize;
	InPlayArea.bottom = row + CullingSize > m_nTile ? m_nTile : row + CullingSize;


	for (int y = InPlayArea.top; y <= InPlayArea.bottom; y++)
	{
		for (int x = InPlayArea.left; x <= InPlayArea.right; x++)
		{
			vecVertex.push_back(m_vecMapVertex[x + y * (m_nTile + 1)]);

		}
	}


	// Index Buffer
	for (int y = 0; y < (InPlayArea.bottom - InPlayArea.top); ++y)
	{
		for (int x = 0; x < (InPlayArea.right - InPlayArea.left); ++x)
		{
			int v0 = (x + 0) + (y + 0) * (InPlayArea.right - InPlayArea.left + 1);
			int v1 = (x + 1) + (y + 0) * (InPlayArea.right - InPlayArea.left + 1);
			int v2 = (x + 1) + (y + 1) * (InPlayArea.right - InPlayArea.left + 1);
			int v3 = (x + 0) + (y + 1) * (InPlayArea.right - InPlayArea.left + 1);

			vecIndex.push_back(v1);
			vecIndex.push_back(v3);
			vecIndex.push_back(v0);

			vecIndex.push_back(v1);
			vecIndex.push_back(v2);
			vecIndex.push_back(v3);
		}

	}

	RECT rc = { vec.x - CullingSize,vec.z - CullingSize
		,vec.x + CullingSize,vec.z + CullingSize };
	m_CullingRect = rc;
	IsSwapMesh = true;
	LeaveCriticalSection(&cs);
}

float cTerrain::getHeight(D3DXVECTOR3 vec)
{
	float x = ((float)(m_nTile) / 2.0f) + vec.x;
	float z = ((float)(m_nTile) / 2.0f) - vec.z;

	float col = ::floorf(x);
	float row = ::floorf(z);

	if (col >= (m_nTile) || row >= (m_nTile))
		return 0.0f;

	float A = getHeightMapEntry(row + 0, col + 0);
	float B = getHeightMapEntry(row + 0, col + 1);
	float C = getHeightMapEntry(row + 1, col + 0);
	float D = getHeightMapEntry(row + 1, col + 1);

	float dx = x - col;
	float dz = z - row;

	float height = 0.0f;
	if (dz < 1.0 - dx)
	{
		float uy = B - A;
		float vy = C - A;
		height = A + LerpPosition(0.0f, uy, dx)
			+ LerpPosition(0.0f, vy, dz);
	}
	else
	{
		float uy = C - D;
		float vy = B - D;
		height = D + LerpPosition(0.0f, uy, 1.0f - dx)
			+ LerpPosition(0.0f, vy, 1.0f - dz);
	}
	return height;

}

void cTerrain::Setup(std::string strFolder, std::string strTex,
	std::string strRaw, DWORD dwBytesPerPixel, float MaxHeight)
{
	CreateMaxSizeMeshMap(strFolder, strTex, strRaw, dwBytesPerPixel, MaxHeight);
	return;
	using namespace std;
	string strTexPath = strFolder + string("/") + strTex;
	string strRawPath = strFolder + string("/") + strRaw;


	D3DXCreateTextureFromFileA(g_pD3DDevice, strTexPath.c_str(), &m_pTexture);

	FILE* fpRaw;
	fopen_s(&fpRaw, strRawPath.c_str(), "rb");

	fseek(fpRaw, 0, SEEK_END);
	int nFileLength = ftell(fpRaw);
	fseek(fpRaw, 0, SEEK_SET);

	int nNumVertex = nFileLength / dwBytesPerPixel;
	int nRow = (int)(sqrt(float(nNumVertex) + 0.001f));
	int nCol = nRow;
	int nTile = nRow - 1;

	m_nTile = nTile;

	// 0 255 -> 255 = MaxHeight;


	ST_PNT_VERTEX v;

	for (int i = 0; i <= m_nTile; i++)
	{
		for (int j = 0; j <= m_nTile; j++)
		{
			int k = (m_nTile + 1) * i + j;
			v.t = D3DXVECTOR2((float)j / m_nTile, (float)i / m_nTile);
			v.p.y = (unsigned char)fgetc(fpRaw) / 255.0f * MaxHeight;
			v.p.x = -m_nTile * 0.5 + j;
			v.p.z = +m_nTile * 0.5 - i;
			v.n = D3DXVECTOR3(0, 1, 0);
			m_vecMapVertex.push_back(v);
		}
	}


	fclose(fpRaw);

	for (int z = 1; z < nTile; ++z)
	{
		for (int x = 1; x < nTile; ++x)
		{
			int k = (m_nTile)* z + x;

			D3DXVECTOR3 v0, v1, vCross;

			v0 = m_vecMapVertex[k - (m_nTile + 1)].p - m_vecMapVertex[k + (m_nTile + 1)].p;
			v1 = m_vecMapVertex[k - 1].p - m_vecMapVertex[k + 1].p;

			D3DXVec3Cross(&vCross, &v0, &v1);
			D3DXVec3Normalize(&vCross, &vCross);
			m_vecMapVertex[k].n = vCross;
		}
	}

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	InitializeCriticalSection(&cs);
	m_vOldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	
}


bool cTerrain::SwapMesh()
{
	if (IsSwapMesh)
	{
		if (vecIndex.size() == 0 || vecVertex.size() == 0)
		{
			return false;
		}

		D3DXCreateMeshFVF(vecIndex.size() / 3,
			vecVertex.size(),
			D3DXMESH_MANAGED | D3DXMESH_32BIT,
			ST_PNT_VERTEX::FVF,
			g_pD3DDevice,
			&m_pNewTerrainMesh);

		ST_PNT_VERTEX *pV = NULL;
		m_pNewTerrainMesh->LockVertexBuffer(0, (LPVOID*)&pV);
		memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
		m_pNewTerrainMesh->UnlockVertexBuffer();

		DWORD *pI = NULL;
		m_pNewTerrainMesh->LockIndexBuffer(0, (LPVOID*)&pI);
		memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
		m_pNewTerrainMesh->UnlockIndexBuffer();

		DWORD *pA = NULL;

		m_pNewTerrainMesh->LockAttributeBuffer(0, &pA);
		ZeroMemory(pA, (vecIndex.size() / 3) * sizeof(DWORD));
		m_pNewTerrainMesh->UnlockAttributeBuffer();

		std::vector<DWORD> vecAdj;
		vecAdj.resize(vecIndex.size());

		m_pNewTerrainMesh->GenerateAdjacency(0.001f, &vecAdj[0]);
		m_pNewTerrainMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT |
			D3DXMESHOPT_COMPACT |
			D3DXMESHOPT_VERTEXCACHE,
			&vecAdj[0],
			0, 0, 0);

		IsSwapMesh = false;
		return true;
	}

	return false;
}

void cTerrain::callThread()
{
	if (TerrainThread == NULL)
	{
		float distance = sqrt(pow(m_pvTarget->x - m_vOldPos.x, 2) +
			pow(m_pvTarget->y - m_vOldPos.y, 2) + pow(m_pvTarget->z - m_vOldPos.z, 2));

		if (distance > 10.0f || m_pTerrainMesh == NULL)
		{
			m_vOldPos = *m_pvTarget;
			TerrainThread = new std::thread([&]() {NewTerrain(*m_pvTarget); });
		}
	}
	else
	{
		if (TerrainThread->joinable())
		{
			TerrainThread->join();
			//TerrainThread = NULL;
		}
		SafeDelete(TerrainThread);

	}
}

RECT cTerrain::GetCullingRect()
{
	RECT rc = m_CullingRect;
	return rc;
}

float cTerrain::LerpPosition(float a, float b, float t)
{
	return a - (a *t) + (b * t);
}

void cTerrain::CreateMaxSizeMeshMap(std::string strFolder, std::string strTex,
	std::string strRaw, DWORD dwBytesPerPixel, float MaxHeight)
{
	if (m_pTerrainMesh)
		SafeRelease(m_pTerrainMesh);

	using namespace std;
	string strTexPath = strFolder + string("/") + strTex;
	string strRawPath = strFolder + string("/") + strRaw;


	D3DXCreateTextureFromFileA(g_pD3DDevice, strTexPath.c_str(), &m_pTexture);

	FILE* fpRaw;
	fopen_s(&fpRaw, strRawPath.c_str(), "rb");

	fseek(fpRaw, 0, SEEK_END);
	int nFileLength = ftell(fpRaw);
	fseek(fpRaw, 0, SEEK_SET);

	int nNumVertex = nFileLength / dwBytesPerPixel;
	int nRow = (int)(sqrt(float(nNumVertex) + 0.001f));
	int nCol = nRow;
	int nTile = nRow - 1;

	m_nTile = nTile;


	ST_PNT_VERTEX v;

	for (int i = 0; i <= m_nTile; i++)
	{
		for (int j = 0; j <= m_nTile; j++)
		{
			int k = (m_nTile + 1) * i + j;
			v.t = D3DXVECTOR2((float)j / m_nTile, (float)i / m_nTile);
			v.p.y = (unsigned char)fgetc(fpRaw) / 255.0f * MaxHeight;
			v.p.x = -m_nTile * 0.5 + j;
			v.p.z = +m_nTile * 0.5 - i;
			v.n = D3DXVECTOR3(0, 1, 0);
			m_vecMapVertex.push_back(v);
		}
	}


	fclose(fpRaw);

	for (int z = 1; z < nTile; ++z)
	{
		for (int x = 1; x < nTile; ++x)
		{
			int k = (m_nTile)* z + x;

			D3DXVECTOR3 v0, v1, vCross;

			v0 = m_vecMapVertex[k - (m_nTile + 1)].p - m_vecMapVertex[k + (m_nTile + 1)].p;
			v1 = m_vecMapVertex[k - 1].p - m_vecMapVertex[k + 1].p;

			D3DXVec3Cross(&vCross, &v0, &v1);
			D3DXVec3Normalize(&vCross, &vCross);
			m_vecMapVertex[k].n = vCross;
		}
	}


	
	vector<DWORD> vecIndex;
	for(int y = 0; y < m_nTile; ++y)
		for(int x =0; x < m_nTile; ++x)
		{
			int v0 = (x + 0) + (y + 0) * (m_nTile + 1);
			int v1 = (x + 1) + (y + 0) * (m_nTile + 1);
			int v2 = (x + 1) + (y + 1) * (m_nTile + 1);
			int v3 = (x + 0) + (y + 1) * (m_nTile + 1);

			vecIndex.push_back(v1);
			vecIndex.push_back(v3);
			vecIndex.push_back(v0);

			vecIndex.push_back(v1);
			vecIndex.push_back(v2);
			vecIndex.push_back(v3);
		}
	D3DXCreateMeshFVF(vecIndex.size() / 3,
		m_vecMapVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pTerrainMesh);

	ST_PNT_VERTEX *pV = NULL;

	m_pTerrainMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &m_vecMapVertex[0], m_vecMapVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pTerrainMesh->UnlockVertexBuffer();

	DWORD *pI = NULL;
	m_pTerrainMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	m_pTerrainMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pTerrainMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA,(vecIndex.size()/3) * sizeof(DWORD));
	m_pTerrainMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdj(m_vecMapVertex.size());
	vecAdj.resize(vecIndex.size());
	m_pTerrainMesh->GenerateAdjacency(0.0001f, &vecAdj[0]);

	m_pTerrainMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0], 0, 0, 0);

	m_CullingRect = { 0,0,3000,3000 };

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
}
