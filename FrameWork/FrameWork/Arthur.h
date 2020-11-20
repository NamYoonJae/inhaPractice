#pragma once
#include "cCharater.h"

class cSkinnedMesh;

class cArthur : public cCharater
{
private:
	cSkinnedMesh*	m_pMesh;

	float			m_fvelocity;

	D3DXVECTOR3		m_vScale;
	
	D3DXMATRIXA16	m_matScale;
	D3DXMATRIXA16	m_matRot;
	D3DXMATRIXA16	m_matTranse;
	D3DXMATRIXA16	m_matWorld;
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

	void SetAnimationController(char* szFolder, char* szFile);
	void SetSkinnedMesh(char* szFolder, char* szFile);
};

