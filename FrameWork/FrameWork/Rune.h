#pragma once
#include "cObject.h"

class cGroup;
class cOBB;

class cRune : public cObject
{
private:
	vector<cGroup*> m_vecGroup;

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
};

