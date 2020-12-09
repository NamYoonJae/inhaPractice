#include "stdafx.h"
#include "SoulEater_Rush.h"
#include "DragonSoulEater.h"

#pragma once

cSoulEater_Rush::cSoulEater_Rush()
{
}

cSoulEater_Rush::cSoulEater_Rush(cDragonSoulEater *pDragon)
	:cSoulEaterState(pDragon)
{
	m_nCurentIndex = 3;
}

cSoulEater_Rush::~cSoulEater_Rush()
{
}
