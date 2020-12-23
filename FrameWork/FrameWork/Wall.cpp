#include "stdafx.h"
#include "Wall.h"
#include "cOBB.h"
#include "ObjLoader.h"
#include "DragonSoulEater.h"
#include "jsonManager.h"
#pragma once

cWall::cWall()
	: m_MaxHP(3)
	, m_CurrentHP(3)
{
}

cWall::~cWall()
{
}

void cWall::Setup()
{
#pragma region json
	JSON_Object* pStageBObject = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* pWallObject = json_Function::object_get_object(pStageBObject, "Stage B/Object/1/");

	m_MaxHP = m_CurrentHP = (int)json_Function::object_get_double(pWallObject, "Status/Earth HP");

	// log
	cout << "Wall MAX HP : " << m_MaxHP << endl;
#pragma endregion json


	//임시적인 위치
	m_vPos = D3DXVECTOR3(220.0f, 0.0f, 100.0f);

	cObjLoader objLoader;
	objLoader.LoadOBJ(m_vecGroup, "data/ObjFile/MapObject/NW_WALL", "Wall.obj");

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
	/*
	for (int i = 0; i < m_vecGroup.size(); ++i)
	{
		vector<ST_PNT_VERTEX> Group = m_vecGroup.at(i)->GetVertex();
		for (int j = 0; j < m_vecGroup.at(i)->GetVertex().size(); ++j)
		{
			Group.at(j).t.y = 1 - Group.at(j).t.y;
		}

		m_vecGroup.at(i)->SetVertices(Group);
	}
	*/
	m_pOBB = new cOBB;
	m_pOBB->Setup(vMin, vMax);
}

void cWall::Update()
{
	D3DXMATRIXA16 matW, matT, matS;;
	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matW = matS * matT;

	if (m_pOBB)
		m_pOBB->Update(&matW);
}

void cWall::Render(D3DXMATRIXA16 * pmat)
{
	D3DXMATRIXA16 matW, matT, matS;

	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matW = matS * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);

	for (int i = 0; i < m_vecGroup.size(); ++i)
	{
		m_vecGroup.at(i)->Render();
	}

	if (m_pOBB)
		m_pOBB->OBBBOX_Render(D3DCOLOR_ARGB(255, 255, 255, 0));
}

void cWall::CollisionProcess(cObject * pObject)
{
	int nTag = pObject->GetTag();

	if(nTag == Tag::Tag_Boss && pObject->GetCollsionInfo(m_nTag) == nullptr)
	{
		cDragonSoulEater* pDragon = (cDragonSoulEater*)pObject;
		if(pDragon->CurrentStateIndex() == 3)
		{
			CollisionInfo info;
			info.dwCollsionTime = GetTickCount();
			info.dwDelayTime = 1500;
			pObject->AddCollisionInfo(m_nTag, info);
			//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "Dragon Wall hit");
		}
	}
	
	
}
