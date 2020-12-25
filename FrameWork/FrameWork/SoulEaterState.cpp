#include "stdafx.h"
#include "SoulEaterState.h"
#include "DragonSoulEater.h"
#include "jsonManager.h"

#pragma once

cSoulEaterState::cSoulEaterState()
	: m_pDragon(NULL)
	, m_vTarget(0, 0, 0)
	, m_vDir(0, 0, 0)
	, m_dwElapsedTime(GetTickCount())
{
}

cSoulEaterState::cSoulEaterState(cDragonSoulEater *pDragon)
			: m_vTarget(0, 0, 0)
			, m_vDir(0,0,0)
			, m_dwElapsedTime(GetTickCount())
{
	m_pDragon = pDragon;



	// BOSS SKILL status
	{
		JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
		JSON_Object* p_SKILL_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS SKILL/");
		JSON_Object* p_ExtraPattern_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/Extra Pattern/");

		// 파이어볼 // 즉사기 패턴
		m_FireBall_Physic_Rate = json_Function::object_get_double(p_ExtraPattern_object, "FireBall/Attribute/Melee rate");
		m_FireBall_Elemental_Rate = json_Function::object_get_double(p_ExtraPattern_object, "FireBall/Attribute/Elemental rate");
		m_FireBall_Range = json_Function::object_get_double(p_ExtraPattern_object, "FireBall/Attribute/Range");
		// 돌진 // 패턴 2
		m_Rush_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 2/Attribute/Melee rate");
		m_Rush_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 2/Attribute/Elemental rate");
		// 포효 // 포효 패턴
		m_Scream_Range = json_Function::object_get_double(p_ExtraPattern_object, "Scream/Attribute/Range");

		// 브레스 // 패턴 4
		//m_Breath_Duration = json_Function::object_get_double(p_SKILL_object, "SKILL 4/Attribute/Duration");
		//m_Breath_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 4/Attribute/Melee rate");
		//m_Breath_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 4/Attribute/Elemental rate");;
		//// 장판 // 패턴 3 // swamp 로 이동됨
		//m_Flood_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 3/Attribute/Melee rate");
		//m_Flood_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 3/Attribute/Elemental rate");
		//m_Flood_Condition = json_Function::object_get_string(p_SKILL_object, "SKILL 3/Attribute/Condition"); // 상태이상 부여 종류
		//m_Flood_Condition_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 3/Attribute/Condition rate"); // 상태이상 부여치
	}

	// BOSS SKILL Attribute log
	{
		// cout << "BOSS_jsonValue FireBall_Physic_Rate : " << m_FireBall_Physic_Rate << endl;
		// cout << "BOSS_jsonValue FireBall_Elemental_Rate : " << m_FireBall_Elemental_Rate << endl;
		// cout << "BOSS_jsonValue FireBall_Range : " << m_FireBall_Range << endl;
		// cout << "BOSS_jsonValue Rush_Physic_Rate : " << m_Rush_Physic_Rate << endl;
		// cout << "BOSS_jsonValue Rush_Elemental_Rate : " << m_Rush_Elemental_Rate << endl;
		// cout << "BOSS_jsonValue Scream_Range : " << m_Scream_Range << endl;
	}
}


cSoulEaterState::~cSoulEaterState()
{
}

void cSoulEaterState::SetDragon(cDragonSoulEater* pDragon)
{
	m_pDragon = pDragon;
}

void cSoulEaterState::TargetCapture()
{
	if (m_pDragon == NULL) return;

	D3DXVECTOR3 pos = m_pDragon->GetPos();

	if (m_pDragon->GetTarget())
	{
		m_vTarget = *m_pDragon->GetTarget();
		m_vDir = m_vTarget - m_pDragon->GetPos();
		//m_vDir.y = 0;
		D3DXMATRIXA16 matR, matRy;
		D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &(m_vTarget - pos), &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixTranspose(&matR, &matR);
		D3DXMatrixRotationY(&matRy, D3DX_PI);
		m_pDragon->SetRotation((D3DXMATRIXA16*)&(matR * matRy));

	}
	//

}
