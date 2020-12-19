#pragma once
#include "cObject.h"

class cGroup;
class cOBB;
class cOrb : public cObject
{
private:
	vector<cGroup*> m_vecGroup;
	cOBB *m_pOBB;
	LPDIRECT3DTEXTURE9 m_pTex0;
	D3DXVECTOR3 m_vPos;
	

public:
	cOrb();
	~cOrb();

	void Setup();
	void Update();
	void Render(D3DXMATRIXA16 * pmat = NULL) override;

	void CollisionProcess(cObject* pObject);
};

