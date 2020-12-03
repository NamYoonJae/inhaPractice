#pragma once
#include "cObject.h"

class cSkinnedMesh;
class cLavaState;

class cLavaGolem :
	public cObject
{
private:
	cSkinnedMesh* m_pSkinnedMesh;
	cLavaState* m_pState;
	D3DMATERIAL9	m_Mstl;

	D3DXVECTOR3* m_pvTarget;

	float		m_fCurrentHP;
	float		m_fMaxHP;

	float		m_fDist;
	D3DXMATRIXA16 m_matR;
public:
	cLavaGolem();
	~cLavaGolem();
	
	void Setup(char* szFolder, char* szFileName);
	virtual void Update() override;
	virtual void Render(D3DXMATRIXA16 *pmat = 0) override;

	void Request(int state);
	cSkinnedMesh& GetSkinnedMesh() { return *m_pSkinnedMesh; }

	float GetCurrentHP() { return m_fCurrentHP; }
	D3DXVECTOR3* GetTarget() { return m_pvTarget; }
	float GetDist() { return m_fDist; }
	D3DXMATRIXA16* GetRotationMatrix() { return &m_matR; };
	void	SetRotationMatrix(D3DXMATRIXA16* mat) { m_matR = *mat; }
};

// ���� �̵� ���� IDLE

// attack move die

