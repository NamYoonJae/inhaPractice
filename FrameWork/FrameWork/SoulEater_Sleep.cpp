#include "stdafx.h"
#include "SoulEater_Sleep.h"
#include "DragonSoulEater.h"
#include "LavaGolem.h"
#include "ObjectPool.h"
#include "jsonManager.h"

#pragma once

cSoulEater_Sleep::cSoulEater_Sleep()
{
	m_nCurentIndex = 6;
	m_IsSleep = false;
	m_fDamagetaken = 0.0f;
	m_fHealingAmount = 0.0f;
	m_dwHealingCoolTime = 1500.0f;
	m_dwSleepSoundElapsed = GetTickCount();
	m_dwSleepSoundTime = 10000.0f;

}

cSoulEater_Sleep::cSoulEater_Sleep(cDragonSoulEater* pDragon)
	:cSoulEaterState(pDragon)
{
	m_nCurentIndex = 6;
	m_IsSleep = false;
	m_fDamagetaken = 0.0f;
	m_fHealingAmount = 0.0f;
	m_dwHealingCoolTime = 1500.0f;
	m_dwSleepSoundElapsed = GetTickCount();
	m_dwSleepSoundTime = 10000.0f;



	m_dwElapsedTime = GetTickCount();

	// 수면 // 체력회복 패턴
	JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* p_SKILL_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS SKILL/");
	JSON_Object* p_ExtraPattern_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/Extra Pattern/");

	// 수면 // 체력회복 패턴
	m_Sleep_Duration = json_Function::object_get_double(p_ExtraPattern_object, "Sleep/Attribute/Duration");
	// SKILL log
	// cout << "BOSS_jsonValue Sleep_Duration : " << m_Sleep_Duration << endl;
}


cSoulEater_Sleep::~cSoulEater_Sleep()
{
}

void cSoulEater_Sleep::handle()
{
	if (m_pDragon == NULL) return;

	if(!m_IsSleep)
	{
		LPD3DXANIMATIONCONTROLLER pAnimController = m_pDragon->GetSkinnedMesh().GetAnimationController();
		LPD3DXANIMATIONSET pCurAnimSet = NULL;
		pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
		if (GetTickCount() - m_pDragon->GetSkinnedMesh().GetAnimStartTime()
			- pCurAnimSet->GetPeriod() * 1000.0f - m_pDragon->GetSkinnedMesh().GetBlendTime() * 1000.0f)
		{
			m_IsSleep = true;
			m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Sleeping);
			// gelem  create

			vector<cObject*> GolemList;
			ObjectManager->FindAllObjectsWithTag(Tag::Tag_LavaGolem, GolemList);
			if (GolemList.size() < 2)
			{
				D3DXVECTOR3 vGolemPos;
				vGolemPos = D3DXVECTOR3(0, 0, 0);
				cLavaGolem *pGolem;
				pGolem = new cLavaGolem;
				pGolem->SetScale(D3DXVECTOR3(0.2, 0.2, 0.2));
				pGolem->Setup();
				pGolem->Tagging(Tag::Tag_LavaGolem);
				pGolem->SetPos(vGolemPos);
				ObjectManager->AddChild(pGolem);
			}
			m_dwElapsedTime = GetTickCount();
			
			g_pSoundManager->PlaySFX(eSoundList::Dragon_Sleep);
			//m_dwSleepSoundElapsed = GetTickCount();

		}

	}
	else 
	{
		//if (GetTickCount() - m_dwSleepSoundElapsed >= m_dwSleepSoundTime)
		//{
		//	g_pSoundManager->PlaySFX(eSoundList::Dragon_Sleep);
		//	m_dwSleepSoundElapsed = GetTickCount();
		//}

		// 회복
		if(m_pDragon)
		{
			// 최대체력의 10%이하가 될 시 수면에 돌입
			// 수면에 돌입한 후 수면지속시간이 끝났을 때
			// 현재체력이 최대체력의 15%로 변경
			if (m_Sleep_Duration <= GetTickCount() - m_dwElapsedTime)
			{
				m_pDragon->SetCURHP(m_pDragon->GetMAXHP() * 0.15f);
			}

			if(GetTickCount() - m_dwElapsedTime >= m_dwHealingCoolTime)
			{
				m_fHealingAmount += m_pDragon->GetMAXHP() * 0.15 * 0.05;
				m_dwElapsedTime = GetTickCount();

				g_pSoundManager->PlaySFX(eSoundList::Dragon_Sleep);
			}

			if (m_fDamagetaken >= 1500)
			{
				m_pDragon->Request();
				return;
			}
			else if(m_fHealingAmount > m_pDragon->GetMAXHP() * 0.15)
			{
				m_pDragon->Request();
				return;
			}
		}
		
		//		
	}
	
}
