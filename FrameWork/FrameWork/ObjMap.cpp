#include "stdafx.h"
#include "ObjMap.h"
#include "ObjLoader.h"
#pragma once

cObjMap::cObjMap(string folder, string file)
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
	D3DXMatrixScaling(&matS,0.1,1,0.1);
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
