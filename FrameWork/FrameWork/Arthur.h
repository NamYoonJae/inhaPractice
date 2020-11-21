#pragma once
#include "cCharater.h"
#include "SkinnedMesh.h"

class cBoundingBox;

class cArthur : public cCharater, cSkinnedMesh
{
private:
	cBoundingBox*	m_pOBB;
	float			m_fvelocity;

	D3DXVECTOR3		m_vScale;
	
	D3DXMATRIXA16	m_matScale;
	D3DXMATRIXA16	m_matRot;
	D3DXMATRIXA16	m_matTranse;
	D3DXMATRIXA16	m_matWorld;

	bool			m_isMoving;
// >>
	D3DXMATRIXA16	m_matOBB;
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

