#include "stdafx.h"
#include "SoulEaterState.h"
#include "DragonSoulEater.h"

#pragma once

cSoulEaterState::cSoulEaterState()
{
}

cSoulEaterState::cSoulEaterState(cDragonSoulEater *pDragon)
{
	m_pDragon = pDragon;
}


cSoulEaterState::~cSoulEaterState()
{
}

void cSoulEaterState::GetDragon(cDragonSoulEater* pDragon)
{
	m_pDragon = pDragon;
}
