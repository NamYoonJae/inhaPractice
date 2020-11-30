#include "stdafx.h"
#include "SkinnedMesh.h"
#include "TimerManager.h"
#include "BoundingBox.h"
#include "basic.h"
#include  "cOBB.h"
#include "Arthur.h"


cArthur::cArthur()
	:m_vScale(1, 1, 1)
	,m_fvelocity(0.f)
	,m_isMoving(false)
{
}


cArthur::~cArthur()
{
	SafeDelete(m_pMesh);
}

void cArthur::Setup(char* szFolder, char* szFile)
{
	cSkinnedMesh::Setup(szFolder, szFile);
	SetAnimationIndex(0);
	m_vPos = D3DXVECTOR3(20, 0, 30);
	
	D3DXMATRIXA16 mat;
	D3DXMatrixScaling(&mat, 0.1, 0.1, 0.1);

	cSkinnedMesh::Update();
	
	m_pWeapon = new cArthurWeapon;
	m_pWeapon->Setup(D3DXFrameFind(m_pRoot, "weapon_sub"), 
		D3DXFrameFind(m_pRoot, "omniknight")->pMeshContainer, &mat);
	
	if (this->m_pCurrentBoneMatrices)
		mat *= *this->m_pCurrentBoneMatrices;
	m_pOBB = new cOBB;
	m_pOBB->Setup(this, &mat);


	EventManager->Attach(this);
}

void cArthur::Update()
{
	D3DXMatrixScaling(&m_matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationY(&m_matRot, m_vRot.y);
	D3DXMatrixTranslation(&m_matTranse, m_vPos.x, m_vPos.y, m_vPos.z);
	
	m_matWorld = m_matScale * m_matRot * m_matTranse;
	m_matWorldTM = m_matWorld;

	if(m_fvelocity != 0 && !m_isMoving)
	{
		SetAnimationIndexBlend(2);
		m_isMoving = true;
	}
	else if(m_fvelocity == 0 && m_isMoving)
	{
		m_isMoving = false;
		SetAnimationIndexBlend(0);
	}

	if (m_isAnimBlend)
	{
		m_fPassedBlendTime += g_pTimeManager->GetElapsedTime();
		if (m_fPassedBlendTime >= m_fBlendTime)
		{
			m_isAnimBlend = false;
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackEnable(1, false);
			//m_pAnimController->SetTrackWeight(1, 0.0f);
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAnimController->SetTrackWeight(0, fWeight);
			m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);
		}
	}

	LPD3DXANIMATIONSET pCurAnimSet = NULL;
	m_pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);

	if (GetTickCount() - m_dAnimStartTime > pCurAnimSet->GetPeriod() * 1000 - m_fBlendTime * 1000)
	{
		if(!m_isMoving) 
			SetAnimationIndexBlend(0);
	}

	m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
	cSkinnedMesh::Update((ST_BONE*)m_pRoot, &m_matWorldTM);
	UpdateSkinnedMesh(m_pRoot);

	//m_matOBB = (D3DXMATRIXA16)*m_pCurrentBoneMatrices;
	//m_matOBB = m_pRoot->TransformationMatrix * m_matRot * m_matTranse;
	//m_matOBB = m_pRoot->TransformationMatrix * m_matWorld;
	
	m_matOBB = m_matRot * m_matTranse;
	//D3DXMatrixScaling(&m_matOBB, 20, 40, 20);
	//m_matOBB *= m_matWorldTM;
	m_pOBB->Update(&m_matOBB);
	m_pWeapon->Update(&m_matOBB);
}

void cArthur::Update(EventType event)
{
	m_fvelocity = 0;
	D3DXMATRIXA16 TempRot;
	D3DXMatrixIdentity(&TempRot);

	//float delta = g_pTimeManager->GetElapsedTime();
	float delta = 0.001f;
	bool isKeyDown = false;
	
	if (event == EventType::EVENT_ARROW_UP)
	{
		m_fvelocity = 300.0f * delta;
		isKeyDown = true;
	}
	if (event == EventType::EVENT_ARROW_LEFT)
	{
		D3DXVec3TransformNormal(&m_vDir, &m_vDir, D3DXMatrixRotationY(&TempRot, -125.0f * delta));
		m_vRot.y -= 125.0f * delta;
		isKeyDown = true;
	}
	if (event == EventType::EVENT_ARROW_DOWN)
	{
		m_fvelocity = -118.5f * delta;
		isKeyDown = true;
	}
	if (event == EventType::EVENT_ARROW_RIGHT)
	{
		D3DXVec3TransformNormal(&m_vDir, &m_vDir, D3DXMatrixRotationY(&TempRot, 125.0f * delta));
		m_vRot.y += 125.0f * delta;
		isKeyDown = true;
	}

	D3DXVec3Normalize(&m_vDir, &m_vDir);
	m_vPos += m_vDir * m_fvelocity;

	static int n = 0;
	
	if(event == EventType::EVENT_LBUTTONDOWN)
	{
		SetAnimationIndexBlend(n++);
	}
}

void cArthur::Render(D3DXMATRIXA16 * pmat)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	cSkinnedMesh::Render();
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	m_pOBB->OBBBOX_Render(D3DCOLOR_XRGB(255, 0, 0));
	m_pWeapon->Render(NULL);
}

void cArthur::SetTranseform(D3DXMATRIXA16* pmat)
{
	if(pmat)
	{
		SetTransform(pmat);
	}
}

cArthurWeapon::cArthurWeapon()
{
	D3DXMatrixIdentity(&m_matOBB);
}

cArthurWeapon::~cArthurWeapon()
{
}

void cArthurWeapon::Setup(D3DXFRAME* pFrame,
							D3DXMESHCONTAINER* pMesh,
							D3DXMATRIXA16* pmat)
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

			if(NumVertice)
			{
				DWORD* Vertices = new DWORD[NumVertice];
				float* Weights = new float[NumVertice];
				pSkin->GetBoneInfluence(BoneNum, Vertices, Weights);

				DWORD Stride = D3DXGetFVFVertexSize(pMesh->MeshData.pMesh->GetFVF());

				D3DXMATRIX* matInvBone = pSkin->GetBoneOffsetMatrix(BoneNum);

				char* pVertices;
				pMesh->MeshData.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);

				for(DWORD i = 0; i < NumVertice; i++)
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
	m_pOBB = new cOBB;
	m_pOBB->Setup(vMin, vMax, pmat);
}

void cArthurWeapon::Update(D3DXMATRIXA16* pmat)
{
	m_pOBB->Update(pmat);
}

void cArthurWeapon::Render(D3DXMATRIXA16* pmat)
{
	m_pOBB->OBBBOX_Render(D3DCOLOR_XRGB(255, 255, 255));
}
