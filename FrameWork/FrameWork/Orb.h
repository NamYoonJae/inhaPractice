#pragma once
#include "cObject.h"

class cGroup;
class cOBB;
class cOrb : public cObject
{
private:
	vector<cGroup*> m_vecGroup;
	LPDIRECT3DTEXTURE9 m_pTex0;

	cOBB*		m_pSubOBB;

	bool m_OnOff;
	float m_RotY;
	DWORD m_dwPreparationTime;
	DWORD m_dwStateStartTime;
public:
	cOrb();
	~cOrb();

	void Setup();
	void Update();
	void Render(D3DXMATRIXA16 * pmat = NULL) override;

	void CollisionProcess(cObject* pObject);
	cOBB* GetOBB() { return m_pOBB; };
	cOBB* GetSubOBB() { return m_pSubOBB; };
	void SetOnOff(bool state) { m_OnOff = state; };
};

