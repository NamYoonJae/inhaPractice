#include "stdafx.h"
#include "LavaGolem.h"
#include "SkinnedMesh.h"

//
#include "cOBB.h"
#include "cCharater.h"
#include "ObjectPool.h"

#include "LavaState.h"
#include "TimerManager.h"

//
#include "Orb.h"
#include "Paladin.h"
#include "PaladinState.h"
#pragma once

cLavaGolem::cLavaGolem()
	:m_pState(NULL)
	,m_pSkinnedMesh(NULL)
	,m_fDist(INT_MAX)
	,m_pvTarget(NULL)
	,m_pMg_Attack(NULL)
	,m_pMg_Die(NULL)
	,m_pMg_Run(NULL)
{
	m_fMaxHP = 1000.0f;
	m_fCurrentHP = m_fMaxHP;
	m_fDamege = 50.0f;
	m_IsAttack = false;
	
}


cLavaGolem::~cLavaGolem()
{
	SafeDelete(m_pSkinnedMesh);
	SafeDelete(m_pState);
	SafeDelete(m_pOBB);
	SafeDelete(m_pMg_Attack);
	SafeDelete(m_pMg_Die);
	SafeDelete(m_pMg_Run);
}

void cLavaGolem::Setup()
{
	//m_pSkinnedMesh = new cSkinnedMesh(szFolder,szFileName);

	//string szFolder = "data/XFile/LavaGolem";
	char* szFolder = "data/XFile/LavaGolem";
	
	m_pMg_Run = new cSkinnedMesh(szFolder, "Mg_Move.X");
	m_pMg_Die = new cSkinnedMesh(szFolder, "Mg_Die.X");
	m_pMg_Attack = new cSkinnedMesh(szFolder, "Mg_Attack.X");


	m_pSkinnedMesh = m_pMg_Run;
	m_pOBB = new cOBB;

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	m_pOBB->Setup(m_pMg_Run,&matS);

	ZeroMemory(&m_Mstl, sizeof(D3DMATERIAL9));
	m_Mstl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_Mstl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_Mstl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	m_pState = new cLavaIdle(this);

	D3DXMatrixIdentity(&m_matR);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pSkinnedMesh->SetTransform(&matWorld);

	cCharater* m_player = (cCharater*)ObjectManager->SearchChild(Tag::Tag_Player);

	if (m_player != nullptr)
	{
		m_pvTarget = m_player->GetpPos();
	}
	
}

void cLavaGolem::Update()
{
	if (m_pSkinnedMesh)
	{
		if (m_pSkinnedMesh->GetIsBlend())
		{
			float fPassedBlendTime = m_pSkinnedMesh->GetPassedBlendTime();
			fPassedBlendTime += g_pTimeManager->GetElapsedTime();
			m_pSkinnedMesh->SetPassedBlendTime(fPassedBlendTime);

			if (fPassedBlendTime >= m_pSkinnedMesh->GetBlendTime())
			{
				m_pSkinnedMesh->SetIsBlend(false);
				m_pSkinnedMesh->GetAnimationController()->SetTrackWeight(0, 1.0f);
				m_pSkinnedMesh->GetAnimationController()->SetTrackEnable(1, false);
			}
			else
			{
				float fWeight = fPassedBlendTime / m_pSkinnedMesh->GetBlendTime();
				m_pSkinnedMesh->GetAnimationController()->SetTrackWeight(0, fWeight);
				m_pSkinnedMesh->GetAnimationController()->SetTrackWeight(1, 1.0f - fWeight);
			}
		}

		m_pSkinnedMesh->GetAnimationController()->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
		this->GetSkinnedMesh().Update((ST_BONE*)this->GetSkinnedMesh().GetFrame()
			, &this->GetSkinnedMesh().m_matWorldTM);
		m_pSkinnedMesh->UpdateSkinnedMesh(m_pSkinnedMesh->GetFrame());
	}

	// 예비
	
	if (m_pvTarget && m_pState->GetStateIndex() != 3)
	{
		m_fDist = (sqrt(pow(m_pvTarget->x - m_vPos.x, 2) +
			pow(m_pvTarget->z - m_vPos.z, 2)));

		D3DXVECTOR3 goal = *m_pvTarget;
		D3DXVECTOR3 currentPos = m_vPos;
		D3DXVECTOR3 vUp(0, 1, 0);
		m_vDir = (goal - currentPos);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		D3DXMATRIXA16 matR,matRy;
		D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_vDir, &vUp);
		D3DXMatrixTranspose(&matR, &matR);
		D3DXMatrixRotationY(&matRy, D3DX_PI);
		
		matR = matR * matRy;
		SetRotationMatrix(&matR);
		
	}

	//

	if (m_fCurrentHP <= 0.0f )
	{
		Request(3);
		return;
	}

	D3DXMATRIXA16 matWorld, matT,
		matR, matRx, matRy, matRz, matS;
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixRotationX(&matRx, m_vRot.x);
	D3DXMatrixRotationY(&matRy, m_vRot.y);
	D3DXMatrixRotationZ(&matRz, m_vRot.z);
	matR = matRx * matRy * matRz;

	if (m_matR)
		matR = m_matR;
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	matWorld = matR * matT;

	m_pOBB->Update(&matWorld);

	if (m_pState)
		m_pState->Handle();
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
	if (m_matR)
		matR = m_matR;
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
		//안전하게 제거하기 위해선
		m_isDelete = true;

		//if (m_pMaster)
		//	m_pMaster->SubtractGolem();
		return;
	}



	

}

void cLavaGolem::CollisionProcess(cObject* pObject)
{
	cOBB *pOBB = pObject->GetOBB();
	int nTag = pObject->GetTag();

	if(nTag == Tag::Tag_Player && m_IsAttack)
	{
		cPaladin* Paladin = (cPaladin*)pObject;
		cOBB*pBody = Paladin->GetPartsList().at(1)->GetOBB();

		if(cOBB::IsCollision(m_pOBB,pBody) && pObject->GetCollsionInfo(m_nTag) == nullptr)
		{
			CollisionInfo info;
			info.dwCollsionTime = GetTickCount();
			info.dwDelayTime = 1300;
			pObject->AddCollisionInfo(m_nTag, info);

			g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "Golem_Attack Hit Player");

		}
	}

	D3DXVECTOR3 vOtherPos = pObject->GetPos();
	float dist = pow(m_vPos.x - vOtherPos.x, 2)
		+ pow(m_vPos.z - vOtherPos.z, 2);

	cOBB* pObb;
	D3DXMATRIXA16 matW;
	
	switch (nTag)
	{
	case Tag::Tag_Orb:
	{
		cOrb* pOrb = (cOrb*)pObject;
		pObb = pOrb->GetSubOBB();
		matW = pOrb->GetSubOBB()->GetWorldMatrix();
	}
	break;
	case Tag::Tag_SwampA:
	case Tag::Tag_SwampB:
		return;
	default:
		pObb = pOBB;
		matW = pObb->GetWorldMatrix();
		break;
	}
	
	D3DXVECTOR3 vOtherPoint0 = pObb->GetList().at(0);
	matW = pObb->GetWorldMatrix();
	D3DXVec3TransformCoord(&vOtherPoint0, &vOtherPoint0, &matW);
	float Radian0 = pow(vOtherPos.x - vOtherPoint0.x, 2) + pow(vOtherPos.z - vOtherPoint0.z, 2);
	
	D3DXVECTOR3 vPoint0 = m_pOBB->GetList().at(0);
	matW = m_pOBB->GetWorldMatrix();
	D3DXVec3TransformCoord(&vPoint0, &vPoint0, &matW);
	float Radian1 = pow(m_vPos.x - vPoint0.x, 2) + pow(m_vPos.z - vPoint0.z, 2);
	
	float Radian = Radian0 + Radian1;
	
	while (dist < Radian)
	{
			m_vPos += -m_vDir * 0.02f;

			dist = pow(m_vPos.x - vOtherPos.x, 2)
				+ pow(m_vPos.z - vOtherPos.z, 2);
	}
	m_vPos += D3DXVECTOR3(0, 0, 1);
	

}
