#include "stdafx.h"
#include "FireBall.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "cOBB.h"
#define once
#define X_Radian 25.0f
#pragma once

DWORD FtoDw(float f)
{
	return *((DWORD*)&f);
}

cFireBall::cFireBall()
	:m_pMesh(NULL)
	, m_pShader(NULL)
	, m_pTexcoord(NULL)
{
	m_pOBB = NULL;
}


cFireBall::~cFireBall()
{
}

void cFireBall::Setup()
{
	//m_vDir = D3DXVECTOR3(0, 0, -1);
	//m_vPos = D3DXVECTOR3(0, 10, 0);
	m_vScale = D3DXVECTOR3(0.1, 0.1, 0.1);
	
	// obb
	D3DXVECTOR3 vMin(25,25,25), 
				vMax(-25,-25,-25);
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	m_pOBB = new cOBB;
	m_pOBB->Setup(vMin,vMax,&matS);

	//shader
	m_pShader = g_pShaderManager->GetShader(eShader::FireBall);


	// xfile
	using namespace std;
	string szFullPathX = "data/XFile/Sphere/Sphere.x";


	HRESULT hr = 0;
	ID3DXBuffer *adjBuffer = 0;
	ID3DXBuffer *mtrlBuffer = 0;
	DWORD numMtrls = 0;

	hr = D3DXLoadMeshFromXA(
		szFullPathX.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&m_pMesh);

	if (FAILED(hr))
		return;

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL *mtrls = (D3DXMATERIAL *)mtrlBuffer->GetBufferPointer();

		for (int i = 0; i < numMtrls; i++)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
			m_vecMtls.push_back(mtrls[i].MatD3D);
		}


	}
	SafeRelease(mtrlBuffer);

	D3DXCreateTextureFromFileA(g_pD3DDevice,
		"data/Texture/Base.jpg", &m_pTexcoord);

	D3DXCreateTextureFromFileA(g_pD3DDevice,
		"data/Texture/alpha_tex.tga", &m_pParticle);

	//  particle

	m_vecVertexParticle.resize(500);
	
	using namespace std;
	random_device rd;
	mt19937_64 mtRand(rd());
	uniform_real_distribution<float> dis(2.5, 3.0);

	for (int i = 0; i < m_vecVertexParticle.size(); i++)
	{
		float fRadius = dis(rd);

		m_vecVertexParticle[i].p = D3DXVECTOR3(0, fRadius, fRadius);
		D3DXVECTOR3 vAngle = D3DXVECTOR3(
			D3DXToRadian(rand() % 360),
			D3DXToRadian(rand() % 360),
			D3DXToRadian(rand() % 360 / 10.0f));



		D3DXMATRIX matRx, matRy, matRz, matWorld;
		D3DXMatrixRotationX(&matRx, vAngle.x);
		D3DXMatrixRotationY(&matRy, vAngle.y);
		D3DXMatrixRotationZ(&matRz, vAngle.z);

		matWorld = matRx * matRy * matRz;
		D3DXVec3TransformCoord(
			&m_vecVertexParticle[i].p,
			&m_vecVertexParticle[i].p,
			&matWorld);

		m_vecVertexParticle[i].c =
			D3DCOLOR_ARGB(255, 255, 0, 0);

		m_vecVertexParticle[i].p += m_vPos;
	}



}

void cFireBall::Update()
{

	m_vPos += m_vDir * 0.1f;

	static int nAlpha = 0;
	static int nDelta = 4;
	nAlpha += nDelta;
	//std::cout << nAlpha << std::endl;
	if (nAlpha > 255)
	{
		nAlpha = 255;
		nDelta = -1;
	}
	if (nAlpha < 200)
	{
		nAlpha = 200;
		nDelta *= -1;
	}

	D3DXVECTOR3 Particle = m_vecVertexParticle[0].p;
	for (int i = 0; i < m_vecVertexParticle.size(); i++)
	{
		//if (i % 2) continue;
		m_vecVertexParticle[i].c = D3DCOLOR_ARGB(nAlpha, 255, 70, 0);
		m_vecVertexParticle[i].p += m_vDir * 0.1f;
	}

	// 파티클을 생성한다. 1초마다하고size가 500이상이면 앞에 100삭제 
	static DWORD dwTimeElapsed = GetTickCount();
	if (GetTickCount() - dwTimeElapsed > 500.0f)
	{
		std::random_device rd;
		std::mt19937_64 mtRand(rd());

		for (int i = 0; i < 500; i++)
		{
			float d = i * 0.005;
			std::uniform_real_distribution<float> dis(2.5 - d, 3.0 - d);
			float fRadius = dis(rd);
			ST_PC_VERTEX pc;
			pc.p = D3DXVECTOR3(0, fRadius, fRadius);
			D3DXVECTOR3 vAngle = D3DXVECTOR3(
				D3DXToRadian(rand() % 360),
				D3DXToRadian(rand() % 360),
				D3DXToRadian(rand() % 360 / 10.0f));



			D3DXMATRIX matRx, matRy, matRz, matWorld;
			D3DXMatrixRotationX(&matRx, vAngle.x);
			D3DXMatrixRotationY(&matRy, vAngle.y);
			D3DXMatrixRotationZ(&matRz, vAngle.z);

			matWorld = matRx * matRy * matRz;
			D3DXVec3TransformCoord(
				&pc.p,
				&pc.p,
				&matWorld);

			float dir = 0.5 + d * 3;
			pc.p += m_vPos - m_vDir * (dir);
			pc.c = D3DCOLOR_ARGB(255, 255, 70, 0);

			m_FlowParticle.push_back(pc);
		}

	}

	if (m_FlowParticle.size() > 1500)
	{
		std::vector<ST_PC_VERTEX> vecNewFlowParticle;
		vecNewFlowParticle.assign(m_FlowParticle.begin() + 500, m_FlowParticle.end());
		m_FlowParticle.swap(vecNewFlowParticle);
	}


	D3DXMATRIXA16 matWorld, matS, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matWorld = matS * matT;
	m_pOBB->Update(&matT);
}

void cFireBall::Render(D3DXMATRIXA16 *pmat)
{

	D3DXMATRIXA16 matWorld, matS, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, m_vScale.x,m_vScale.y,m_vScale.z);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	
	matWorld = matS * matT;

	for (int i = 0; i < m_vecMtls.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtls[i]);
		if (m_pShader)
		{
			m_pShader->SetTechnique("Default_DirectX_Effect");
			D3DXMATRIXA16 matView, matProjection, matViewProj;
			g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
			g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
			matViewProj = matView * matProjection;
			m_pShader->SetMatrix("matViewProjection", &matViewProj);
			m_pShader->SetMatrix("matWorld", &matWorld);

			m_pShader->SetFloat("Time", GetTickCount() * 0.001f);
			m_pShader->SetTexture("Base_Tex", m_pTexcoord);

			UINT numPasses = 0;
			m_pShader->Begin(&numPasses, NULL);
			for (UINT i = 0; i < numPasses; ++i)
			{
				m_pShader->BeginPass(i);
				if (m_pMesh)
				{
					m_pMesh->DrawSubset(0);
				}
				m_pShader->EndPass();
			}
			m_pShader->End();
		}
		else
		{
			if (m_pTexcoord)
				g_pD3DDevice->SetTexture(0, m_pTexcoord);

			g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
			if (m_pMesh)
				m_pMesh->DrawSubset(0);

		}

	}

	ParticleRender();

	if (m_pOBB)
		m_pOBB->OBBBOX_Render(D3DCOLOR_ARGB(255,255, 0, 0));
}

void cFireBall::ParticleRender()
{
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
		m_vecVertexParticle.size(),
		&m_vecVertexParticle[0],
		sizeof(ST_PC_VERTEX));
	if (!m_FlowParticle.empty())
	{
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_POINTLIST,
			m_FlowParticle.size(),
			&m_FlowParticle[0],
			sizeof(ST_PC_VERTEX));
	}

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pD3DDevice->SetTexture(0,
		NULL);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG0, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}
