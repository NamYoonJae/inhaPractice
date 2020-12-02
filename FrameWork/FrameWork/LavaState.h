#pragma once

class cLavaGolem;

class cLavaState
{
protected:
	cLavaGolem* m_pGolem;
	DWORD		m_dwAnimStartTime;
	DWORD		m_dwBlendTime;
public:
	cLavaState(cLavaGolem*);
	~cLavaState();

	virtual void Handle() = 0;
};

#include "LavaAttack.h"
#include "LavaDie.h"
#include "LavaRun.h"
#include "LavaIdle.h"