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

	// ---- ������Ʈ ��ȣ�ۿ�Ӽ� -----
	int		m_Wall_Stun_Damage; // �� �浹�� �޴� ����ġ
	int		m_Wall_Rigid_Damage; // �� �浹�� �޴� ����ġ

public:
	cWall();
	~cWall();

	void Setup();
	void Update();
	void Render(D3DXMATRIXA16 * pmat = NULL) override;

	void CollisionProcess(cObject* pObject) override;
};

