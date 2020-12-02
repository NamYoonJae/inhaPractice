#pragma once
#include "LavaState.h"
class cLavaRun :
	public cLavaState
{
private:

public:
	cLavaRun(cLavaGolem* pLavaGolem);
	~cLavaRun();
	virtual void Handle() override;
};

