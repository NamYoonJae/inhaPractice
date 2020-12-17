#pragma once
#include "cObject.h"

class cGroup;
class cOBB;
class cOrb : public cObject
{
private:
	vector<cGroup*> m_vecGroup;
	cOBB *m_pOBB;

public:
	cOrb();
	~cOrb();

	void Setup();
	void Update();
	void Render(D3DXMATRIXA16 * pmat = NULL) override;

	void CollisionProcess(cObject* pObject);
};

