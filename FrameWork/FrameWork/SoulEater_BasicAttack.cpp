#include "stdafx.h"
#include "SoulEater_BasicAttack.h"
#include "DragonSoulEater.h"
#include "jsonManager.h"
//#include "SoundManager.h"

#pragma once
cSoulEater_BasicAttack::cSoulEater_BasicAttack()
	: cSoulEaterState()
	, m_IsAnimBlend(false)
	, m_IsRun(false)
	, m_dwSoundTime(500.0f)
{
	m_nCurentIndex = 1;
	m_dwElapsedTime = GetTickCount();
	TargetDistance = 1000.0f;
}

cSoulEater_BasicAttack::cSoulEater_BasicAttack(cDragonSoulEater *pDragon)
	: cSoulEaterState(pDragon)
	, m_IsAnimBlend(false)
	, m_IsRun(false)
	, m_dwSoundTime(500.0f)
{
	m_nCurentIndex = 1;
	m_dwElapsedTime = GetTickCount();
	TargetDistance = 1000.0f;


	// json Attribute
	JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* p_SKILL_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS SKILL/");
	JSON_Object* p_ExtraPattern_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/Extra Pattern/");

	// 기본공격 // 패턴 1
	m_BasicAttack_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 1/Attribute 1/Melee rate");
	m_BasicAttack_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 1/Attribute 1/Elemental rate");

	// log
	//cout << "BOSS_jsonValue BasicAttack_Physic_Rate : " << m_BasicAttack_Physic_Rate << endl;
	//cout << "BOSS_jsonValue BasicAttack_Elemental_Rate : " << m_BasicAttack_Elemental_Rate << endl;
}

cSoulEater_BasicAttack::~cSoulEater_BasicAttack()
{
}

void cSoulEater_BasicAttack::handle()
{
	// 함수로 만들자
	if (m_pDragon == NULL ) return;
	
	if (m_vTarget == D3DXVECTOR3(0, 0, 0))
	{
		TargetCapture();
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Walk);
		m_IsRun = true;
	}

	D3DXVECTOR3 pos = m_pDragon->GetPos();
	
	//
	float distance = pow(pos.x - m_vTarget.x, 2) + pow(pos.z - m_vTarget.z, 2);
	
	if (distance <= TargetDistance)
	{
		if (!m_IsAnimBlend)
		{
			m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Basic_Attack);
			g_pSoundManager->PlaySFX((int)eSoundList::Dragon_BasicAttack);
			m_dwElapsedTime = GetTickCount();
			m_IsAnimBlend = true;
			m_IsRun = false;
			m_isAttack = true;
		}
		else if(GetTickCount() - m_dwElapsedTime >= 500.0f && m_IsAnimBlend)
		{
			m_isAttack = false;
			m_pDragon->Request();
			return;
		}

	}
	else
	{
		//pos += m_vDir * 0.003f; // 이동
		pos += m_vDir * json_Function::object_get_double(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/BOSS/Move Speed");

		m_pDragon->SetPos(pos);
		//GenerateRandomNum(
	}
	
	if (GetTickCount() - m_dwElapsedTime >= m_dwSoundTime && m_IsRun)
	{
		g_pSoundManager->PlaySFX(GenerateRandomNum((int)eSoundList::Dragon_Move0, (int)eSoundList::Dragon_Move9));
		m_dwElapsedTime = GetTickCount();
	}
}
