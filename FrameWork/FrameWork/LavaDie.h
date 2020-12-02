#pragma once
#include "LavaState.h"
class cLavaDie :
	public cLavaState
{
public:
	cLavaDie(cLavaGolem* pLavaGolem);
	~cLavaDie();
	virtual void Handle() override {};
};

