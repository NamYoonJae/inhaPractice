#include "cObject.h"
#pragma once
class cFireBall : public cObject
{
private:
	bool m_IsExplosion;
	DWORD	m_dwElaspedTime;
	DWORD	m_dwExplosionTime;
	LPD3DXMESH		m_pMesh;
	std::vector<D3DMATERIAL9> m_vecMtls;
	
	LPDIRECT3DTEXTURE9 m_pTex;
	LPD3DXEFFECT	m_pShader;

	LPDIRECT3DTEXTURE9 m_pTexcoord;
	LPDIRECT3DTEXTURE9 m_pParticle;

	// 
	std::vector<ST_PC_VERTEX>		m_vecVertexParticle;
	std::vector<ST_PC_VERTEX>		m_FlowParticle;

	std::vector<ST_PC_VERTEX>		m_ExplosionParticle;
	std::vector<D3DXVECTOR3>		m_ExplosionDir;

	float m_fPhysicDamage;
	float m_fElementalDamage;

	float m_fPhysicRate;
	float m_fElementalRate;

public:
	cFireBall();
	~cFireBall();
	void Setup();
	void Update() override;
	void Render(D3DXMATRIXA16 *pmat = NULL) override;
	void ParticleRender();
	void SetEFFECT(LPD3DXEFFECT shader) { m_pShader = shader; }
	virtual void CollisionProcess(cObject* pObject) override;
	//void SetDir(D3DXVECTOR3 dir) { m_vDir = dir; }
	//void SetPos(D3DXVECTOR3 Pos) { m_vPos = Pos; }
	void Exploding();
};

