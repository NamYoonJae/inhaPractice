#include "stdafx.h"
#include "DragonBreathe.h"
#include <random>
#include <iostream>
#include "FireBall.h"

#pragma once

cDragonBreathe::cDragonBreathe()
	:m_dwDuration(10000.0f)
	,m_dwStartTime(GetTickCount())
	,m_pvTarget(NULL)
{
	D3DXCreateTextureFromFileA(g_pD3DDevice,
		"data/Texture/Lava.png", &m_pParticle);
	m_vPos = D3DXVECTOR3(0, 0, 0);
}


cDragonBreathe::~cDragonBreathe()
{
}

void cDragonBreathe::Update()
{
	if (GetTickCount() - m_dwStartTime > m_dwDuration)
		return;

	if (m_pvTarget)
	{
		D3DXVECTOR3 vDir = *m_pvTarget - m_vPos;
		D3DXVec3Normalize(&vDir, &vDir);
		using namespace std;
		random_device rd;
		mt19937_64 mtRand(rd());
		uniform_real_distribution<float> dis(1.0f, 3.0f);

		for (int i = 0; i < 150; i++)
		{
			ST_PC_VERTEX pc;
			float fDist = dis(rd);
			pc.p = m_vPos + fDist * vDir;
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

			m_vecPosList.push_back(pc);
			m_vecDirList.push_back(vDir);
		}
	}

	for (int i = 0; i < m_vecPosList.size(); ++i)
	{
		m_vecPosList[i].p += m_vecDirList[i] * 0.8;
	}

	if (m_vecPosList.size() > 50000)
	{
		std::vector<ST_PC_VERTEX> vecPosList;
		std::vector<D3DXVECTOR3> vecDirList;

		vecPosList.assign(m_vecPosList.begin() + 500,
			m_vecPosList.end());
		m_vecPosList.swap(vecPosList);

		vecDirList.assign(m_vecDirList.begin() + 500,
			m_vecDirList.end());
		m_vecDirList.swap(vecDirList);
	}
	//


}

void cDragonBreathe::Render()
{
	if (GetTickCount() - m_dwStartTime > m_dwDuration)
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

}

void cDragonBreathe::SetUp()
{
	m_vPos = D3DXVECTOR3(0, 0, 0); 
}