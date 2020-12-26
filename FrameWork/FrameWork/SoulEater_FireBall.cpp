#include "stdafx.h"
#include "SoulEater_FireBall.h"
#include "DragonSoulEater.h"
#include "FireBall.h"
#include "ObjectPool.h"
#include "AllocateHierarchy.h"
#pragma once

cSoulEater_FireBall::cSoulEater_FireBall()
{
	m_nCurentIndex = 5;
	m_nIndex = 7;
	m_nSoundIndex = (int)eSoundList::Dragon_Fly1;
	m_dwPrevTime = m_dwDelayTime = 0.0f;

}

cSoulEater_FireBall::cSoulEater_FireBall(cDragonSoulEater *pDragon)
	:cSoulEaterState(pDragon)
{
	m_nCurentIndex = 5;
	m_nIndex = 7;
	m_nSoundIndex = (int)eSoundList::Dragon_Fly1;
	m_dwPrevTime = m_dwDelayTime = 0.0f;
}


cSoulEater_FireBall::~cSoulEater_FireBall()
{
}

void cSoulEater_FireBall::handle()
{
	if (m_pDragon == NULL) return;

	if (m_vTarget == D3DXVECTOR3(0, 0, 0))
	{
		TargetCapture();
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Run);
	}
	// TakeOff7 - Fly Float6 - Fly Glide(5,4) - Land3

	if (m_nIndex == 3)
	{
		m_pDragon->Request();
		return;
	}

	if (GetTickCount() - m_dwPrevTime < m_dwDelayTime)
		return;


	LPD3DXANIMATIONCONTROLLER pAnimController = m_pDragon->GetSkinnedMesh().GetAnimationController();
	LPD3DXANIMATIONSET pCurAnimSet = NULL;
	pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
	if (GetTickCount() - m_pDragon->GetSkinnedMesh().GetAnimStartTime()
		- pCurAnimSet->GetPeriod() * 1000.0f - m_pDragon->GetSkinnedMesh().GetBlendTime() * 1000.0f)
	{
		m_dwPrevTime = GetTickCount();
		m_dwDelayTime = 500.0f;
		
		switch (m_nIndex)
		{
		case 4:
		{
			cFireBall* mFireBall;
			mFireBall = new cFireBall;
			D3DXVECTOR3 vDir, vPos;
			D3DXMATRIXA16 matCurrentAnimMatrix;

			vPos = m_pDragon->GetPos();// +m_pDragon->GetDirection();

			// ¸Ó¸® 

			ST_BONE *pBone = (ST_BONE*)D3DXFrameFind(m_pDragon->GetSkinnedMesh().GetFrame(), "Head");
			matCurrentAnimMatrix = pBone->CombinedTransformationMatrix;

			vPos.x += matCurrentAnimMatrix._41;
			vPos.y += matCurrentAnimMatrix._42;
			vPos.z += matCurrentAnimMatrix._43;
			D3DXVECTOR3 vTarget = m_vTarget;
			vTarget.y += 10.0f;
			vDir = vTarget - vPos;
			
			D3DXVec3Normalize(&vDir, &vDir);
			mFireBall->SetDirection(vDir);

			vPos += vDir * 4.0f;

			mFireBall->SetPos(vPos);
			mFireBall->Setup();

			mFireBall->SetDirection(vDir);
			mFireBall->Tagging(Tag::Tag_FireBall);
			ObjectManager->AddChild(mFireBall);
			m_dwDelayTime = 1000.0f;
		}
		break;
		case 3:
			m_dwDelayTime = 1000.0f;
			break;
		};
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(m_nIndex--);
	
		if(m_nSoundIndex <= 29)
			g_pSoundManager->PlaySFX(m_nSoundIndex++);
		// 7 6 5 4 3
		//26 27 28 29


	}


}
