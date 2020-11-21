#include "stdafx.h"
#include "SkinnedMesh.h"
#include "TimerManager.h"
#include "BoundingBox.h"
#include "basic.h"

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
	
	m_pOBB = new cBoundingBox;
	m_pOBB->Setup(this);
	m_pOBB->SetPivot(D3DXVECTOR3(0, 0.001f, 0));

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

	D3DXMatrixScaling(&m_matOBB, 20, 40, 20);
	m_matOBB *= m_matWorldTM;
	m_pOBB->Update(&m_matOBB);
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

	//int AnimGroup[3] = { 0, 1, 2 };
	static int n = 0;
	
	if(event == EventType::EVENT_LBUTTONDOWN)
	{
		SetAnimationIndexBlend(n++);
		//SetAnimationController("data/XFile/Arthur", "arthur_Attack01.X");
		//SetSkinnedMesh("data/XFile/Arthur", "arthur_Attack01.X");
	}
	else if (event == EventType::EVENT_RBUTTONDOWN)
	{
		//SetSkinnedMesh("data/XFile/Arthur", "arthur_a01.X");
	}

	//if(event == EventType::EVENT_JUMP)
	//{
	//	m_pMesh->SetAnimationIndexBlend(0);
	//}
}

void cArthur::Render(D3DXMATRIXA16 * pmat)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	cSkinnedMesh::Render();
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pOBB->Render(D3DCOLOR_XRGB(255, 0, 0));
}

void cArthur::SetTranseform(D3DXMATRIXA16* pmat)
{
	if(pmat)
	{
		SetTransform(pmat);
	}
}
