#include "stdafx.h"
#include "SoulEater_Flood.h"
#include "DragonSoulEater.h"
#include "Swamp.h"
#include "ObjectPool.h"
#pragma once

cSoulEater_Flood::cSoulEater_Flood()
{
	m_nCurentIndex = 8;
	m_dwCoolTime = 3000.0f;
	m_dwElapsedTime = 0.0f;
}

cSoulEater_Flood::cSoulEater_Flood(cDragonSoulEater* pDragon)
	:cSoulEaterState(pDragon)
{
	m_nCurentIndex = 8;
	m_dwCoolTime = 3000.0f;
	m_dwElapsedTime = 0.0f;
}


cSoulEater_Flood::~cSoulEater_Flood()
{
}

void cSoulEater_Flood::handle()
{
	if (m_pDragon == NULL) return;

	TargetCapture();
	if(m_IsTrigger == false)
	{
		LPD3DXANIMATIONCONTROLLER pAnimController = m_pDragon->GetSkinnedMesh().GetAnimationController();
		LPD3DXANIMATIONSET pCurAnimSet = NULL;
		pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
		if (GetTickCount() - m_pDragon->GetSkinnedMesh().GetAnimStartTime()
			- pCurAnimSet->GetPeriod() * 1000.0f - m_pDragon->GetSkinnedMesh().GetBlendTime() * 1000.0f)
		{
			if(m_nCntSwamp >5)
			{
				m_pDragon->Request();
				std::vector<cObject*> vecSwampList;
				
				return;
			}
			else
			{				
				m_vAttackTarget = m_vTarget;
				m_IsTrigger = true;
				m_dwElapsedTime = GetTickCount();
			}
		}
	}
	else if(m_IsTrigger && (GetTickCount() -  m_dwElapsedTime >= m_dwCoolTime))
	{
		m_IsTrigger = false;
		cSwamp *pSwamp = new cSwamp;
		pSwamp->Setup();
		pSwamp->SetPos(m_vAttackTarget);
		pSwamp->Tagging(Tag::Tag_SwampB);
		ObjectManager->AddChild(pSwamp);
		m_nCntSwamp++;
	}
	
}
