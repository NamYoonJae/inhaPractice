#include "stdafx.h"
#include "ObjLoader.h"
#include "ObjObject.h"


cObjObject::cObjObject()
	:m_vPos(0, 0, 0)
	,m_vScale(1, 1, 1)
	,m_vRotateAngle(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matTrans);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matWorld);
}


cObjObject::~cObjObject()
{
}

void cObjObject::Setup(char* folder, char* file)
{
	cObjLoader Loader;
	Loader.LoadOBJ(m_vecGroup, folder, file);
}

void cObjObject::Update()
{
	D3DXMatrixScaling(&m_matScale, m_vScale.x, m_vScale.y, m_vScale.z);

	if(m_vRotateAngle.x != 0)
	{
		D3DXMATRIXA16 XRotMat;
		D3DXMatrixIdentity(&XRotMat);
		D3DXMatrixRotationX(&XRotMat, m_vRotateAngle.x);
		m_matRot = XRotMat;
	}
	if (m_vRotateAngle.y != 0)
	{
		D3DXMATRIXA16 YRotMat;
		D3DXMatrixIdentity(&YRotMat);
		D3DXMatrixRotationX(&YRotMat, m_vRotateAngle.y);
		m_matRot *= YRotMat;
	}
	if (m_vRotateAngle.z != 0)
	{
		D3DXMATRIXA16 ZRotMat;
		D3DXMatrixIdentity(&ZRotMat);
		D3DXMatrixRotationX(&ZRotMat, m_vRotateAngle.z);
		m_matRot *= ZRotMat;
	}

	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	m_matWorld = m_matScale * m_matRot * m_matTrans;

	for (int groupNum = 0; groupNum < m_vecGroup.size(); groupNum++)
		for (int i = 0; i < m_vecGroup[groupNum]->GetVertex().size(); i += 3)
		{
			D3DXVec3TransformCoord(&m_vecGroup[groupNum]->GetVertex()[i].p,		&m_vecGroup[groupNum]->GetVertex()[i].p,	&m_matWorld);
			D3DXVec3TransformCoord(&m_vecGroup[groupNum]->GetVertex()[i + 1].p, &m_vecGroup[groupNum]->GetVertex()[i + 1].p, &m_matWorld);
			D3DXVec3TransformCoord(&m_vecGroup[groupNum]->GetVertex()[i + 2].p, &m_vecGroup[groupNum]->GetVertex()[i + 2].p, &m_matWorld);
		}
}

void cObjObject::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	for (auto Unit : m_vecGroup)
	{
		Unit->Render();
	}

	g_pD3DDevice->SetTexture(0, NULL);
}
