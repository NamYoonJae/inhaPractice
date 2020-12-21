#include "stdafx.h"
#include "SoulEater_Sleep.h"
#include "DragonSoulEater.h"
#include "LavaGolem.h"
#include "ObjectPool.h"
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
			D3DXVECTOR3 vPos1, vPos2;
			vPos1 = vPos2 = m_pDragon->GetPos();
			vPos1.x += 150;
			vPos2.x -= 150;
			
			cLavaGolem *pGolem1,*pGolem2;
			pGolem1 = new cLavaGolem;
			pGolem1->SetScale(D3DXVECTOR3(0.2, 0.2, 0.2));
			pGolem1->Setup("data/XFile/LavaGolem", "LavaGolem.X");
			pGolem1->Tagging(Tag::Tag_LavaGolem);
			pGolem1->SetPos(vPos1);
			ObjectManager->AddChild(pGolem1);
			pGolem1->SetMater(this);
					
			//m_nliveGolem = 1;
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
		// È¸º¹
		if(m_pDragon)
		{
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
