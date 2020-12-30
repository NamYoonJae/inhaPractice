#include "stdafx.h"
#include "SoulEater_Flood.h"
#include "DragonSoulEater.h"
#include "Swamp.h"
#include "ObjectPool.h"
#include "jsonManager.h"
#include "SwampB.h"
#include "ArenaMap.h"
#pragma once


cSoulEater_Flood::cSoulEater_Flood()
{
	m_nCurentIndex = 8;
	m_dwCoolTime = 1000.0f;
	m_dwElapsedTime = 0.0f;
	m_nCntSwamp = 0;
	MapRC = { -500,-800,500,800 };
	m_IsTrigger = false;
}

cSoulEater_Flood::cSoulEater_Flood(cDragonSoulEater* pDragon)
	:cSoulEaterState(pDragon)
{
	m_nCurentIndex = 8;
	m_dwCoolTime = 1000.0f;
	m_dwElapsedTime = 0.0f;
	m_nCntSwamp = 0;
	MapRC = { -500,-500,500,500};
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
			m_IsTrigger = true;
			m_dwElapsedTime = GetTickCount();

			cArenaMap* pMap = (cArenaMap*)ObjectManager->SearchChild(Tag::Tag_Map);
			if (pMap)
			{
				MapRC = pMap->GetAREA();
				MapRC.right = MapRC.right * 0.6;
				MapRC.left = MapRC.left * 0.6;
				MapRC.top = MapRC.top * 0.6;
				MapRC.bottom = MapRC.bottom * 0.6;

			}

		}
	}
	else if(m_IsTrigger && (GetTickCount() -  m_dwElapsedTime >= m_dwCoolTime))
	{
		
		m_dwElapsedTime = GetTickCount();
		random_device rd;
		mt19937_64 gen(rd());
		uniform_real_distribution<> randNumZ((int)MapRC.top, (int)MapRC.bottom);
		uniform_real_distribution<> randNumX((int)MapRC.left, (int)MapRC.right);

		
		D3DXVECTOR3 vec3SwampSize(
			(float)json_Function::object_get_double(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/BOSS SKILL/SKILL 3/Attribute/Radius"),
			0.001f,
			(float)json_Function::object_get_double(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/BOSS SKILL/SKILL 3/Attribute/Radius"));


		for(int i = 0; i < 10; i++)
		{
			D3DXVECTOR3 vPos = D3DXVECTOR3(randNumX(gen), 30, randNumZ(gen));
			g_pLogger->ValueLog(__FUNCTION__,__LINE__,"ff",vPos.x,vPos.z);
			cSwampB *pSwampB = new cSwampB;
			pSwampB->Setup(Tag::Tag_SwampB);
			pSwampB->SetPos(vPos);
			pSwampB->SetDuration(json_Function::object_get_double(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/BOSS SKILL/SKILL 3/Attribute/Duration")); // 장판공격 지속시간 처리
			pSwampB->SetScale(vec3SwampSize);
			
			ObjectManager->AddChild(pSwampB);
		}
			m_nCntSwamp++;
	}

	
	if (m_nCntSwamp > 6)
	{
		m_pDragon->Request();
		return;
	}
	
}
