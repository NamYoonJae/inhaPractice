#include "stdafx.h"
#include "Shadow.h"
#include "cOBB.h"

cShadow::cShadow()
	: m_pMesh(NULL)
	, m_pTexcoord(NULL)
{
}

cShadow::~cShadow()
{
}

void cShadow::Setup()
{
	m_vPos = D3DXVECTOR3(0, 0, 0);
	m_vScale = D3DXVECTOR3(0.3, 0.001, 0.3);

	{
		using namespace std;
		string szFullPathX = "data/XFile/Cylinder/Cylinder.x";

		HRESULT hr = 0;
		ID3DXBuffer* adjBuffer = 0;
		ID3DXBuffer* mtrlBuffer = 0;
		DWORD numMtrls = 0;

		hr = D3DXLoadMeshFromXA(
			szFullPathX.c_str(),
			D3DXMESH_MANAGED,
			g_pD3DDevice,
			&adjBuffer,
			&mtrlBuffer,
			0,
			&numMtrls,
			&m_pMesh);

		if (FAILED(hr))
			return;

		if (mtrlBuffer != 0 && numMtrls != 0)
		{
			D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

			for (int i = 0; i < numMtrls; i++)
			{
				mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
				m_vecMtl.push_back(mtrls[i].MatD3D);
			}


		}
		SafeRelease(mtrlBuffer);
	}

	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFileA("data/Texture/shadow.png", &info);

	D3DXCreateTextureFromFileExA
	(g_pD3DDevice, "data/Texture/shadow.png",
		info.Width, info.Height, 1, 0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		NULL,
		NULL,
		&m_pTexcoord);
}

void cShadow::Update()
{
}

void cShadow::Render(D3DXMATRIXA16* pmat)
{
	D3DXMATRIXA16 matWorld, matS, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);

	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matWorld = matS * matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetTexture(0, m_pTexcoord);

	for (int i = 0; i < m_vecMtl.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtl[i]);
		m_pMesh->DrawSubset(0);
	}
}
