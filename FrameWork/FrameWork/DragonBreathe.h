#pragma once
class cDragonBreathe
{
private:
	std::vector<ST_PC_VERTEX> m_vecPosList;
	std::vector<D3DXVECTOR3> m_vecDirList;
	
	LPDIRECT3DTEXTURE9 m_pParticle;
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 *m_pvTarget;
	DWORD	m_dwDuration;
	DWORD	m_dwStartTime;
public:
	cDragonBreathe();
	~cDragonBreathe();
	void SetUp();
	void Update();
	void Render();
	void GetTarget(D3DXVECTOR3* Target) { m_pvTarget = Target; }
};


DWORD FtoDw(float f);
