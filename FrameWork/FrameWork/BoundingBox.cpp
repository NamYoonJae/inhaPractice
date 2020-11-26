#include "stdafx.h"
#include "SkinnedMesh.h"
#include "BoundingBox.h"


cBoundingBox::cBoundingBox()
	:m_vPivot(0, 0, 0)
	,m_vOriCenter(0, 0, 0)
	,m_vCenterPos(0, 0, 0)
	,m_Color(D3DCOLOR_XRGB(0, 255, 0))
{
	D3DXMatrixIdentity(&m_matWorldTM);
}


cBoundingBox::~cBoundingBox()
{
}

void cBoundingBox::Setup(LPD3DXMESH pMesh)
{
	D3DXVECTOR3 vMin(0, 0, 0), vMax(0, 0, 0);
	LPVOID pV = NULL;
	DWORD NumVertices = pMesh->GetNumVertices();

	pMesh->LockVertexBuffer(0, &pV);
	
	D3DXComputeBoundingBox((D3DXVECTOR3*)pV,
							NumVertices,
							D3DXGetFVFVertexSize(pMesh->GetFVF()),
							&vMin,
							&vMax);

	pMesh->UnlockVertexBuffer();
	
	m_vOriCenter = (vMin + vMax) / 2.0f;
	m_vOriCenter += m_vPivot;
	m_vOriAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;
}

void cBoundingBox::Setup(cSkinnedMesh* pSkinnedMesh)
{
	D3DXVECTOR3 vMin(0, 0, 0), vMax(0, 0, 0);
	
	vMin = pSkinnedMesh->GetMin();
	vMax = pSkinnedMesh->GetMax();

	m_vOriCenter = (vMin + vMax) / 2.0f;
	m_vOriAxisDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriAxisDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriAxisDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;
}

void cBoundingBox::Update(D3DXMATRIXA16* pmatWorld)
{
	if (pmatWorld)
	{
		m_matWorldTM = *pmatWorld;
	}

	for (int i = 0; i < 3; ++i)
	{
		D3DXVec3TransformNormal(&m_vAxisDir[i], &m_vOriAxisDir[i], &m_matWorldTM);
	}
	
	D3DXVec3TransformCoord(&m_vCenterPos, &m_vOriCenter, &m_matWorldTM);
}

void cBoundingBox::Render()
{
	vector<ST_PC_VERTEX> vecVertices;
	ST_PC_VERTEX v[8];
	float x(0), y(0), z(0);
	
	x = m_fAxisHalfLen[0];
	y = m_fAxisHalfLen[1];
	z = m_fAxisHalfLen[2];

	v[0].p = D3DXVECTOR3(-x, -y, -z);
	v[1].p = D3DXVECTOR3(+x, -y, -z);
	v[2].p = D3DXVECTOR3(+x, +y, -z);
	v[3].p = D3DXVECTOR3(-x, +y, -z);

	v[4].p = D3DXVECTOR3(-x, -y, +z);
	v[5].p = D3DXVECTOR3(+x, -y, +z);
	v[6].p = D3DXVECTOR3(+x, +y, +z);
	v[7].p = D3DXVECTOR3(-x, +y, +z);

	for (int i = 0; i < 8; i++)
	{
		v[i].c = m_Color;
		v[i].p += m_vOriCenter;
		D3DXVec3TransformCoord(&v[i].p, &v[i].p, &m_matWorldTM);
	}

	vecVertices.push_back(v[0]); vecVertices.push_back(v[1]);
	vecVertices.push_back(v[1]); vecVertices.push_back(v[2]);
	vecVertices.push_back(v[2]); vecVertices.push_back(v[3]);
	vecVertices.push_back(v[0]); vecVertices.push_back(v[3]);

	vecVertices.push_back(v[1]); vecVertices.push_back(v[5]);
	vecVertices.push_back(v[5]); vecVertices.push_back(v[4]);
	vecVertices.push_back(v[0]); vecVertices.push_back(v[4]);

	vecVertices.push_back(v[5]); vecVertices.push_back(v[6]);
	vecVertices.push_back(v[2]); vecVertices.push_back(v[6]);

	vecVertices.push_back(v[3]); vecVertices.push_back(v[7]);
	vecVertices.push_back(v[4]); vecVertices.push_back(v[7]);

	vecVertices.push_back(v[7]); vecVertices.push_back(v[6]);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
									vecVertices.size() / 2, 
									&vecVertices[0],
									sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

bool cBoundingBox::IsCollision(cBoundingBox* pOBB1, cBoundingBox* pOBB2)
{
	float cos[3][3];
	float absCos[3][3];
	float dist[3];
	float r0, r1, r;
	const float cutoff = 0.999999f;
	bool existsParallelPair = false;

	D3DXVECTOR3 D = pOBB2->m_vCenterPos - pOBB1->m_vCenterPos;

	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			cos[a][b] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &pOBB2->m_vAxisDir[b]);

			absCos[a][b] = abs(cos[a][b]);

			if (absCos[a][b] > cutoff)
				existsParallelPair = true;
		}


		dist[a] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &D);
		r = abs(dist[a]);
		r0 = pOBB1->m_fAxisHalfLen[a];
		r1 = pOBB2->m_fAxisHalfLen[0] * absCos[a][0] +
			pOBB2->m_fAxisHalfLen[1] * absCos[a][1] +
			pOBB2->m_fAxisHalfLen[2] * absCos[a][2];

		if (r > r0 + r1)   return false;
	}

	for (int b = 0; b < 3; b++)
	{
		r = abs(D3DXVec3Dot(&pOBB2->m_vAxisDir[b], &D));
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[0][b] +
			pOBB1->m_fAxisHalfLen[1] * absCos[1][b] +
			pOBB1->m_fAxisHalfLen[2] * absCos[2][b];

		r1 = pOBB2->m_fAxisHalfLen[b];

		if (r > r0 + r1)   return false;
	}


	if (existsParallelPair) return true;

	/////////////////////////////////////////////////////////////////
	{
		// : 0
		r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][0] + pOBB1->m_fAxisHalfLen[2] * absCos[0][0];
		r1 = pOBB2->m_fAxisHalfLen[1] * absCos[1][2] + pOBB2->m_fAxisHalfLen[2] * absCos[1][1];
		if (r > r0 + r1)   return false;

		r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][1] + pOBB1->m_fAxisHalfLen[2] * absCos[0][1];
		r1 = pOBB2->m_fAxisHalfLen[0] * absCos[1][2] + pOBB2->m_fAxisHalfLen[2] * absCos[1][0];
		if (r > r0 + r1)   return false;

		r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[0][2];
		r1 = pOBB2->m_fAxisHalfLen[0] * absCos[1][1] + pOBB2->m_fAxisHalfLen[1] * absCos[1][0];
		if (r > r0 + r1)
			return false;

		/////////////////////////////////////////////////////////////////    
		// : 1 
		r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][0] + pOBB1->m_fAxisHalfLen[1] * absCos[0][0];
		r1 = pOBB2->m_fAxisHalfLen[1] * absCos[2][2] + pOBB2->m_fAxisHalfLen[2] * absCos[2][1];
		if (r > r0 + r1)   return false;

		r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][1] + pOBB1->m_fAxisHalfLen[1] * absCos[0][1];
		r1 = pOBB2->m_fAxisHalfLen[0] * absCos[2][2] + pOBB2->m_fAxisHalfLen[2] * absCos[2][0];
		if (r > r0 + r1)   return false;

		r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][2] + pOBB1->m_fAxisHalfLen[1] * absCos[0][2];
		r1 = pOBB2->m_fAxisHalfLen[0] * absCos[2][1] + pOBB2->m_fAxisHalfLen[1] * absCos[2][0];
		if (r > r0 + r1)   return false;

		/////////////////////////////////////////////////////////////////
		// : 2 
		r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
		r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][0] + pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
		r1 = pOBB2->m_fAxisHalfLen[1] * absCos[0][2] + pOBB2->m_fAxisHalfLen[2] * absCos[0][1];
		if (r > r0 + r1)   return false;

		r = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
		r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][1] + pOBB1->m_fAxisHalfLen[2] * absCos[1][1];
		r1 = pOBB2->m_fAxisHalfLen[0] * absCos[0][2] + pOBB2->m_fAxisHalfLen[2] * absCos[0][0];
		if (r > r0 + r1)   return false;

		r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
		r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[1][2];
		r1 = pOBB2->m_fAxisHalfLen[0] * absCos[0][1] + pOBB2->m_fAxisHalfLen[1] * absCos[0][0];
		if (r > r0 + r1)   return false;
	} // << : 

	return true;
}