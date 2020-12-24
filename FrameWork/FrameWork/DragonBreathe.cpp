#include "stdafx.h"
#include "DragonBreathe.h"
#include <random>
#include <iostream>
#include "FireBall.h"
#include "cOBB.h"

#include "jsonManager.h"
#pragma once

cDragonBreathe::cDragonBreathe()
	:m_dwStartTime(GetTickCount())
	,m_pvTarget(NULL)
	,cObject()
{
	D3DXCreateTextureFromFileA(g_pD3DDevice,
		"data/Texture/alpha_tex.tga", &m_pParticle);
	m_vPos = D3DXVECTOR3(0, 0, 0);

	JSON_Object* p_ROOT_Object = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* p_BOSS_Object = json_Function::object_get_object(p_ROOT_Object, "Stage B/BOSS");

	m_dwDurationTime = 5000.0f; // << json에 추가할것
}


cDragonBreathe::~cDragonBreathe()
{
}

void cDragonBreathe::Update()
{
	if (GetTickCount() - m_dwStartTime > m_dwDurationTime)
	{
		m_isDelete = true;
		return;
	}

	// 드래곤이 충돌했을때 포지션이 바뀌지않는 버그가있는데 수정가능
	if (m_pvTarget)
	{
		D3DXVECTOR3 vTarget = *m_pvTarget;
		vTarget.y += 15.0f;
		D3DXVECTOR3 vDir = vTarget - m_vPos;
		D3DXVec3Normalize(&vDir, &vDir);
		using namespace std;
		random_device rd;
		mt19937_64 mtRand(rd());
		uniform_real_distribution<float> dis(1.0f, 3.0f);

		for (int i = 0; i < 20; i++)
		{
			ST_PC_VERTEX pc;
			float fDist = dis(rd);
			pc.p = D3DXVECTOR3(0, fDist, fDist);
			float RadiusX = D3DXToRadian(rand() % 360);
			float RadiusZ = D3DXToRadian(rand() % 360);
			float RadiusY = D3DXToRadian(rand() % 360);
			D3DXMATRIX matRx,matRz,matRy;
			D3DXMATRIX matWorld;
			D3DXMatrixRotationX(&matRx, RadiusX);
			D3DXMatrixRotationZ(&matRz, RadiusZ);
			D3DXMatrixRotationZ(&matRy, RadiusY);

			matWorld = matRx * matRz * matRy;
			D3DXVec3TransformCoord(
				&pc.p,
				&pc.p,
				&matWorld);

			pc.c = D3DCOLOR_ARGB(255, 255, 0, 0);
			pc.p += (m_vPos + vDir * 2.0f);

			m_vecPosList.push_back(pc);
			m_vecDirList.push_back(vDir);
		}
	}

	D3DXVECTOR3 vMin, vMax;
	vMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	vMax = D3DXVECTOR3(FLT_MIN, FLT_MIN, FLT_MIN);

	for (int i = 0; i < m_vecPosList.size(); ++i)
	{
		m_vecPosList[i].p += m_vecDirList[i] * 2.0f;

		vMin.x = min(vMin.x, m_vecPosList.at(i).p.x);
		vMin.y = min(vMin.y, m_vecPosList.at(i).p.y);
		vMin.z = min(vMin.z, m_vecPosList.at(i).p.z);

		vMax.x = max(vMax.x, m_vecPosList.at(i).p.x);
		vMax.y = max(vMax.y, m_vecPosList.at(i).p.y);
		vMax.z = max(vMax.z, m_vecPosList.at(i).p.z);
	}

	//m_vecPosList[0].p; // << 첫 인덱스
	//m_vecPosList[m_vecPosList.size() - 1)].p; 마지막 인덱스 거리 구해서 지워버리기

	if (m_vecPosList.size() > 50000)
	{
		m_vecPosList.erase(m_vecPosList.begin(), m_vecPosList.begin() + 500);
		m_vecDirList.erase(m_vecDirList.begin(), m_vecDirList.begin() + 500);
	}
	//

	if(m_pOBB != NULL)
	{
		SafeDelete(m_pOBB);
	}

	m_pOBB = new cOBB;
	m_pOBB->Setup(vMin,vMax);
	
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pOBB->Update(&matWorld);
}

void cDragonBreathe::Render(D3DXMATRIXA16 *pmat)
{
	if (GetTickCount() - m_dwStartTime > m_dwDurationTime)
		return;
	else if (m_pvTarget == NULL)
		return;

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(5.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(10.0f));

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0,
		m_pParticle);

	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_POINTLIST,
		m_vecPosList.size(),
		&m_vecPosList[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pD3DDevice->SetTexture(0,
		NULL);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG0, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

	if (m_pOBB)
		m_pOBB->OBBBOX_Render(D3DCOLOR_ARGB(255, 128, 128, 0));
}

void cDragonBreathe::CollisionProcess(cObject* pObject)
{
	int nTag = pObject->GetTag();
	cOBB* pOBB = pObject->GetOBB();
	
	if(nTag == Tag::Tag_RunStone)
	{

		int i = 0;
		std::vector<D3DXVECTOR3> list = pOBB->GetList();
		D3DXMATRIXA16 matWorld = pOBB->GetWorldMatrix();
		D3DXVECTOR3 pos;
		pos.x = matWorld._41; pos.y = matWorld._42; pos.z = matWorld._43;

		for (i = m_vecPosList.size() - 1; i > 0; --i)
		{
			if ((m_vecPosList[i].p.z <= pos.z + list[4].z && m_vecPosList[i].p.z >= pos.z + list[0].z) &&
				(m_vecPosList[i].p.x <= pos.x + list[2].x && m_vecPosList[i].p.x >= pos.x + list[0].x) &&
				(m_vecPosList[i].p.y <= pos.y + list[1].y && m_vecPosList[i].p.y >= pos.y + list[0].y))
			{
				break;
			}

		}

		if (i == 0)
			return;
		else
		{
			m_vecPosList.erase(m_vecPosList.begin(), m_vecPosList.begin() + i);
			m_vecDirList.erase(m_vecDirList.begin(), m_vecDirList.begin() + i);

		}
	}

	if (nTag == Tag::Tag_Player)
	{

	}
}

void cDragonBreathe::SetUp(D3DXVECTOR3 vPos)
{
	m_vPos = vPos;
}
