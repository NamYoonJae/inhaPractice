#include "stdafx.h"
#include "LavaIdle.h"
#pragma once

cLavaIdle::cLavaIdle(cLavaGolem* pLavaGolem)
	:cLavaState(pLavaGolem)
	, m_dwElapsedTime(GetTickCount())
{
	m_nStateIndex = 0;

	//cSkinnedMesh& pCurrentMesh = m_pGolem->GetSkinnedMesh();
	cSkinnedMesh* pNextMesh = m_pGolem->GetRun();
	//pCurrentMesh = *pNextMesh;
	m_pGolem->SetSkinnedMesh(pNextMesh);
}


cLavaIdle::~cLavaIdle()
{
}

void cLavaIdle::Handle()
{
	if (GetTickCount() - m_dwElapsedTime >= 1000.0f &&
		m_pGolem->GetTarget())
	{
		if (m_pGolem->GetDist() < Distance)
		{
			m_pGolem->Request(2);	
			return;
		}
		else 
		{
			m_pGolem->Request(1);
			return;
		}
	}	
}
