#include "stdafx.h"
#include "SoulEater_TailAttack.h"
#include "DragonSoulEater.h"

cSoulEater_TailAttack::cSoulEater_TailAttack()
	:cSoulEaterState()
	,m_IsAnimBlend(false)
{
	m_nCurentIndex = 2;
}
cSoulEater_TailAttack::cSoulEater_TailAttack(cDragonSoulEater* pDragon)
	:cSoulEaterState(pDragon)
	,m_IsAnimBlend(false)
{
	m_nCurentIndex = 2;
}

cSoulEater_TailAttack::~cSoulEater_TailAttack()
{
}

void cSoulEater_TailAttack::handle()
{
	if (m_pDragon == NULL) return;
	if (m_IsAnimBlend == false)
	{
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Tail_Attack);
		m_IsAnimBlend = true;
	}
	else
	{
		LPD3DXANIMATIONCONTROLLER pAnimController = m_pDragon->GetSkinnedMesh().GetAnimationController();
		LPD3DXANIMATIONSET pCurAnimSet = NULL;
		pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
		if (GetTickCount() - m_pDragon->GetSkinnedMesh().GetAnimStartTime()
			- pCurAnimSet->GetPeriod() * 1000.0f - m_pDragon->GetSkinnedMesh().GetBlendTime() * 1000.0f)
		{
			m_pDragon->Request();
		}
	}

}
