#pragma once
#include "cObject.h"

class cGroup;
class cOBB;
class cShadow;

class cRune : public cObject
{
private:
	vector<cGroup*> m_vecGroup;

	cOBB* m_pSubOBB;

	bool m_OnOff;
	bool m_IsCollision;
	float m_RotY;
	DWORD m_dwPreparationTime;
	DWORD m_dwStateStartTime;

	float		m_Rune_Gauge; // << 충전된 게이지 값을 저장할 멤버변수
	float		m_Rune_Gauge_require;
	float		m_Rune_Gauge_recharge;

	cShadow* m_pShadow;

public:
	cRune();
	~cRune();

	void Setup();
	void Setup(D3DXVECTOR3 position); // 오버라이딩 추가
	void Update();
	void Render(D3DXMATRIXA16 * pmat = NULL) override;

	void CollisionProcess(cObject* pObject);
	cOBB* GetSubOBB() { return m_pSubOBB; }
	void SetOnOff(bool state);
	bool GetOnOff() { return m_OnOff; };

};

