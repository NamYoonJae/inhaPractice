#pragma once
#include "cObject.h"

class cGroup;
class cOBB;

class cRune : public cObject
{
private:
	vector<cGroup*> m_vecGroup;
	cOBB *m_OBB;
	D3DXVECTOR3 m_vPos;


public:
	cRune();
	~cRune();

	void Setup();
	void Update();
	void Render(D3DXMATRIXA16 * pmat = NULL) override;

	void CollisionProcess(cObject* pObject);
};

