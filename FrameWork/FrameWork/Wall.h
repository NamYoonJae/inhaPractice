#pragma once
#include "cObject.h"

class cGroup;
class cOBB;

class cWall : public cObject
{
private:
	vector<cGroup*> m_vecGroup;

	int		m_MaxHP;
	Synthesize(int, m_CurrentHP, CurHP);


	// ---- ������Ʈ ��ȣ�ۿ�Ӽ� -----
	int		m_Wall_Stun_Damage; // �� �浹�� �޴� ����ġ
	int		m_Wall_Rigid_Damage; // �� �浹�� �޴� ����ġ
	Synthesize(bool, m_IsSwitch, Switch);
public:
	cWall();
		~cWall();

	void Setup();
	void Setup(D3DXVECTOR3 Pos); // �������̵�
	void Update();
	void Render(D3DXMATRIXA16 * pmat = NULL) override;

	void CollisionProcess(cObject* pObject) override;
	void CreateShadow();
};

