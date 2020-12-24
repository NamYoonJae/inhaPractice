#include "stdafx.h"
#include "LavaRun.h"
#include "LavaGolem.h"
#include "jsonManager.h"

#pragma once
cLavaRun::cLavaRun(cLavaGolem* pLavaGolem)
	:cLavaState(pLavaGolem)
{
	m_nStateIndex = 1;
	m_IsAnimBlend = false;
	TargetChange();
}


cLavaRun::~cLavaRun()
{
}

void cLavaRun::Handle()
{
	if (m_pGolem)
	{

		{
			D3DXVECTOR3 vPos = m_pGolem->GetPos();
			//vPos += m_vDirection * 0.2f;
			vPos += m_vDirection * json_Function::object_get_double(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/Sub Monster/Move Speed");
			m_pGolem->SetPos(vPos);
		}

		if(&m_pGolem->GetSkinnedMesh() && m_IsAnimBlend == false)
		{
			LPD3DXANIMATIONCONTROLLER pAnimController = m_pGolem->GetSkinnedMesh().GetAnimationController();
			LPD3DXANIMATIONSET pCurAnimSet = NULL;
			pAnimController->GetTrackAnimationSet(0, &pCurAnimSet);
			if (GetTickCount() - m_pGolem->GetSkinnedMesh().GetAnimStartTime()
				 > pCurAnimSet->GetPeriod() * 1000.0f - m_pGolem->GetSkinnedMesh().GetBlendTime() * 1000.0f)
			{
				//m_pGolem->GetSkinnedMesh().SetAnimationIndexBlend(0);
				//m_pGolem->GetSkinnedMesh().SetAnimationIndex(0);

				//cSkinnedMesh& pCurrentMesh = m_pGolem->GetSkinnedMesh();
				cSkinnedMesh* pNextMesh = m_pGolem->GetRun();
				//pCurrentMesh = *pNextMesh;
				m_pGolem->SetSkinnedMesh(pNextMesh);
				
				m_IsAnimBlend = true;
			}
		}
		
		float dist = sqrt(pow(m_pGolem->GetPos().x - m_vTarget.x, 2)
			+ pow(m_pGolem->GetPos().z - m_vTarget.z, 2));

		if (m_IsAnimBlend && dist < Distance)
		{
			m_pGolem->Request(2);
			return;
			
		}
	}
}

void cLavaRun::TargetChange()
{
	if (m_pGolem)
	{
		m_vTarget = *m_pGolem->GetTarget();
		m_vDirection = m_vTarget - m_pGolem->GetPos();
		D3DXVec3Normalize(&m_vDirection, &m_vDirection);
	}
}
