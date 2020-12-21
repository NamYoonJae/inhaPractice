#include "stdafx.h"
#include "cOBB.h"
//#include "cSkinnedMesh.h"
#include "SkinnedMesh.h"

cOBB::cOBB()
{
}


cOBB::~cOBB()
{
}

void cOBB::Setup(cSkinnedMesh* pSkinnedMesh,D3DXMATRIXA16* pmat)
{
	D3DXVECTOR3 vMin = pSkinnedMesh->GetMin();
	D3DXVECTOR3 vMax = pSkinnedMesh->GetMax();

	if(pmat)
	{
		D3DXVec3TransformCoord(&vMin, &vMin, pmat);
		D3DXVec3TransformCoord(&vMax, &vMax, pmat);
	}

	m_vOriCenterPos = (vMin + vMax) / 2.0f;
	m_vOriAXidsDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriAXidsDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriAXidsDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x); 
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);
	
	BuildVertices();
}

void cOBB::Setup(D3DXVECTOR3 vmin, D3DXVECTOR3 vmax, D3DXMATRIXA16* pmat)
{
	D3DXVECTOR3 vMin = vmin;
	D3DXVECTOR3 vMax = vmax;
	
	if (pmat)
	{
		D3DXVec3TransformCoord(&vMin, &vMin, pmat);
		D3DXVec3TransformCoord(&vMax, &vMax, pmat);
	}

	m_vOriCenterPos = (vMin + vMax) / 2.0f;
	m_vOriAXidsDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOriAXidsDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOriAXidsDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	BuildVertices();
}

void cOBB::Setup(D3DXFRAME* pFrame, D3DXMESHCONTAINER* pMesh, D3DXMATRIXA16* pmat)
{
	D3DXVECTOR3 vMin(0, 0, 0);
	D3DXVECTOR3 vMax(0, 0, 0);

	DWORD BoneNum = -1;
	if (pFrame->Name)
	{
		ID3DXSkinInfo* pSkin = pMesh->pSkinInfo;

		for (DWORD i = 0; i < pSkin->GetNumBones(); i++)
		{
			if (!strcmp(pSkin->GetBoneName(i), pFrame->Name))
			{
				BoneNum = i;
				break;
			}
		}


		if (BoneNum != -1)
		{
			DWORD NumVertice = pSkin->GetNumBoneInfluences(BoneNum);

			if (NumVertice)
			{
				DWORD* Vertices = new DWORD[NumVertice];
				float* Weights = new float[NumVertice];
				pSkin->GetBoneInfluence(BoneNum, Vertices, Weights);

				DWORD Stride = D3DXGetFVFVertexSize(pMesh->MeshData.pMesh->GetFVF());

				D3DXMATRIX* matInvBone = pSkin->GetBoneOffsetMatrix(BoneNum);

				char* pVertices;
				pMesh->MeshData.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);

				for (DWORD i = 0; i < NumVertice; i++)
				{
					D3DXVECTOR3* vecPtr = (D3DXVECTOR3*)(pVertices + Vertices[i] * Stride);

					D3DXVECTOR3 vecPos;
					D3DXVec3TransformCoord(&vecPos, vecPtr, matInvBone);

					vMin.x = min(vMin.x, vecPos.x);
					vMin.y = min(vMin.y, vecPos.y);
					vMin.z = min(vMin.z, vecPos.z);

					vMax.x = max(vMax.x, vecPos.x);
					vMax.y = max(vMax.y, vecPos.y);
					vMax.z = max(vMax.z, vecPos.z);
				}

				pMesh->MeshData.pMesh->UnlockVertexBuffer();

				delete[] Vertices;
				delete[] Weights;
			}
		}
	}

	Setup(vMin, vMax, pmat);
}

void cOBB::BuildVertices()
{
	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2;

	D3DXMatrixIdentity(&m_matWorldTM);
	
	list.resize(8);

	for (int i = 0; i < 8; i++)
		list[i] = m_vOriCenterPos;

	list[0].x -= m_fAxisHalfLen[0], list[0].y -= m_fAxisHalfLen[1], list[0].z -= m_fAxisHalfLen[2];

	list[1].x -= m_fAxisHalfLen[0], list[1].y += m_fAxisHalfLen[1], list[1].z -= m_fAxisHalfLen[2];

	list[2].x += m_fAxisHalfLen[0], list[2].y += m_fAxisHalfLen[1], list[2].z -= m_fAxisHalfLen[2];

	list[3].x += m_fAxisHalfLen[0], list[3].y -= m_fAxisHalfLen[1], list[3].z -= m_fAxisHalfLen[2];

	list[4].x -= m_fAxisHalfLen[0], list[4].y -= m_fAxisHalfLen[1], list[4].z += m_fAxisHalfLen[2];

	list[5].x -= m_fAxisHalfLen[0], list[5].y += m_fAxisHalfLen[1], list[5].z += m_fAxisHalfLen[2];

	list[6].x += m_fAxisHalfLen[0], list[6].y += m_fAxisHalfLen[1], list[6].z += m_fAxisHalfLen[2];

	list[7].x += m_fAxisHalfLen[0], list[7].y -= m_fAxisHalfLen[1], list[7].z += m_fAxisHalfLen[2];

	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(255, 255, 255);

	v.p = list[0];	m_vecVertex.push_back(v);

	v.p = list[1];	m_vecVertex.push_back(v);

	v.p = list[1];	m_vecVertex.push_back(v);

	v.p = list[2];	m_vecVertex.push_back(v);


	v.p = list[2];	m_vecVertex.push_back(v);

	v.p = list[3];	m_vecVertex.push_back(v);

	v.p = list[3];	m_vecVertex.push_back(v);

	v.p = list[0];	m_vecVertex.push_back(v);

	v.p = list[4];	m_vecVertex.push_back(v);

	v.p = list[5];	m_vecVertex.push_back(v);

	v.p = list[5];	m_vecVertex.push_back(v);

	v.p = list[6];	m_vecVertex.push_back(v);

	v.p = list[6];	m_vecVertex.push_back(v);

	v.p = list[7];	m_vecVertex.push_back(v);

	v.p = list[7];	m_vecVertex.push_back(v);

	v.p = list[4];	m_vecVertex.push_back(v);

	v.p = list[0];	m_vecVertex.push_back(v);

	v.p = list[4];	m_vecVertex.push_back(v);

	v.p = list[1];	m_vecVertex.push_back(v);

	v.p = list[5];	m_vecVertex.push_back(v);

	v.p = list[2];	m_vecVertex.push_back(v);

	v.p = list[6];	m_vecVertex.push_back(v);

	v.p = list[3];	m_vecVertex.push_back(v);

	v.p = list[7];	m_vecVertex.push_back(v);
}

void cOBB::Update(D3DXMATRIXA16* pmatWorld)
{
	if(pmatWorld)
	{
		m_matWorldTM = *pmatWorld;
		
	}
	
	for(int i = 0; i < 3; i++)
	{
		D3DXVec3TransformNormal(&m_vAxisDir[i], &m_vOriAXidsDir[i],
			&m_matWorldTM);
	}

	D3DXVec3TransformCoord(&m_vCenterPos, &m_vOriCenterPos, 
		&m_matWorldTM);

}

bool cOBB::IsCollision(cOBB* pOBB1, cOBB* pOBB2)
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


void cOBB::OBBBOX_Render(D3DXCOLOR c)
{
	if (EventManager->m_IsOBBButten == false)
		return;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, NULL);
	for (int i = 0; i < m_vecVertex.size(); i++)
		m_vecVertex[i].c = c;

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	//if(!m_vecDrawingVertex.empty())
	//{
	//	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
	//	m_vecDrawingVertex.size() / 2, &m_vecDrawingVertex[0], sizeof(ST_PC_VERTEX));
	//}
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

