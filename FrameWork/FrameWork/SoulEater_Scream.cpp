#include "stdafx.h"
#include "SoulEater_Scream.h"
#include "DragonSoulEater.h"
#include "BackViewCamera.h"
#include "ObjectPool.h"
#pragma once
#define Radius 100

cSoulEater_Scream::cSoulEater_Scream()
	:cSoulEaterState()
	, m_IsAnimBlend(false)
	, m_dwScreamCoolTime(2000.0f)
	, m_dwSCreamElapsedTime(0.0f)

{
	m_nCurentIndex = 4;
}

cSoulEater_Scream::cSoulEater_Scream(cDragonSoulEater * pDragon)
	: cSoulEaterState(pDragon)
	, m_IsAnimBlend(false)
	, m_dwScreamCoolTime(2000.0f)
	, m_dwSCreamElapsedTime(0.0f)
{
	m_nCurentIndex = 4;
}


cSoulEater_Scream::~cSoulEater_Scream()
{
}

void cSoulEater_Scream::handle()
{
	static float distance = 0.0f;
	if (m_pDragon == NULL) return;
	// 범위안에 있으면 모션블러 
	// 애니메이션이 끝나면 
	if (m_vTarget == D3DXVECTOR3(0, 0, 0))
	{
		TargetCapture();
		D3DXVECTOR3 pos = m_pDragon->GetPos();
		distance = sqrt(pow(pos.x - m_vTarget.x, 2) + pow(pos.z - m_vTarget.z, 2));
	}

	if (m_IsAnimBlend == false)
	{
		LPD3DXANIMATIONCONTROLLER pAnimController = m_pDragon->GetSkinnedMesh().GetAnimationController();
		LPD3DXANIMATIONSET pCurAnimSet = NULL;
		pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
		if (GetTickCount() - m_pDragon->GetSkinnedMesh().GetAnimStartTime()
			- pCurAnimSet->GetPeriod() * 1000.0f - m_pDragon->GetSkinnedMesh().GetBlendTime() * 1000.0f)
		{
			m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::FireBall_Shot);
			m_IsAnimBlend = true;
			m_dwSCreamElapsedTime = m_dwElapsedTime = GetTickCount();
			g_pSoundManager->PlaySFX(eSoundList::Dragon_Scream);
			cObject* pObject = (cObject*)ObjectManager->SearchChild(Tag::Tag_Player);

			if(pObject->GetCollsionInfo(Tag::Tag_Scream) == nullptr)
			{
				CollisionInfo info;
				info.dwCollsionTime = GetTickCount();
				info.dwDelayTime = 5000.0f;
				pObject->AddCollisionInfo(Tag_Scream, info,0,true,100,0);
			}
		}
	}
	else if (m_IsAnimBlend)
	{
		if (GetTickCount() - m_dwSCreamElapsedTime >= m_dwScreamCoolTime)
		{
			g_pSoundManager->PlaySFX(eSoundList::Dragon_Scream);
			m_dwSCreamElapsedTime = GetTickCount();
		}
		cBackViewCamera *pCamera = (cBackViewCamera*)ObjectManager->SearchChild(Tag::Tag_Camera);

		if (distance <= Radius)
			pCamera->SetVibration(true);
		else
			pCamera->SetVibration(false);

		DWORD dwCurrentTime = GetTickCount();
		if (dwCurrentTime - m_dwElapsedTime >= 5000.0f
			&& m_pDragon->GetTarget()
			&& m_IsAnimBlend)
		{
			m_pDragon->SetRageGauge(0);
			m_pDragon->SetRage(false);
			pCamera->SetVibration(false);
			m_pDragon->Request();
			return;
		}
	}

}
