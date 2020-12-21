#include "stdafx.h"
#include "SoulEater_BasicAttack.h"
#include "DragonSoulEater.h"
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
}

cSoulEater_BasicAttack::cSoulEater_BasicAttack(cDragonSoulEater *pDragon)
	: cSoulEaterState(pDragon)
	, m_IsAnimBlend(false)
	, m_IsRun(false)
	, m_dwSoundTime(500.0f)
{
	m_nCurentIndex = 1;
	m_dwElapsedTime = GetTickCount();
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
	float distance = sqrt(pow(pos.x - m_vTarget.x, 2) + pow(pos.z - m_vTarget.z, 2));
	
	if (distance <= 30.0f)
	{
		if (!m_IsAnimBlend)
		{
			m_pDragon->GetSkinnedMesh().SetAnimationIndexBlend(AnimationSet::Basic_Attack);
			g_pSoundManager->PlaySFX((int)eSoundList::Dragon_BasicAttack);
			m_dwElapsedTime = GetTickCount();
			m_IsAnimBlend = true;
			m_IsRun = false;
		}
		else if(GetTickCount() - m_dwElapsedTime >= 500.0f && m_IsAnimBlend)
		{
			m_pDragon->Request();
			return;
		}
	}
	else
	{
		pos += m_vDir * 0.003f;
		m_pDragon->SetPos(pos);
		//GenerateRandomNum(
	}
	
	if (GetTickCount() - m_dwElapsedTime >= m_dwSoundTime && m_IsRun)
	{
		g_pSoundManager->PlaySFX(GenerateRandomNum((int)eSoundList::Dragon_Move0, (int)eSoundList::Dragon_Move9));
		m_dwElapsedTime = GetTickCount();
	}
}
