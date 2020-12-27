#include "stdafx.h"
#include "SoulEater_Rush.h"
#include "DragonSoulEater.h"
#include "SoundManager.h"
#include "Wall.h"
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
		m_IsRush = true;
	}
	

	D3DXVECTOR3 pos = m_pDragon->GetPos();

	//
	float distance = sqrt(pow(pos.x - m_vTarget.x, 2) + pow(pos.z - m_vTarget.z, 2));

	std::map<int, CollisionInfo> CollisionList = m_pDragon->GetMapCollisionList();

	// ���ε���������
	if (CollisionList.find(Tag::Tag_Wall) != CollisionList.end() &&
		m_IsHitAnything == false)
	{
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Get_Hit);
		m_IsHitAnything = true;
		m_vDir = D3DXVECTOR3(0, 0, 0);
		
		//����ġ�� ���δ�9
		//����ġ �־���ߵ�

		m_pDragon->SetSTUN(m_pDragon->GetSTUN() + m_pDragon->GetWallStunDamage());
		//m_pDragon->SetSTUN(m_pDragon->GetSTUN() + 50.0f);

		m_pDragon->SetRigid(m_pDragon->GetRigid() + m_pDragon->GetWallRigidDamage());
		//m_pDragon->SetRigid(m_pDragon->GetRigid() + 15.0f);
		
		//g_pSoundManager->PlaySFX(eSoundList::Dragon_Collision);

		m_pDragon->HitSound();
		m_pDragon->Request();
		return;
	}

	if (distance <= 30.0f)
	{
		m_pDragon->Request();
		return;
	}
	else
	{
		pos += m_vDir * 0.005f;
		m_pDragon->SetPos(pos);
	}

}
