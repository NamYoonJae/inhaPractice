#pragma once
#include "cObject.h"

class cGroup;
class cOBB;

class cWall : public cObject
{
private:
	vector<cGroup*> m_vecGroup;

	int		m_MaxHP;
	int		m_CurrentHP;

	// ---- 오브젝트 상호작용속성 -----
	int		m_Wall_Stun_Damage; // 벽 충돌시 받는 기절치
	int		m_Wall_Rigid_Damage; // 벽 충돌시 받는 경직치

public:
	cWall();
	~cWall();

	void Setup();
	void Update();
	void Render(D3DXMATRIXA16 * pmat = NULL) override;

	void CollisionProcess(cObject* pObject) override;
};

