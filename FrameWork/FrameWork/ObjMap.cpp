#include "stdafx.h"
#include "ObjMap.h"
#include "ObjLoader.h"
#pragma once

cObjMap::cObjMap(string folder, string file)
	:iMap()
{
	cObjLoader objLoader;
	objLoader.LoadOBJ(m_vecGroup,folder.c_str(), file.c_str());
}

cObjMap::~cObjMap()
{
}

float cObjMap::getHeight(D3DXVECTOR3 pos)
{
	
	
	return 0.0f;
}

void cObjMap::Render(D3DXMATRIXA16 * pmat)
{
	D3DXMATRIXA16 matW,matS,matR, matT;
	D3DXMatrixScaling(&matS,m_vScale.x,m_vScale.y,m_vScale.z);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matW = matS * matR * matT;
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);
	for (int i = 0; i < m_vecGroup.size(); ++i)
		m_vecGroup[i]->Render();

	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, true);
}

void cObjMap::Update()
{
	return;
}

bool cObjMap::CheckInMap(D3DXVECTOR3 pos)
{

	pos.y += 10;
	
	std::vector<ST_PNT_VERTEX> list;
	//IntersectTri
	for(int i = 0; i < m_vecGroup.size(); ++i)
	{
		list.insert(list.end(), 
			m_vecGroup[i]->GetVertices().begin(),
			m_vecGroup[i]->GetVertices().end());
	}

	
	float u, v, t;
	bool check;

	D3DXMATRIXA16  matS;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	
	for(int i = 0; i < list.size();i += 3)
	{
		D3DXVECTOR3 p1, p2, p3;
		p1 = list[i + 0].p;
		p2 = list[i + 1].p;
		p3 = list[i + 2].p;

		D3DXVec3TransformCoord(&p1, &p1, &matS);
		D3DXVec3TransformCoord(&p2, &p2, &matS);
		D3DXVec3TransformCoord(&p3, &p3, &matS);

		
		check = D3DXIntersectTri(&p1, &p2, &p3, &pos, &D3DXVECTOR3(0, -1, 0), &u, &v, &t);

		if(check)
		{
			return true;
		}
	}

	
	return false;
}
