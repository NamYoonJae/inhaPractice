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
{
	m_nCurentIndex = 4;
}

cSoulEater_Scream::cSoulEater_Scream(cDragonSoulEater * pDragon)
	: cSoulEaterState(pDragon)
	, m_IsAnimBlend(false)
{
	m_nCurentIndex = 4;
}


cSoulEater_Scream::~cSoulEater_Scream()
{
}

void cSoulEater_Scream::handle()
{
	float distance = 0.0f;
	if (m_pDragon == NULL) return;
	// 범위안에 있으면 모션블러 
	// 애니메이션이 끝나면 
	if (m_vTarget == D3DXVECTOR3(0, 0, 0))
	{
		TargetCapture();
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

			m_dwElapsedTime = GetTickCount();
		}
	}
	else if (m_IsAnimBlend)
	{
		cBackViewCamera *pCamera = (cBackViewCamera*)ObjectManager->SearchChild(Tag::Tag_Camera);

		D3DXVECTOR3 pos = m_pDragon->GetPos();
		distance = sqrt(pow(pos.x - m_vTarget.x, 2) + pow(pos.z - m_vTarget.z, 2));
		//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "f", distance);
		if (distance <= Radius)
			pCamera->SetVibration(true);
		else
			pCamera->SetVibration(false);

		DWORD dwCurrentTime = GetTickCount();
		if (dwCurrentTime - m_dwElapsedTime >= 5000.0f
			&& m_pDragon->GetTarget()
			&& m_IsAnimBlend)
		{
			pCamera->SetVibration(false);
			m_pDragon->Request();
			return;
		}
	}

}
