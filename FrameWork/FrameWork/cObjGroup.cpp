#include "stdafx.h"
#include "cObjGroup.h"


cObjGroup::cObjGroup()
	:m_vPos(0,0,0)
	,m_vRot(0,0,0)
{
}


cObjGroup::~cObjGroup()
{
}

void cObjGroup::Update()
{
	// this update

	for (int i = 0; i < cObjList.size(); i++)
		cObjList[i]->Update();
}

void cObjGroup::Render(D3DXMATRIXA16* pmat)
{
	D3DXMATRIXA16 matWorld, matT, matR,
				  matRx, matRy, matRz;

	D3DXMatrixIdentity(&matWorld);

	// rotation , position
	D3DXMatrixRotationX(&matRx, m_vRot.x);
	D3DXMatrixRotationY(&matRy, m_vRot.y);
	D3DXMatrixRotationZ(&matRz, m_vRot.z);

	matR = matRx * matRy * matRz;
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	
	matWorld = matR * matT;
	if(pmat)
	{
		matWorld *= *pmat;
	}

	for(int i = 0; i < cObjList.size(); i++)
	{
		cObjList[i]->Render(&matWorld);
	}
	
}

void cObjGroup::addChild(cObject* cChild)
{
	cObjList.push_back(cChild);
}

void cObjGroup::removeChild(cObject& cChild)
{
	cObjList.erase(remove(cObjList.begin(),
		cObjList.end(), &cChild));
}
