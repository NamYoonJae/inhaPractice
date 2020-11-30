#pragma once
#include "cCharater.h"
#include "SkinnedMesh.h"

class cBoundingBox;
class cArthurWeapon;

class cArthur : public cCharater, cSkinnedMesh
{
private:
	float			m_fvelocity;

	D3DXVECTOR3		m_vScale;
	
	D3DXMATRIXA16	m_matScale;
	D3DXMATRIXA16	m_matRot;
	D3DXMATRIXA16	m_matTranse;
	D3DXMATRIXA16	m_matWorld;

	bool			m_isMoving;
// >>
	D3DXMATRIXA16	m_matOBB;
	cArthurWeapon*  m_pWeapon;
// <<
public:
	cArthur();
	~cArthur() override;

	void Setup(char* szFolder, char* szFile);
	void Update();
	void Update(EventType event) override;
	void Render(D3DXMATRIXA16 * pmat = NULL);
	  
	void SetTranseform(D3DXMATRIXA16* pmat);
	
	void SetPosition(D3DXVECTOR3 pos) { m_vPos = pos; }
	D3DXVECTOR3 GetPosition() { return m_vPos; }

	void SetScale(D3DXVECTOR3 scale) { m_vScale = scale; }
	D3DXVECTOR3 GetScale() { return m_vScale; }
};

class cArthurWeapon : public cObject
{
private:
// >>
	D3DXMATRIXA16 m_matOBB;
// <<
public:
	cArthurWeapon();
	~cArthurWeapon();

	void Setup(D3DXFRAME* pFrame,
				D3DXMESHCONTAINER* pMesh,
				D3DXMATRIXA16* pmat);
	void Update() {}
	void Update(D3DXMATRIXA16* pmat);
	void Render(D3DXMATRIXA16* pmat) override;
};

