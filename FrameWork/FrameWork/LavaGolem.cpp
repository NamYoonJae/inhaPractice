#include "stdafx.h"
#include "LavaGolem.h"
#include "SkinnedMesh.h"

//
#include "cOBB.h"
#include "cCharater.h"
#include "ObjectPool.h"

#include "LavaState.h"
 
#pragma once;

cLavaGolem::cLavaGolem()
	:m_pState(NULL)
	,m_pSkinnedMesh(NULL)
	,m_fMaxHP(10000.0f)
	,m_fDist(INT_MAX)
{
	m_fCurrentHP = m_fMaxHP;
}


cLavaGolem::~cLavaGolem()
{
	SafeDelete(m_pSkinnedMesh);
	SafeDelete(m_pState);
	SafeDelete(m_pOBB);
}

void cLavaGolem::Setup(char* szFolder, char* szFileName)
{
	m_pSkinnedMesh = new cSkinnedMesh(szFolder,szFileName);
	m_pOBB = new cOBB;

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	m_pOBB->Setup(m_pSkinnedMesh,&matS);

	ZeroMemory(&m_Mstl, sizeof(D3DMATERIAL9));
	m_Mstl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_Mstl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_Mstl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	m_pState = new cLavaIdle(this);
}

void cLavaGolem::Update()
{
	// 예비
	cCharater* m_player = (cCharater*)ObjectManager->SearchChild(Tag::Tag_Player);
	if (m_player)
	{
		m_pvTarget = m_player->GetPos();

		m_fDist = (sqrt(pow(m_pvTarget->x - m_vPos.x, 2) +
			pow(m_pvTarget->z - m_vPos.z, 2)));
	}

	//
	if (m_pState)
		m_pState->Handle();




	if (m_fCurrentHP <= 0.0f)
	{
		Request(3);
	}
}

void cLavaGolem::Render(D3DXMATRIXA16 * pmat)
{
	D3DXMATRIXA16 matWorld, matT,
		matR, matRx, matRy, matRz, matS;
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixRotationX(&matRx, m_vRot.x);
	D3DXMatrixRotationY(&matRy, m_vRot.y);
	D3DXMatrixRotationZ(&matRz, m_vRot.z);
	matR = matRx * matRy * matRz;
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	matWorld = matS * matR * matT;

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_Mstl);
	if(m_pSkinnedMesh)
		m_pSkinnedMesh->Render();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	if (m_pOBB)
		m_pOBB->OBBBOX_Render(D3DXCOLOR(0.5f, 0.5f, 1.0f,1.0f));
}

void cLavaGolem::Request(int state)
{
	if (m_pState)
		SafeDelete(m_pState);

	switch (state)
	{
	case 0: // idle
		m_pState = new cLavaIdle(this);
		break;
	case 1: // 이동
		m_pState = new cLavaRun(this);
		break;
	case 2: // attack
		m_pState = new cLavaAttack(this);
		break;
	case 3: // 죽음
		m_pState = new cLavaDie(this);
		break;
	case 4:
		//삭제
		return;
	}



	

}
