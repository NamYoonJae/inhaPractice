#pragma once
#include "LavaState.h"
class cLavaDie :
	public cLavaState
{
private:
	bool IsDead;
public:
	cLavaDie(cLavaGolem* pLavaGolem);
	~cLavaDie();
	virtual void Handle() override;
};

