#include "stdafx.h"
#include "LavaState.h"


cLavaState::cLavaState(cLavaGolem* pLavaGolem)
{
	m_pGolem = pLavaGolem;
	m_dwAnimStartTime = 0.0f;
	m_dwBlendTime = 0.3f;
	m_nStateIndex = 99;
}


cLavaState::~cLavaState()
{
}
