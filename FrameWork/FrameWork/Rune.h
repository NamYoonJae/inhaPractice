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

	float		m_Rune_Gauge; // << 충전된 게이지 값을 저장할 멤버변수
	float		m_Rune_Gauge_require;
	float		m_Rune_Gauge_recharge;

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

