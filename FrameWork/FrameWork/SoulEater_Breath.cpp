#include "stdafx.h"
#include "SoulEater_Breath.h"
#include "DragonSoulEater.h"
#include "DragonBreathe.h"
#include "ObjectPool.h"
#include "AllocateHierarchy.h"
#include "jsonManager.h"
#pragma once


cSoulEater_Breath::cSoulEater_Breath()
{
	m_nCurentIndex = 7;
	m_IsAnimBlend = false;
	//m_Breath_Duration = 5000.0f;

	JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* p_SKILL_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS SKILL/");

	m_Breath_Duration = json_Function::object_get_double(p_SKILL_object, "SKILL 4/Attribute/Duration");
	m_Breath_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 4/Attribute/Melee rate");
	m_Breath_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 4/Attribute/Elemental rate");;
}

cSoulEater_Breath::cSoulEater_Breath(cDragonSoulEater* pDragon)
	:cSoulEaterState(pDragon)
{
	m_nCurentIndex = 7;
	m_IsAnimBlend = false;
	//m_Breath_Duration = 5000.0f;

	JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* p_SKILL_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS SKILL/");

	m_Breath_Duration = (DWORD)json_Function::object_get_double(p_SKILL_object, "SKILL 4/Attribute/Duration");
	m_Breath_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 4/Attribute/Melee rate");
	m_Breath_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 4/Attribute/Elemental rate");


	D3DMATERIAL9 Mstl;
	ZeroMemory(&Mstl, sizeof(D3DMATERIAL9));
	Mstl.Ambient = D3DXCOLOR(0.8f, 0.3f, 0.0f, 1.0f);
	Mstl.Specular = D3DXCOLOR(0.8f, 0.3f, 0.0f, 1.0f);
	Mstl.Diffuse = D3DXCOLOR(0.8f, 0.3f, 0.0f, 1.0f);

	m_PrevMstl = m_pDragon->GetMaterial();
	m_pDragon->SetMaterial(Mstl);
	m_pDragon->GetSkinnedMesh().SetUsemstl(false);

	m_dwElapsedTime = GetTickCount();
}


cSoulEater_Breath::~cSoulEater_Breath()
{
}

void cSoulEater_Breath::handle()
{
	if (m_pDragon == NULL) return;

	TargetCapture();

	if (GetTickCount() - m_dwElapsedTime <= 1500.0f)
	{
		return;
	}

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
			pBreath->SetTarget(m_pDragon->GetTarget());
			pBreath->SetDurationTime(m_Breath_Duration);
			
			D3DXVECTOR3 vPos = m_pDragon->GetPos();
			ST_BONE *pBone = (ST_BONE*)D3DXFrameFind(m_pDragon->GetSkinnedMesh().GetFrame(), "Neck");
			
			pBreath->SetHead(&pBone->CombinedTransformationMatrix);
			pBreath->SetDragonPos(m_pDragon->GetpPos());
			pBreath->Tagging(Tag::Tag_Breath);
			ObjectManager->AddChild(pBreath);
			
			m_IsAnimBlend = true;
			m_dwStartTime = GetTickCount();

			g_pSoundManager->PlaySFX(eSoundList::Dragon_Breath);
		}
	}
	else if(GetTickCount() - m_dwStartTime > m_Breath_Duration)
	{
		m_pDragon->SetMaterial(m_PrevMstl);
		m_pDragon->GetSkinnedMesh().SetUsemstl(true);
		m_pDragon->Request();
		return;
	}
	
}
