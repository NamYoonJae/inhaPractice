#include "stdafx.h"
#include "SoulEater_Rush.h"
#include "DragonSoulEater.h"
#include "SoundManager.h"
#include "Wall.h"
#include "jsonManager.h"
#pragma once

cSoulEater_Rush::cSoulEater_Rush()
	: m_IsHitAnything(false)
	, m_dwStateStartTime(GetTickCount())
	, m_dwPreparationTime(1500.0f)
	, m_IsRush(false)
	
{
}

cSoulEater_Rush::cSoulEater_Rush(cDragonSoulEater *pDragon)
	: cSoulEaterState(pDragon)
	, m_IsHitAnything(false)
	, m_IsRush(false)
	, m_dwStateStartTime(GetTickCount())
	, m_dwPreparationTime(1500.0f)
{
	m_nCurentIndex = 3;

	// json Attribute
	JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* p_SKILL_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS SKILL/");

	// 기본공격 // 패턴 1
	m_RushAttack_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 2/Attribute/Melee rate");
	m_RushAttack_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 2/Attribute/Elemental rate");

	g_pLogger->ValueLog(__FUNCTION__, __LINE__, "sf", "RUSH ELEMENTAL RATE", m_RushAttack_Elemental_Rate);
	//cout << "RUSH RATE         : " << m_RushAttack_Physic_Rate << endl;
}

cSoulEater_Rush::~cSoulEater_Rush()
{
}

void cSoulEater_Rush::handle()
{
	if (m_pDragon == NULL) return;
	
	if (GetTickCount() - m_dwStateStartTime <= m_dwPreparationTime)
	{
		TargetCapture();
		return;
	}

	if (m_IsRush == false)
	{
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Run);
		m_isAttack = m_IsRush = true;
		
	}
	

	D3DXVECTOR3 pos = m_pDragon->GetPos();

	//
	float distance = sqrt(pow(pos.x - m_vTarget.x, 2) + pow(pos.z - m_vTarget.z, 2));

	std::map<int, CollisionInfo> CollisionList = m_pDragon->GetMapCollisionList();

	if (CollisionList.find(Tag::Tag_Wall) != CollisionList.end() &&
		m_IsHitAnything == false)
	{
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Get_Hit);
		m_IsHitAnything = true;
		m_vDir = D3DXVECTOR3(0, 0, 0);
		
		m_pDragon->SetSTUN(m_pDragon->GetSTUN() + m_pDragon->GetWallStunDamage());
		m_pDragon->SetRigid(m_pDragon->GetRigid() + m_pDragon->GetWallRigidDamage());
		
		m_pDragon->HitSound();
		m_pDragon->Request();
		return;
	}

	if (distance <= 30.0f)
	{
		m_pDragon->Request();
		m_isAttack = false;
		return;
	}
	else
	{
		pos += m_vDir * 0.005f;
		m_pDragon->SetPos(pos);
	}

}
