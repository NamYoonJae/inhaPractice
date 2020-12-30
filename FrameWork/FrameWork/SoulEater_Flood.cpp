#include "stdafx.h"
#include "SoulEater_Flood.h"
#include "DragonSoulEater.h"
#include "Swamp.h"
#include "ObjectPool.h"
#include "jsonManager.h"
#include "SwampB.h"

#pragma once

cSoulEater_Flood::cSoulEater_Flood()
{
	m_nCurentIndex = 8;
	m_dwCoolTime = 1000.0f;
	m_dwElapsedTime = 0.0f;
	m_nCntSwamp = 0;
}

cSoulEater_Flood::cSoulEater_Flood(cDragonSoulEater* pDragon)
	:cSoulEaterState(pDragon)
{
	m_nCurentIndex = 8;
	m_dwCoolTime = 1000.0f;
	m_dwElapsedTime = 0.0f;
	m_nCntSwamp = 0;
	m_IsTrigger = false;
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
			m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::FireBall_Shot);
			m_vAttackTarget = m_vTarget;
			m_IsTrigger = true;
			m_dwElapsedTime = GetTickCount();
			
		}
	}
	else if(m_IsTrigger && (GetTickCount() -  m_dwElapsedTime >= m_dwCoolTime))
	{
		m_IsTrigger = false;
		cSwampB *pSwampB = new cSwampB;
		pSwampB->Setup(Tag::Tag_SwampB);
		pSwampB->SetPos(m_vAttackTarget);
		pSwampB->SetDuration(json_Function::object_get_double(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/BOSS SKILL/SKILL 3/Attribute/Duration")); // 장판공격 지속시간 처리

		D3DXVECTOR3 vec3SwampSize(
			(float)json_Function::object_get_double(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/BOSS SKILL/SKILL 3/Attribute/Radius"),
			0.001f,
			(float)json_Function::object_get_double(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/BOSS SKILL/SKILL 3/Attribute/Radius")
		);
		pSwampB->SetScale(vec3SwampSize);


		//pSwamp->Tagging(Tag::Tag_SwampB);
		ObjectManager->AddChild(pSwampB);
		m_nCntSwamp++;
	}

	
	if (m_nCntSwamp > 6)
	{
		m_pDragon->Request();
		return;
	}
	
}
