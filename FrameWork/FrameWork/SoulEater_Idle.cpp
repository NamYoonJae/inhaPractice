#include "stdafx.h"
#include "SoulEater_Idle.h"
#include "TimerManager.h"
#include "DragonSoulEater.h"
cSoulEater_Idle::cSoulEater_Idle()
	: cSoulEaterState()
	, m_dwElapsedTime(GetTickCount())
	, m_IsAnimBlend(false)
{
	m_nCurentIndex = 0;
}

cSoulEater_Idle::cSoulEater_Idle(cDragonSoulEater *pDragon)
	: cSoulEaterState(pDragon)
	, m_dwElapsedTime(GetTickCount())
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
	
	TargetCapture();

	if (!m_IsAnimBlend)
	{
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Idle); // 1¹øÀÚ¸®
		m_IsAnimBlend = true;
	}
	DWORD dwCurrentTime = GetTickCount();
	if (dwCurrentTime - m_dwElapsedTime >= 1500.0f
		&& m_pDragon->GetTarget())
	{
		m_pDragon->Request();
		return;
	}

}
