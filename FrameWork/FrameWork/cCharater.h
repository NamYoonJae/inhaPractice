#pragma once
#include "cObject.h"
#include "Observer.h"
class cCharater :
	public cObject,public cObserver
{
private:
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vRot;

	D3DMATERIAL9	m_Mstl;
	LPD3DXMESH		m_pMesh;
public:
	cCharater();
	~cCharater();
	void Setup();
	virtual void cObserver::Update(string) override;
	virtual void cObject::Update() override {};
	virtual void Render(D3DXMATRIXA16 * pmat = NULL) override;
	D3DXVECTOR3 GetPosition() { return m_vPos; };
};

