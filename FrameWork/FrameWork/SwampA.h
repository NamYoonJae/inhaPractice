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


	// ������ ���ݷ�
	float				m_fPhysicDamage;
	float				m_fElementalDamage;
	// ���� // ���� 3
	float				m_Flood_Physic_Rate;
	float				m_Flood_Elemental_Rate;
	string				m_Flood_Condition; // �����̻� �ο� ����
	float				m_Flood_Condition_Rate; // �����̻� �ο�

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

