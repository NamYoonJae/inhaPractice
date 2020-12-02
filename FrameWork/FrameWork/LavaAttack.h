#pragma once
#include "LavaState.h"
class cLavaAttack :
	public cLavaState
{
private:
public:
	cLavaAttack(cLavaGolem*);
	~cLavaAttack();
	virtual void Handle() override;
};

