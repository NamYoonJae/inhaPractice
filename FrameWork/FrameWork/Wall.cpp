#include "stdafx.h"
#include "Wall.h"
#include "cOBB.h"
#include "ObjLoader.h"
#include "DragonSoulEater.h"
#include "SoulEaterState.h"
#include "jsonManager.h"
#pragma once

cWall::cWall()
	: m_MaxHP(3)
	, m_CurrentHP(3)
	, m_IsSwitch(true)
{
	m_vScale = D3DXVECTOR3(0.4f, 0.4f, 0.4f);
	m_vPos = D3DXVECTOR3(220.0f, 0.0f, 100.0f);
	m_vRot = D3DXVECTOR3(0, 0, 0);
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

void cWall::Setup(D3DXVECTOR3 Pos)
{
#pragma region json
	JSON_Object* pStageBObject = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* pWallObject = json_Function::object_get_object(pStageBObject, "Stage B/Object/1/");

	m_MaxHP = m_CurrentHP = (int)json_Function::object_get_double(pWallObject, "Status/Earth HP");
#pragma endregion json

	m_vPos = D3DXVECTOR3(Pos.x, Pos.y, Pos.z);
	//m_vScale = Scale;

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
	if (!m_IsSwitch) return;
	D3DXMATRIXA16 matW, matT, matR, matS;
	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, m_vRot.y);
	//D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.x, m_vScale.x);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matW = matS * matR * matT;

	if (m_pOBB)
		m_pOBB->Update(&matW);
}

void cWall::Render(D3DXMATRIXA16 * pmat)
{
	if (!m_IsSwitch) return;
	//CreateShadow();

	D3DXMATRIXA16 matW, matT, matR, matS;

	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, m_vRot.y);
	//D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.x, m_vScale.x);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matW = matS * matR * matT;
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
	return;
}

void cWall::CreateShadow()
{
	D3DLIGHT9  light;
	g_pD3DDevice->GetLight(0, &light);
	D3DXVECTOR4 vDir(light.Direction, 0);

	// 그림자 행렬 만들기.
	D3DXPLANE  plane(0, -1, 0, 0);
	D3DXMATRIXA16   mShadow;
	D3DXMatrixShadow(&mShadow, &vDir, &plane);


	// 그림자 반투명처리.
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_CONSTANT);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_CONSTANT);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_CONSTANT, D3DXCOLOR(0, 0, 0, 0.5f));

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//  스텐실 테스트 옵션 설정. : '0' 인곳에 그린후, 값을 증가 시켜, 중복렌더링을 방지.
	//
	g_pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILREF, 0x00);            //기본값은 0x00
	g_pD3DDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);      //기본값.
	g_pD3DDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);   //기본값.
	g_pD3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);   //성공시, 버퍼의 값을 증가 


	// 기타 옵션.
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	// 그리기..
	D3DXMATRIXA16 _mTM;
	D3DXMATRIXA16 matT, matR, matS;

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.x, m_vScale.x);
	D3DXMatrixRotationY(&matR, m_vRot.y);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	
	_mTM = matS * matR * matT * mShadow;
	//_mTM = matS * matR * matT;
	//_mTM = matS * matT * mShadow;
	//_mTM = mShadow;
	
	for (int i = 0; i < m_vecGroup.size(); ++i)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &_mTM);
		m_vecGroup.at(i)->Render();
	}

	// 옵션 복구.
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, TRUE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
