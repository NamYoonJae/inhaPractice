#include "cObject.h"
#pragma once
class cDragonBreathe : public cObject
{
private:
	std::vector<ST_PC_VERTEX> m_vecPosList;
	std::vector<D3DXVECTOR3> m_vecDirList;
	
	LPDIRECT3DTEXTURE9 m_pParticle;
	D3DXVECTOR3 *m_pvTarget;
	DWORD	m_dwStartTime;
	
	Synthesize(DWORD, m_dwDurationTime, DurationTime);
public:
	cDragonBreathe();
	~cDragonBreathe();
	void SetUp(D3DXVECTOR3 vPos = D3DXVECTOR3(0,0,0));
	void Update();
	void Render(D3DXMATRIXA16 *pmat = NULL);
	void GetTarget(D3DXVECTOR3* Target) { m_pvTarget = Target; }
	void CollisionProcess(cObject* pObject) override;
};


DWORD FtoDw(float f);
