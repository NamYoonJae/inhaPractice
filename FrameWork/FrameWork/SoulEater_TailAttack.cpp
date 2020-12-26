#include "stdafx.h"
#include "SoulEater_TailAttack.h"
#include "DragonSoulEater.h"
#include "jsonManager.h"

cSoulEater_TailAttack::cSoulEater_TailAttack()
	:cSoulEaterState()
	,m_IsAnimBlend(false)
	, m_IsRun(false)
{
	m_nCurentIndex = 2;
	TargetDistance = 1000.0f;
}
cSoulEater_TailAttack::cSoulEater_TailAttack(cDragonSoulEater* pDragon)
	:cSoulEaterState(pDragon)
	,m_IsAnimBlend(false)
	,m_IsRun(false)
{
	m_nCurentIndex = 2;
	TargetDistance = 1000.0f;

	JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* p_SKILL_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS SKILL/");
	JSON_Object* p_ExtraPattern_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/Extra Pattern/");

	// 꼬리치기 // 패턴 1
	m_TailAttack_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 1/Attribute 2/Melee rate");
	m_TailAttack_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 1/Attribute 2/Elemental rate");

	// log
	cout << "BOSS_jsonValue TailAttack_Physic_Rate : " << m_TailAttack_Physic_Rate << endl;
	cout << "BOSS_jsonValue TailAttack_Elemental_Rate : " << m_TailAttack_Elemental_Rate << endl;
}

cSoulEater_TailAttack::~cSoulEater_TailAttack()
{
}

void cSoulEater_TailAttack::handle()
{
	if (m_pDragon == NULL) return;

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
		m_IsRun = false;

	if(!m_IsRun && !m_IsAnimBlend)
	{
		LPD3DXANIMATIONCONTROLLER pAnimController = m_pDragon->GetSkinnedMesh().GetAnimationController();
		LPD3DXANIMATIONSET pCurAnimSet = NULL;
		pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
		if (GetTickCount() - m_pDragon->GetSkinnedMesh().GetAnimStartTime()
			- pCurAnimSet->GetPeriod() * 1000.0f - m_pDragon->GetSkinnedMesh().GetBlendTime() * 1000.0f)
		{
			if (m_IsAnimBlend == false)
			{
				m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Tail_Attack);
				g_pSoundManager->PlaySFX((int)eSoundList::Dragon_TailAttack);
				m_IsAnimBlend = true;
				m_dwElapsedTime = GetTickCount();
			}
		}
	}
	else if (!m_IsRun && m_IsAnimBlend)
	{
		DWORD dwCurrentTime = GetTickCount();
		if (dwCurrentTime - m_dwElapsedTime >= 1000.0f
			&& m_pDragon->GetTarget())
		{
			m_pDragon->Request();
			return;
		}
	}
	else if (m_IsRun)
	{
		//pos += m_vDir * 0.003f; // 이동
		pos += m_vDir * json_Function::object_get_double(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/BOSS/Move Speed");

		m_pDragon->SetPos(pos);
	}
}
