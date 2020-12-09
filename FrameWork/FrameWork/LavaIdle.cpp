#include "stdafx.h"
#include "LavaIdle.h"
#pragma once

cLavaIdle::cLavaIdle(cLavaGolem* pLavaGolem)
	:cLavaState(pLavaGolem)
	, m_dwElapsedTime(GetTickCount())
{
	m_nStateIndex = 0;
}


cLavaIdle::~cLavaIdle()
{
}

void cLavaIdle::Handle()
{
	DWORD dwCurrentTime = GetTickCount();
	if (dwCurrentTime - m_dwElapsedTime >= 1500.0f&&
		m_pGolem->GetTarget())
	{
		if (m_pGolem->GetDist() < 10.0f)
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
