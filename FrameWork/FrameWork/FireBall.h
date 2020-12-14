#include "cObject.h"
#pragma once
class cFireBall : public cObject
{
private:
	LPD3DXMESH		m_pMesh;
	std::vector<D3DMATERIAL9> m_vecMtls;
	
	LPDIRECT3DTEXTURE9 m_pTex;
	LPD3DXEFFECT	m_pShader;

	LPDIRECT3DTEXTURE9 m_pTexcoord;
	LPDIRECT3DTEXTURE9 m_pParticle;

	// 
	std::vector<ST_PC_VERTEX>		m_vecVertexParticle;
	std::vector<ST_PC_VERTEX>		m_FlowParticle;

public:
	cFireBall();
	~cFireBall();
	void Setup();
	void Update() override;
	void Render(D3DXMATRIXA16 *pmat = NULL) override;
	void ParticleRender();
	void SetEFFECT(LPD3DXEFFECT shader) { m_pShader = shader; }
	//void SetDir(D3DXVECTOR3 dir) { m_vDir = dir; }
	//void SetPos(D3DXVECTOR3 Pos) { m_vPos = Pos; }
};
