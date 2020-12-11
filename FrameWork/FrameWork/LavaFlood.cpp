#include "stdafx.h"
#include "LavaFlood.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#pragma once

cLavaFlood::cLavaFlood()
	: m_pEffect(NULL)
	, m_pFlameTex(NULL)
	, m_dwStartTime(GetTickCount())
	, m_dwElapseTime(0.0f)
{

}


cLavaFlood::~cLavaFlood()
{
}

void cLavaFlood::Setup()
{
	m_pEffect = g_pShaderManager->GetShader(eShader::LavaEffect);

	m_pFlameTex = g_pTextureManager->GetTexture("data/Texture/Lava.png");

	m_vPos = D3DXVECTOR3(0,0,0);

}

void cLavaFlood::Update()
{
}

void cLavaFlood::Render(D3DXMATRIXA16* pmat)
{
	D3DXMATRIXA16 matWorld, matT,matR,matS;

	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matWorld);
	
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matWorld = matS * matT * matR;

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	if(m_pEffect)
	{
		m_pEffect->SetTechnique("Default_DirectX_Effect");
		D3DXMATRIXA16 matView, matProjection , matViewProj;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

		matViewProj = matView * matProjection;

		m_pEffect->SetMatrix("matWorld", &matWorld);
		m_pEffect->SetMatrix("matViewProjection", &matViewProj);

		
		if (GetTickCount() - m_dwPrevTime > 300.0f)
		{
			m_dwPrevTime = GetTickCount();
			m_dwElapseTime = fmod((m_dwStartTime - m_dwPrevTime), (D3DX_PI * 2.0f));
		}
		
		
		m_pEffect->SetFloat("time", m_dwElapseTime);
		
		m_pEffect->SetTexture("Lava_Tex", m_pFlameTex);
	
		UINT numPasses = 0;
		m_pEffect->Begin(&numPasses, NULL);
		
		for(UINT i = 0; i < numPasses; ++i)
		{
			m_pEffect->BeginPass(i);
			// skinnedMesh ÇÊ¿ä
			m_pEffect->EndPass();
		}
		
		m_pEffect->End();
		
	}
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}
