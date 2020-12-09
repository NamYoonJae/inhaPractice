#pragma once
#include "cObject.h"
#include "Observer.h"
class cCharater :
	public cObject,public cObserver
{
protected:
	D3DMATERIAL9	m_Mstl;
	LPD3DXMESH		m_pMesh;
public:
	cCharater();
	virtual ~cCharater();
	void Setup();
	virtual void cObserver::Update(EventType) override;
	virtual void cObject::Update() override {}

	virtual void Render(D3DXMATRIXA16 * pmat = NULL) override;
	D3DXVECTOR3 GetPosition() { return m_vPos; }
	//D3DXVECTOR3* GetPos() { return &m_vPos; }
	void SetPostiion(D3DXVECTOR3 vec) { m_vPos = vec; }
};

