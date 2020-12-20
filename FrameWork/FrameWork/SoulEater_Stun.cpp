#include "stdafx.h"
#include "SoulEater_Stun.h"
#include "DragonSoulEater.h"

cSoulEater_Stun::cSoulEater_Stun()
{
	m_nCurentIndex = 9;
	m_dwElapsedTime = FLT_MAX;
	m_dwStunTime = 8000.0f;
}

cSoulEater_Stun::cSoulEater_Stun(cDragonSoulEater *pDragon,DWORD dwTime)
	:cSoulEaterState(pDragon)
{
	m_nCurentIndex = 9;
	m_dwElapsedTime = FLT_MAX;
	m_dwStunTime = dwTime;
}


cSoulEater_Stun::~cSoulEater_Stun()
{
}

void cSoulEater_Stun::handle()
{
	if (m_pDragon == NULL) return;


	LPD3DXANIMATIONCONTROLLER pAnimController = m_pDragon->GetSkinnedMesh().GetAnimationController();
	LPD3DXANIMATIONSET pCurAnimSet = NULL;
	pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);

	if (GetTickCount() - m_pDragon->GetSkinnedMesh().GetAnimStartTime()
		- pCurAnimSet->GetPeriod() * 1000.0f - m_pDragon->GetSkinnedMesh().GetBlendTime() * 1000.0f)
	{
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Get_Hit);

		m_dwElapsedTime = GetTickCount();
	}

	if (GetTickCount() - m_dwElapsedTime >= m_dwStunTime)
	{
		m_pDragon->SetSTUN(0.0f);
		m_pDragon->Request();
		return;
	}

}
