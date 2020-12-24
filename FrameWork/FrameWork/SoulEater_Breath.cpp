#include "stdafx.h"
#include "SoulEater_Breath.h"
#include "DragonSoulEater.h"
#include "DragonBreathe.h"
#include "ObjectPool.h"
#include "AllocateHierarchy.h"
#pragma once


cSoulEater_Breath::cSoulEater_Breath()
{
	m_nCurentIndex = 7;
	m_IsAnimBlend = false;
	m_dwBreathDurationTime = 5000.0f;
}

cSoulEater_Breath::cSoulEater_Breath(cDragonSoulEater* pDragon)
	:cSoulEaterState(pDragon)
{
	m_nCurentIndex = 7;
	m_IsAnimBlend = false;
	m_dwBreathDurationTime = 5000.0f;
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
			pBreath->SetDurationTime(m_dwBreathDurationTime);
			
			D3DXVECTOR3 vPos = m_pDragon->GetPos();
			D3DXMATRIXA16 matCurrentAnimMatrix;
			ST_BONE *pBone = (ST_BONE*)D3DXFrameFind(m_pDragon->GetSkinnedMesh().GetFrame(), "Jaw");
			matCurrentAnimMatrix = pBone->CombinedTransformationMatrix;
			vPos.x += matCurrentAnimMatrix._41;
			vPos.y += matCurrentAnimMatrix._42;
			vPos.z += matCurrentAnimMatrix._43;
			pBreath->SetUp(vPos);

			pBreath->Tagging(Tag::Tag_Breath);
			ObjectManager->AddChild(pBreath);
			
			m_IsAnimBlend = true;
			m_dwStartTime = GetTickCount();

			g_pSoundManager->PlaySFX(eSoundList::Dragon_Breath);
		}
	}
	else if(GetTickCount() - m_dwStartTime > m_dwBreathDurationTime)
	{
		m_pDragon->Request();
		return;
	}
	
}
