#pragma once
#include "cObject.h"

class cGroup;
class cOBB;

class cWall : public cObject
{
private:
	vector<cGroup*> m_vecGroup;
public:
	cWall();
	~cWall();

	void Setup();
	void Update();
	void Render(D3DXMATRIXA16 * pmat = NULL) override;

	void CollisionProcess(cObject* pObject) override;
};

