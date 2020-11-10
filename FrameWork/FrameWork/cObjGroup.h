#pragma once
#include "cObject.h"
class cObjGroup :
	public cObject
{
private:
	std::vector<cObject*> cObjList;
	D3DXVECTOR3			  m_vPos;
	D3DXVECTOR3			  m_vRot;
public:
	cObjGroup();
	~cObjGroup();
	virtual void Update() override;
	virtual void Render(D3DXMATRIXA16 * pmat = NULL) override;
	void	addChild(cObject* cChild);
	void	removeChild(cObject& cChild);
};

