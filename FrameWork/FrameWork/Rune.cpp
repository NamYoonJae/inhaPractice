#include "stdafx.h"
#include "Rune.h"
#include "cOBB.h"
#include "ObjLoader.h"
#pragma once

cRune::cRune()
{
}


cRune::~cRune()
{
}

void cRune::Setup()
{
	cObjLoader objLoader;
	objLoader.LoadOBJ(m_vecGroup, "data/ObjFile/MapObject/NW_Rune", "Stone.obj");

	std::vector<ST_PNT_VERTEX> list;

	for (int i = 0; i < m_vecGroup.size(); ++i)
	{
		list.insert(list.begin() + list.size(),
			m_vecGroup.at(i)->GetVertex().begin(),
			m_vecGroup.at(i)->GetVertex().end());
	}

	D3DXVECTOR3 vMin, vMax;
	vMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	vMax = D3DXVECTOR3(FLT_MIN, FLT_MIN, FLT_MIN);
	for (int i = 0; i < list.size(); i++)
	{
		vMin.x = min(vMin.x, list.at(i).p.x);
		vMin.y = min(vMin.y, list.at(i).p.y);
		vMin.z = min(vMin.z, list.at(i).p.z);

		vMax.x = max(vMax.x, list.at(i).p.x);
		vMax.y = max(vMax.y, list.at(i).p.y);
		vMax.z = max(vMax.z, list.at(i).p.z);
	}

	m_pOBB = new cOBB;
	m_pOBB->Setup(vMin, vMax);
}

void cRune::Update()
{
	D3DXMATRIXA16 matW;
	D3DXMatrixIdentity(&matW);

	if (m_pOBB)
		m_pOBB->Update(&matW);
}

void cRune::Render(D3DXMATRIXA16 * pmat)
{
	D3DXMATRIXA16 matW;
	D3DXMatrixIdentity(&matW);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);
	for (int i = 0; i < m_vecGroup.size(); ++i)
	{
		m_vecGroup.at(i)->Render();
	}

	if (m_pOBB)
		m_pOBB->OBBBOX_Render(D3DCOLOR_ARGB(255, 255, 255, 0));
}

void cRune::CollisionProcess(cObject * pObject)
{
}
