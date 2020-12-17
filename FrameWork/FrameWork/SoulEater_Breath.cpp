#include "stdafx.h"
#include "SoulEater_Breath.h"
#include "DragonSoulEater.h"
#include "DragonBreathe.h"
#include "ObjectPool.h"
#pragma once


cSoulEater_Breath::cSoulEater_Breath()
{
	m_nCurentIndex = 7;
	m_IsAnimBlend = false;
}

cSoulEater_Breath::cSoulEater_Breath(cDragonSoulEater* pDragon)
	:cSoulEaterState(pDragon)
{
	m_nCurentIndex = 7;
	m_IsAnimBlend = false;
}


cSoulEater_Breath::~cSoulEater_Breath()
{
}

void cSoulEater_Breath::handle()
{
	if (m_pDragon == NULL) return;

	TargetCapture();

	if(m_IsAnimBlend == false)
	{
		LPD3DXANIMATIONCONTROLLER pAnimController = m_pDragon->GetSkinnedMesh().GetAnimationController();
		LPD3DXANIMATIONSET pCurAnimSet = NULL;
		pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
		if (GetTickCount() - m_pDragon->GetSkinnedMesh().GetAnimStartTime()
			- pCurAnimSet->GetPeriod() * 1000.0f - m_pDragon->GetSkinnedMesh().GetBlendTime() * 1000.0f)
		{
			m_pDragon->GetSkinnedMesh().SetAnimationIndex(AnimationSet::FireBall_Shot);
			cDragonBreathe *pBreath = new cDragonBreathe;
			pBreath->GetTarget(m_pDragon->GetTarget());
			pBreath->SetDurationTime(m_dwElapsedTime);
			pBreath->SetUp();
			pBreath->Tagging(Tag::Tag_Breath);
			ObjectManager->AddChild(pBreath);
			
			m_IsAnimBlend = true;
			m_dwStartTime = GetTickCount();
		}
	}
	else if(GetTickCount() - m_dwStartTime > m_dwElapsedTime)
	{
		m_pDragon->Request();
		return;
	}
	
}
