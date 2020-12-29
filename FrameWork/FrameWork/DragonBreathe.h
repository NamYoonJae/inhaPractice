#include "cObject.h"
#pragma once
class cDragonBreathe : public cObject
{
private:
	std::vector<ST_PC_VERTEX> m_vecPosList;
	std::vector<D3DXVECTOR3> m_vecDirList;
	
	LPDIRECT3DTEXTURE9 m_pParticle;
	D3DXVECTOR3 *m_pvTarget;
	D3DXVECTOR3 *m_pvDragon;
	DWORD	m_dwStartTime;

	float m_fPhysicDamage;
	float m_fElementalDamage;

	float m_fPhysicRate;
	float m_fElementalRate;

	Synthesize(D3DXMATRIXA16*, m_pmatHead, Head);
	Synthesize(DWORD, m_dwDurationTime, DurationTime);

	float  m_fRange;
public:
	cDragonBreathe();
	~cDragonBreathe();
	void Update();
	void Render(D3DXMATRIXA16 *pmat = NULL);
	void SetTarget(D3DXVECTOR3* Target) { m_pvTarget = Target; }
	void SetDragonPos(D3DXVECTOR3* pDragonPos) { m_pvDragon = pDragonPos; }
	void CollisionProcess(cObject* pObject) override;
};


DWORD FtoDw(float f);
