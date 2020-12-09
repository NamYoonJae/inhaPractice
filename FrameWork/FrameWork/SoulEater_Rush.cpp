#include "stdafx.h"
#include "SoulEater_Rush.h"
#include "DragonSoulEater.h"

#pragma once

cSoulEater_Rush::cSoulEater_Rush()
	: m_IsHitAnything(false)
{
}

cSoulEater_Rush::cSoulEater_Rush(cDragonSoulEater *pDragon)
	: cSoulEaterState(pDragon)
	, m_IsHitAnything(false)
{
	m_nCurentIndex = 3;
}

cSoulEater_Rush::~cSoulEater_Rush()
{
}

void cSoulEater_Rush::handle()
{
	if (m_pDragon == NULL) return;

	if (m_vTarget == D3DXVECTOR3(0, 0, 0))
	{
		TargetCapture();
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Run);
	}

	D3DXVECTOR3 pos = m_pDragon->GetPos();

	//
	float distance = sqrt(pow(pos.x - m_vTarget.x, 2) + pow(pos.z - m_vTarget.z, 2));

	std::map<int, CollisionInfo> CollisionList = m_pDragon->GetMapCollisionList();

	// ·é½ºÅæ 
	if (CollisionList.find(Tag::Tag_RunStone) != CollisionList.end() &&
		m_IsHitAnything == false)
	{
		m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Get_Hit);
		m_IsHitAnything = true;
		m_vDir = D3DXVECTOR3(0, 0, 0);
		//½ºÅÏÄ¡ ³Ö¾îÁà¾ßµÇ
	}
	else if (m_IsHitAnything)
	{
		m_pDragon->Request();
		return;
	}

	if (distance <= 10.0f)
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
