#include "stdafx.h"
#include "SoulEater_Idle.h"
#include "TimerManager.h"
#include "DragonSoulEater.h"
cSoulEater_Idle::cSoulEater_Idle()
	: cSoulEaterState()
	, m_IsAnimBlend(false)
{
	m_nCurentIndex = 0;
}

cSoulEater_Idle::cSoulEater_Idle(cDragonSoulEater *pDragon)
	: cSoulEaterState(pDragon)
	, m_IsAnimBlend(false)
{
	m_nCurentIndex = 0;
}


cSoulEater_Idle::~cSoulEater_Idle()
{

}


void cSoulEater_Idle::handle()
{
	if (m_pDragon == NULL) return;
	DWORD dwCurrentTime = GetTickCount();

	if (!m_IsAnimBlend)
	{
		LPD3DXANIMATIONCONTROLLER pAnimController = m_pDragon->GetSkinnedMesh().GetAnimationController();
		LPD3DXANIMATIONSET pCurAnimSet = NULL;
		pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
		if (GetTickCount() - m_pDragon->GetSkinnedMesh().GetAnimStartTime()
			- pCurAnimSet->GetPeriod() * 1000.0f - m_pDragon->GetSkinnedMesh().GetBlendTime() * 1000.0f)
		{
			m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Idle);
			m_IsAnimBlend = true;
			//TargetCapture();
			m_dwElapsedTime = GetTickCount();
		}

	}
	if (dwCurrentTime - m_dwElapsedTime >= 1000.0f
		&& m_pDragon->GetTarget())
	{
		m_pDragon->Request();
		return;
	}

}
