#pragma once
#include "cObject.h"

class cGroup;
class cOBB;

class cRune : public cObject
{
private:
	vector<cGroup*> m_vecGroup;

	cOBB* m_pSubOBB;

	bool m_OnOff;
	float m_RotY;
	DWORD m_dwPreparationTime;
	DWORD m_dwStateStartTime;

public:
	cRune();
	~cRune();

	void Setup();
	void Update();
	void Render(D3DXMATRIXA16 * pmat = NULL) override;

	void CollisionProcess(cObject* pObject);
	cOBB* GetSubOBB() { return m_pSubOBB; }
	void SetOnOff(bool state) { m_OnOff = state; };
};

