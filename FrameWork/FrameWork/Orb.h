#pragma once
#include "cObject.h"

class cGroup;
class cOBB;
class cOrb : public cObject
{
private:
	vector<cGroup*> m_vecGroup;
	LPDIRECT3DTEXTURE9 m_pTex0;
public:
	cOrb();
	~cOrb();

	void Setup();
	void Update();
	void Render(D3DXMATRIXA16 * pmat = NULL) override;

	void CollisionProcess(cObject* pObject);
};

