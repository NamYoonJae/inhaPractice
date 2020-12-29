#pragma once

class cSwampA : public cObject
{
private:
	LPD3DXMESH		m_pMesh;
	LPD3DXEFFECT	m_pShader;
	std::vector<D3DMATERIAL9> m_vecMtl;
	LPDIRECT3DTEXTURE9  m_pTexcoord;
	LPDIRECT3DTEXTURE9  m_pTexcoord_B;
	LPDIRECT3DTEXTURE9	m_pNoise;
	LPDIRECT3DTEXTURE9 m_pTex0;

	DWORD m_dwElapsedTime;
	Synthesize(DWORD, m_dwDurationTime, Duration);


	// 보스의 공격력
	float				m_fPhysicDamage;
	float				m_fElementalDamage;
	// 장판 // 패턴 3
	float				m_Flood_Physic_Rate;
	float				m_Flood_Elemental_Rate;
	string				m_Flood_Condition; // 상태이상 부여 종류
	float				m_Flood_Condition_Rate; // 상태이상 부여

public:
	cSwampA();
	~cSwampA();
public:
	void SetEFFECT(LPD3DXEFFECT shader) { m_pShader = shader; }
	void Setup(Tag);
	void Update();
	void Render(D3DXMATRIXA16 *pmat = NULL);
	void CollisionProcess(cObject* pObject) override;
};

