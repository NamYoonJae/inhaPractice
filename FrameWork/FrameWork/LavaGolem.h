#include "cObject.h"
#include "SoundManager.h"

#pragma once

class cSkinnedMesh;
class cLavaState;

class cLavaGolem :
	public cObject
{
private:
	cSkinnedMesh* m_pSkinnedMesh;
	cLavaState* m_pState;
	D3DMATERIAL9	m_Mstl;

	D3DXVECTOR3* m_pvTarget;


	float		m_fDist;
	D3DXMATRIXA16 m_matR;


	float		m_fCurrentHP;
	float		m_fMaxHP;
	float		m_fDamege;

	bool		m_IsDead;
	float		m_fAttackReach;
	float		m_fSpeed;

	Synthesize(cSkinnedMesh*, m_pMg_Attack,Attack);
	Synthesize(cSkinnedMesh*, m_pMg_Die, Die);
	Synthesize(cSkinnedMesh*, m_pMg_Run, Run);
	Synthesize(bool, m_IsAttack, IsAttack);
public:
	cLavaGolem();
	~cLavaGolem();
	
	void Setup();
	virtual void Update() override;
	virtual void Render(D3DXMATRIXA16 *pmat = 0) override;

	void Request(int state);
	cSkinnedMesh& GetSkinnedMesh() { return *m_pSkinnedMesh; }
	void SetSkinnedMesh(cSkinnedMesh* pMesh) { m_pSkinnedMesh = pMesh; }
	float GetCurrentHP() { return m_fCurrentHP; }
	void SetCurrentHP(float argument) { m_fCurrentHP = argument; }
	D3DXVECTOR3* GetTarget() { return m_pvTarget; }
	float GetDist() { return m_fDist; }
	D3DXMATRIXA16* GetRotationMatrix() { return &m_matR; };
	void	SetRotationMatrix(D3DXMATRIXA16* mat) { m_matR = *mat; }
	int		GetStateIndex();
	virtual void CollisionProcess(cObject* pObject) override;
	void AddCollisionInfo(
		int nTag, CollisionInfo Info,
		float fDMG, bool bDamageType,
		float fStunDamage, float fRigidDamage);
	void HitSound() override;
};

// 공격 이동 죽음 IDLE

// attack move die

