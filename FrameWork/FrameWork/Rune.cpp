#include "stdafx.h"
#include "Rune.h"
#include "cOBB.h"
#include "ObjLoader.h"
#include "Paladin.h"
#include "jsonManager.h"
#include "ObjectPool.h"
#pragma once

cRune::cRune()
	: m_OnOff(false)
	, m_RotY(0.0f)
	, m_dwStateStartTime(GetTickCount())
	, m_dwPreparationTime(1000.0f)
	, m_Rune_Gauge(0)
	, m_Rune_Gauge_require(100)
	, m_Rune_Gauge_recharge(20)
{
	m_nTag = Tag::Tag_RunStone;
}


cRune::~cRune()
{
}

void cRune::Setup()
{
#pragma region json
	JSON_Object* pStageBObject = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* pRuneObject = json_Function::object_get_object(pStageBObject, "Stage B/Object/3/");

	m_Rune_Gauge = 0;
	m_Rune_Gauge_require = json_Function::object_get_double(pRuneObject, "Status/Gauge require");
	m_Rune_Gauge_recharge = json_Function::object_get_double(pRuneObject, "Status/Gauge recharge");

	// log
	cout << "Rune Gauge : " << m_Rune_Gauge << endl;
	cout << "Rune jsonValue  Rune require Gauge : " << m_Rune_Gauge_require << endl;
	cout << "Rune jsonValue  Rune recharge Gauge : " << m_Rune_Gauge_recharge << endl;
#pragma endregion json

	//임시적인 위치
	m_vPos = D3DXVECTOR3(150.0f, 10.0f, 0);

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

	for (int i = 0; i < m_vecGroup.size(); ++i)
	{
		vector<ST_PNT_VERTEX> Group = m_vecGroup.at(i)->GetVertex();
		for (int j = 0; j < m_vecGroup.at(i)->GetVertex().size(); ++j)
		{
			Group.at(j).t.y = 1 - Group.at(j).t.y;
		}

		m_vecGroup.at(i)->SetVertices(Group);
	}
	

	m_pSubOBB = new cOBB;
	m_pSubOBB->Setup(vMin, vMax);

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 2.0f, 1.0f, 2.0f);
	D3DXVec3TransformCoord(&vMin, &vMin, &matS);
	D3DXVec3TransformCoord(&vMax, &vMax, &matS);
	m_pOBB = new cOBB;
	m_pOBB->Setup(vMin, vMax);
	
}

void cRune::Setup(D3DXVECTOR3 position)
{
#pragma region json
	JSON_Object* pStageBObject = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* pRuneObject = json_Function::object_get_object(pStageBObject, "Stage B/Object/3/");

	m_Rune_Gauge = 0;
	m_Rune_Gauge_require = json_Function::object_get_double(pRuneObject, "Status/Gauge require");
	m_Rune_Gauge_recharge = json_Function::object_get_double(pRuneObject, "Status/Gauge recharge");
#pragma endregion json
	m_vPos = position;

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

	for (int i = 0; i < m_vecGroup.size(); ++i)
	{
		vector<ST_PNT_VERTEX> Group = m_vecGroup.at(i)->GetVertex();
		for (int j = 0; j < m_vecGroup.at(i)->GetVertex().size(); ++j)
		{
			Group.at(j).t.y = 1 - Group.at(j).t.y;
		}

		m_vecGroup.at(i)->SetVertices(Group);
	}


	m_pSubOBB = new cOBB;
	m_pSubOBB->Setup(vMin, vMax);

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 2.0f, 1.0f, 2.0f);
	D3DXVec3TransformCoord(&vMin, &vMin, &matS);
	D3DXVec3TransformCoord(&vMax, &vMax, &matS);
	m_pOBB = new cOBB;
	m_pOBB->Setup(vMin, vMax);

}

void cRune::Update()
{
	D3DXMATRIXA16 matW, matT, matS;
	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);

	if (m_OnOff == false) 
	{
		if (m_pOBB)
		{
			matW = matT;
			m_pOBB->Update(&matW);
		}

		if (m_pSubOBB)
		{
			D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
			matW = matS * matT;
			m_pSubOBB->Update(&matW);
		}
	}
	else
	{
		if (GetTickCount() - m_dwStateStartTime <= m_dwPreparationTime)
		{
			D3DXMATRIXA16 matR;
			D3DXMatrixIdentity(&matR);
			D3DXMatrixRotationY(&matR, m_RotY);

			if (m_pOBB)
			{
				matW = matR * matT;
				m_pOBB->Update(&matW);
			}

			if (m_pSubOBB)
			{

				D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
				matW = matS * matR * matT;
				m_pSubOBB->Update(&matW);
			}

			m_RotY += 1 / D3DX_PI * 0.03;
			m_dwStateStartTime = GetTickCount();
		}

		if (m_IsCollision)
		{
			cPaladin* pPaladin = (cPaladin*)ObjectManager->SearchChild(Tag::Tag_Player);
			cOBB* pBody = pPaladin->GetPartsList().at(1)->GetOBB();
			if (!cOBB::IsCollision(pBody, m_pOBB))
			{
				m_IsCollision = false;
				pPaladin->SetInvincible(false);
				g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "false Collision");
			}
		}

	}

}

void cRune::Render(D3DXMATRIXA16 * pmat)
{
	D3DXMATRIXA16 matW,matS, matR, matT;
	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);

	if (m_OnOff == false) 
	{
		matW = matS * matT;
	}
	else
	{
		D3DXMatrixRotationY(&matR, m_RotY);
		matW = matS * matR * matT;
	}
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);
	for (int i = 0; i < m_vecGroup.size(); ++i)
	{
		m_vecGroup.at(i)->Render();
	}

	if (m_pOBB)
		m_pOBB->OBBBOX_Render(D3DCOLOR_ARGB(255, 255, 255, 0));

	if (m_pSubOBB)
		m_pSubOBB->OBBBOX_Render(D3DCOLOR_ARGB(255, 0, 255, 255));

}

void cRune::CollisionProcess(cObject * pObject)
{
	if (!m_OnOff) return;

	int nOtherTag = pObject->GetTag();

	switch (nOtherTag)
	{
	case Tag::Tag_Player:
	{
		if (m_IsCollision) return;

		cPaladin* pPaladin = (cPaladin*)pObject;
		cOBB* pBody = pPaladin->GetPartsList().at(1)->GetOBB();
		if (cOBB::IsCollision(pBody, m_pOBB)
			&& pObject->GetCollsionInfo(m_nTag) == nullptr)
		{
			pPaladin->SetInvincible(true);
			m_IsCollision = true;
			g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "true Collision");
			//info.dwCollsionTime = GetTickCount();
			//info.dwDelayTime = 1500.0f;
			//pObject->AddCollisionInfo(m_nTag, info);

		}
	}
	break;
	}
}
