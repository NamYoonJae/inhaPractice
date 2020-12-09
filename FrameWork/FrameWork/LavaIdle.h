#pragma once
#include "LavaState.h"
class cLavaIdle :
	public cLavaState
{
private:
	DWORD m_dwElapsedTime;
public:
	cLavaIdle(cLavaGolem*);
	~cLavaIdle();
	virtual void Handle() override;
};

