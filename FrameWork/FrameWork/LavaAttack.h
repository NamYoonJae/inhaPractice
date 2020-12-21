#pragma once
#include "LavaState.h"
class cLavaAttack :
	public cLavaState
{
private:
	bool m_IsAttack;
public:
	cLavaAttack(cLavaGolem*);
	~cLavaAttack();
	virtual void Handle() override;
};

