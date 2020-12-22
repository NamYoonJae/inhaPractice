#pragma once
#include "LavaGolem.h"
#include "SkinnedMesh.h"
#include "TimerManager.h"
#include "LavaGolem.h"
#include "SoundManager.h"
#define Distance 15.0f

class cLavaState
{
protected:
	cLavaGolem* m_pGolem;
	DWORD		m_dwAnimStartTime;
	DWORD		m_dwBlendTime;
	int			m_nStateIndex;
public:
	cLavaState(cLavaGolem*);
	~cLavaState();

	virtual void Handle() = 0;
	int GetStateIndex() { return m_nStateIndex; }
};

#include "LavaAttack.h"
#include "LavaDie.h"
#include "LavaRun.h"
#include "LavaIdle.h"