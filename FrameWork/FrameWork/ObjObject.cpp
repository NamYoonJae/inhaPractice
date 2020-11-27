#include "stdafx.h"
#include "ObjLoader.h"
#include "ObjObject.h"


cObjDefault::cObjDefault()
	:m_vPos(0, 0, 0)
	,m_vScale(1, 1, 1)
	,m_vRotateAngle(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matTrans);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matWorld);
}


cObjDefault::~cObjDefault()
{
}

void cObjDefault::Update()
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
}


cObjObject::cObjObject()
{
}

cObjObject::~cObjObject()
{
	for (auto group : m_vecGroup)
	{
		SafeDelete(group);
	}
	m_vecGroup.clear();
}

void cObjObject::Setup(string folder, string file)
{
	Setup(folder.c_str(), file.c_str());
}

void cObjObject::Setup(const char* folder, const char* file)
{
	cObjLoader Loader;
	Loader.LoadOBJ(m_vecGroup, folder, file);
}

void cObjObject::Update()
{
	cObjDefault::Update();
	
	for (int groupNum = 0; groupNum < m_vecGroup.size(); groupNum++)
		for (int i = 0; i < m_vecGroup[groupNum]->GetVertex().size(); i ++)
		{
			D3DXVec3TransformCoord(&m_vecGroup[groupNum]->GetVertex()[i].p, &m_vecGroup[groupNum]->GetVertex()[i].p, &m_matWorld);
			//D3DXVec3TransformCoord(&m_vecGroup[groupNum]->GetVertex()[i + 1].p, &m_vecGroup[groupNum]->GetVertex()[i + 1].p, &m_matWorld);
			//D3DXVec3TransformCoord(&m_vecGroup[groupNum]->GetVertex()[i + 2].p, &m_vecGroup[groupNum]->GetVertex()[i + 2].p, &m_matWorld);
		}
}

void cObjObject::Render(D3DXMATRIXA16* pmat)
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	for (auto group : m_vecGroup)
	{
		group->Render();
	}

	g_pD3DDevice->SetTexture(0, NULL);
}

cObjMesh::cObjMesh()
	:m_Mesh(nullptr)
{
}

cObjMesh::~cObjMesh()
{
	SafeDelete(m_Mesh);
}

void cObjMesh::Setup(string folder, string file)
{
	Setup(folder.c_str(), file.c_str());
}

void cObjMesh::Setup(const char* folder, const char* file)
{
	cObjLoader Loader;
	m_Mesh = Loader.LoadMeshOBJ(m_vecMtlTex, folder, file);
}

void cObjMesh::Render(D3DXMATRIXA16* pmat)
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	for (size_t i = 0; i < m_vecMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMaterial());
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
		
		m_Mesh->DrawSubset(i);
		
		g_pD3DDevice->SetTexture(0, NULL);
	}
}
