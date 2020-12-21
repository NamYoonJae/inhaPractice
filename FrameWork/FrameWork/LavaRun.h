#pragma once
#include "LavaState.h"
class cLavaRun :
	public cLavaState
{
private:
	bool m_IsAnimBlend;

public:
	cLavaRun(cLavaGolem* pLavaGolem);
	~cLavaRun();
	virtual void Handle() override;
};

