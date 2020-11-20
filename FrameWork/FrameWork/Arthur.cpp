#include "stdafx.h"
#include "SkinnedMesh.h"
#include "SkinnedMeshManager.h"

#include "Arthur.h"


cArthur::cArthur()
	:m_pMesh(nullptr)
	,m_vScale(1, 1, 1)
	,m_fvelocity(0.f)
{
}


cArthur::~cArthur()
{
	SafeDelete(m_pMesh);
}

void cArthur::Setup(char* szFolder, char* szFile)
{
	m_pMesh = new cSkinnedMesh(szFolder, szFile);
	m_pMesh->SetAnimationIndex(0);

	EventManager->Attach(this);
}

void cArthur::Update()
{
	D3DXMatrixScaling(&m_matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationY(&m_matRot, m_vRot.y);
	D3DXMatrixTranslation(&m_matTranse, m_vPos.x, m_vPos.y, m_vPos.z);
	
	m_matWorld = m_matScale * m_matRot * m_matTranse;
	m_pMesh->m_matWorldTM = m_matWorld;

	SafeUpdate(m_pMesh);
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
	
	if(!isKeyDown)
	{
		//SetSkinnedMesh("data/XFile/Arthur", "arthur_idle01.X");
	}
	else
	{
		SetSkinnedMesh("data/XFile/Arthur", "arthur_run01.X");
	}

	D3DXVec3Normalize(&m_vDir, &m_vDir);
	m_vPos += m_vDir * m_fvelocity;

	//int AnimGroup[3] = { 0, 1, 2 };
	static int n = 0;
	
	if(event == EventType::EVENT_LBUTTONDOWN)
	{
		//m_pMesh->SetAnimationIndex(n++);
		//SetAnimationController("data/XFile/Arthur", "arthur_Attack01.X");
		SetSkinnedMesh("data/XFile/Arthur", "arthur_Attack01.X");
	}
	else if (event == EventType::EVENT_RBUTTONDOWN)
	{
		SetSkinnedMesh("data/XFile/Arthur", "arthur_a01.X");
	}
}

void cArthur::Render(D3DXMATRIXA16 * pmat)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	SafeRender(m_pMesh);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

void cArthur::SetTranseform(D3DXMATRIXA16* pmat)
{
	if(pmat)
	{
		m_pMesh->SetTransform(pmat);
	}
}

void cArthur::SetAnimationController(char* szFolder, char* szFile)
{
	m_pMesh->SetAnimationController(szFolder, szFile);
}

void cArthur::SetSkinnedMesh(char* szFolder, char* szFile)
{
	m_pMesh = g_pSkinnedMeshManager->GetSkinnedMesh(szFolder, szFile);
}
