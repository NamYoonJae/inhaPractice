#include "stdafx.h"
#include "Rune.h"
#include "cOBB.h"
#include "ObjLoader.h"
#include "Paladin.h"
#include "jsonManager.h"
#include "ObjectPool.h"
#include "Shadow.h"
#include "SoundManager.h"
#pragma once

#define pos_y 20.56f

cRune::cRune()
	: m_OnOff(false)
	, m_RotY(0.0f)
	, m_dwStateStartTime(GetTickCount())
	, m_dwPreparationTime(1000.0f)
	, m_Rune_Gauge(0)
	, m_Rune_Gauge_require(100)
	, m_Rune_Gauge_recharge(20)
	, m_pShadow(NULL)
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
	

	m_pShadow = new cShadow;
	m_pShadow->Setup();
	m_pShadow->SetPos(D3DXVECTOR3(m_vPos.x, pos_y, m_vPos.z));
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

	m_pShadow = new cShadow;
	m_pShadow->Setup();
	m_pShadow->SetPos(D3DXVECTOR3(m_vPos.x, pos_y, m_vPos.z));
}

void cRune::Update()
{
	D3DXMATRIXA16 matW, matT, matS;
	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y + 9.0f, m_vPos.z);

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
		//if (GetTickCount() - m_dwStateStartTime <= m_dwPreparationTime)
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

				D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
				matW = matS * matR * matT;
				m_pSubOBB->Update(&matW);
			}

			m_RotY += 1 / D3DX_PI * 0.03;
			//m_dwStateStartTime = GetTickCount();
		}

		if (m_IsCollision)
		{
			cPaladin* pPaladin = (cPaladin*)ObjectManager->SearchChild(Tag::Tag_Player);
			cOBB* pBody = pPaladin->GetPartsList().at(1)->GetOBB();
			if (!cOBB::IsCollision(pBody, m_pOBB))
			{
				m_IsCollision = false;
				pPaladin->SetInvincible(false);
			}
		}

	}

}

void cRune::Render(D3DXMATRIXA16 * pmat)
{
	//CreateShadow();
	D3DXMATRIXA16 matW,matS, matR, matT;
	D3DXMatrixIdentity(&matW);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y + 9.0f, m_vPos.z);

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

	if (m_pShadow)
	{
		m_pShadow->Render();
	}

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

			//info.dwCollsionTime = GetTickCount();
			//info.dwDelayTime = 1500.0f;
			//pObject->AddCollisionInfo(m_nTag, info);
		}
	}
	break;
	}
}

void cRune::SetOnOff(bool state)
{
	m_OnOff = state;

	if (state == true) 
	{
		string strPath = "data/Sound/SFX/Rune/NW_rune_effect.mp3";
		g_pSoundManager->AddSFX(strPath, (int)Tag_RunStone);
		g_pSoundManager->PlaySFX(Tag_RunStone);
	}


}

void cRune::CreateShadow()
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

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationY(&matR, m_vRot.y);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y-9, m_vPos.z);

	_mTM = matS * matR * matT;
	_mTM *= mShadow;
	//_mTM = matS * matR * matT * mShadow;
	//_mTM = MatrixIdentity * mShadow;
	//_mTM = matT * mShadow;

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
