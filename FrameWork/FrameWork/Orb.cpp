#include "stdafx.h"
#include "Orb.h"
#include "cOBB.h"
#include "ObjLoader.h"
#include "Paladin.h"
#include "jsonManager.h"
#pragma once

cOrb::cOrb()
	: m_pTex0(NULL)
	, m_RotY(0.0f)
	, m_dwStateStartTime(GetTickCount())
	, m_dwPreparationTime(1000.0f)
	, m_Holdingtime(10000.f)
{
	m_nTag = Tag::Tag_Orb;
}


cOrb::~cOrb()
{
	SafeRelease(m_pTex0);
}

void cOrb::Setup()
{
#pragma region json
	JSON_Object* pStageBObject = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* pOrbObject = json_Function::object_get_object(pStageBObject, "Stage B/Object/4/");

	m_Holdingtime = json_Function::object_get_double(pOrbObject, "Status/Holding time");

	// log
	cout << "Obb jsonValue  Holding time : " << m_Holdingtime << endl;
#pragma endregion json


	//임시적인 위치
	m_vPos = D3DXVECTOR3(80.0f, 15.0f, 0);


	D3DXCreateTextureFromFile(g_pD3DDevice, L"data/ObjFile/MapObject/NW_ORB/shield_life.png", &m_pTex0);
	cObjLoader objLoader;
	objLoader.LoadOBJ(m_vecGroup, "data/ObjFile/MapObject/NW_ORB", "ORB.obj");

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
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXVec3TransformCoord(&vMin, &vMin, &matS);
	D3DXVec3TransformCoord(&vMax, &vMax, &matS);
	m_pOBB = new cOBB;
	m_pOBB->Setup(vMin,vMax);
	
	//m_pSubOBB = new cOBB;
	//m_pSubOBB->Setup(vMin, vMax);
}

void cOrb::Update()
{
	D3DXMATRIXA16 matW, matS, matR, matT;
	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);

	/*
	matW = matR * matT;

	if (m_pOBB)
		m_pOBB->Update(&matW);
	*/
	D3DXMatrixRotationY(&matR, m_RotY);

	if (GetTickCount() - m_dwStateStartTime <= m_dwPreparationTime)
	{

		if (m_pOBB)
		{
			//D3DXMATRIXA16 matS;
			//D3DXMatrixIdentity(&matS);
			//D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
			matW = matS * matR * matT;
			m_pOBB->Update(&matW);
		}
		
		m_RotY += 1 / D3DX_PI * 0.02;
		m_dwStateStartTime = GetTickCount();
	}
	else
	{
		if (m_pOBB)
		{
			//D3DXMATRIXA16 matS;
			//D3DXMatrixIdentity(&matS);
			//D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
			matW = matS * matT;
			m_pOBB->Update(&matW);
		}
	}
	
	//m_isDelete = true;
	/*
	if (m_pSubOBB)
	{
		D3DXMatrixScaling(&matS, 0.4f,0.4f,0.4f);
		matW = matS *matT;
		m_pSubOBB->Update(&matW);
	}
	*/
}

void cOrb::Render(D3DXMATRIXA16 * pmat)
{
	D3DXMATRIXA16 matW, matT, matS, matR;

	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixRotationY(&matR, m_RotY);
	matW = matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	//g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	
	for (int i = 0; i < 4; i++)
	{
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, 0);
	g_pD3DDevice->SetTextureStageState(3, D3DTSS_TEXCOORDINDEX, 0);

	g_pD3DDevice->SetTexture(1, m_pTex0);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);

	for (int i = 0; i < m_vecGroup.size(); ++i)
	{
		m_vecGroup.at(i)->Render();
	}
	
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTexture(1, NULL);
	g_pD3DDevice->SetTexture(2, NULL);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_RESULTARG, D3DTA_CURRENT);

	for (int i = 0; i < 4; ++i)
	{
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_NONE);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	}

	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	
	if (m_pOBB)
		m_pOBB->OBBBOX_Render(D3DCOLOR_ARGB(255, 255, 255, 0));
	
	/*
	if (m_pSubOBB)
		m_pSubOBB->OBBBOX_Render(D3DCOLOR_ARGB(255, 0, 255, 255));
	*/
}

void cOrb::CollisionProcess(cObject * pObject)
{
	// 나중에
	
	
	int nOtherTag = pObject->GetTag();

	switch(nOtherTag)
	{
		case Tag::Tag_Player:
		{
			
			cPaladin* pPaladin = (cPaladin*)pObject;
			cOBB* pBody = pPaladin->GetPartsList().at(1)->GetOBB();
			if (cOBB::IsCollision(pBody,m_pOBB)
				&& pObject->GetCollsionInfo(m_nTag) == nullptr)
			{
				cout << "오브 충돌" << endl;
				//CollisionInfo info;
				//info.dwCollsionTime = GetTickCount();
				//info.dwDelayTime = 1500.0f;
				//pObject->AddCollisionInfo(m_nTag, info);
			}
			
		}
		break;
	}
	

}
