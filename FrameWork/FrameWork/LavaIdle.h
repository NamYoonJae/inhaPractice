#pragma once
#include "LavaState.h"
class cLavaIdle :
	public cLavaState
{
private:
	DWORD m_ElapsedTime;
public:
	cLavaIdle(cLavaGolem*);
	~cLavaIdle();
	virtual void Handle() override;
};

