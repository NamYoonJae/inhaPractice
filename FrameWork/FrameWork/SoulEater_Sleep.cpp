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
}

cSoulEater_Sleep::cSoulEater_Sleep(cDragonSoulEater* pDragon)
	:cSoulEaterState(pDragon)
{
	m_nCurentIndex = 6;
	m_IsSleep = false;
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
					
			pGolem2 = new cLavaGolem;
			pGolem2->SetScale(D3DXVECTOR3(0.2, 0.2, 0.2));
			pGolem2->Setup("data/XFile/LavaGolem", "LavaGolem.X");
			pGolem2->Tagging(Tag::Tag_LavaGolem);
			pGolem1->SetPos(vPos2);
			ObjectManager->AddChild(pGolem2);
			pGolem2->SetMater(this);

			m_nliveGolem = 1;
		}

	}
	else 
	{

		// È¸º¹
		
		//
		if (m_nliveGolem == 0)
		{
			m_pDragon->Request();
			return;
		}
		
	}
	
}
