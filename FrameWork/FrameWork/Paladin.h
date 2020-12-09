#pragma once
#include "cCharater.h"

class cSkinnedMesh;
class cPaladinState;
class cPaladinWeapon;

class cPaladin : public cCharater
{
private:
	cSkinnedMesh*	m_pSkinnedUnit;
	float			m_fvelocity;

	D3DXMATRIXA16	m_matScale;
	D3DXMATRIXA16	m_matRot;
	D3DXMATRIXA16	m_matTranse;
	D3DXMATRIXA16	m_matWorld;

	bool			m_isMoving;

	cPaladinState*	m_pCurState;
	DWORD			m_dwDelayState;
	
	cPaladinWeapon* m_pWeapon;
	
	int m_Hp;
	int m_Staminer;
public:
	cPaladin();
	~cPaladin();

	void Setup(char* szFolder, char* szFile);
	void ShaderSetup();
	void Update();
	void Update(EventType event) override;
	void Render(D3DXMATRIXA16 * pmat = NULL);
	void ShaderRender();

	void SetPosition(D3DXVECTOR3 pos) { m_vPos = pos; }
	D3DXVECTOR3 GetPosition() { return m_vPos; }

	cSkinnedMesh* GetSkinnedMesh() { return m_pSkinnedUnit; }

	void CollisionProcess(cObject* pObject, DWORD dwDelayTime) override;
};

class cPaladinWeapon
{
private:
	cOBB*			m_pWeaponOBB;
	Synthesize(D3DCOLOR, m_color, Color);

	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vRot;
	D3DXVECTOR3		m_vScale;

	D3DXMATRIXA16	m_matScale;
	D3DXMATRIXA16	m_matRot;
	D3DXMATRIXA16	m_matTranse;
	D3DXMATRIXA16	m_matWorld;

public:
	cPaladinWeapon();
	~cPaladinWeapon();

	void Setup(D3DXFRAME* pFrame, D3DXMESHCONTAINER* pMesh, D3DXMATRIXA16* pmat);
	void Update(D3DXMATRIXA16* pmat);
	void Render();
};
