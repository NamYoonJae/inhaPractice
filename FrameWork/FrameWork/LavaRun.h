#pragma once
#include "LavaState.h"
class cLavaRun :
	public cLavaState
{
private:
	bool m_IsAnimBlend;
	D3DXVECTOR3 m_vTarget;
	D3DXVECTOR3 m_vDirection;
public:
	cLavaRun(cLavaGolem* pLavaGolem);
	~cLavaRun();
	virtual void Handle() override;
	void TargetChange();
};

