#include "stdafx.h"
#include "Swamp.h"
#include "ShaderManager.h"

#pragma once

cSwamp::cSwamp()
	:m_pMesh(NULL)
	,m_pNoise(NULL)
	,m_pShader(NULL)
	,m_pTexcoord(NULL)
{
}


cSwamp::~cSwamp()
{
}

void cSwamp::Setup()
{
	// 100
	//m_vDir = D3DXVECTOR3(0, 0, -1);
	m_vPos = D3DXVECTOR3(0, 0.0, 0);
	
	// xfile
	{

		using namespace std;
		string szFullPathX = "data/XFile/Cube/Cube.x";


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
				m_vecMtl.push_back(mtrls[i].MatD3D);
			}


		}
		SafeRelease(mtrlBuffer);
	}


	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFileA("data/Texture/Swamp.tga", &info);
	

	//https://m.blog.naver.com/PostView.nhn?blogId=pok_jadan&logNo=189387506&proxyReferer=https:%2F%2Fwww.google.com%2F	
	//https://m.blog.naver.com/PostView.nhn?blogId=likeban&logNo=30037278954&proxyReferer=https:%2F%2Fwww.google.com%2F
	
	D3DXCreateTextureFromFileExA
	(g_pD3DDevice, "data/Texture/Swamp.tga",
		info.Width, info.Height, 1, 0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		NULL,
		NULL,
		&m_pTexcoord);

	// shader load

	m_pShader = g_pShaderManager->GetShader(eShader::Swamp);
}

void cSwamp::Update()
{
}

void cSwamp::Render(D3DXMATRIXA16 *pmat)
{
	D3DXMATRIXA16 matWorld, matS, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS,0.3,0.001,0.3);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matWorld = matS * matT;

	
	for (int i = 0; i < m_vecMtl.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtl[i]);
		
		if (m_pShader)
		{
			m_pShader->SetTechnique("Default_DirectX_Effect");
			D3DXMATRIXA16 matView, matProjection, matViewProj;
			g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
			g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
			
			matViewProj = matWorld * matView * matProjection;
			
			m_pShader->SetMatrix("matViewProjection", &matViewProj);
			m_pShader->SetFloat("time", GetTickCount() * 0.001f);
			m_pShader->SetTexture("Swamp", m_pTexcoord);


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
	}
	
}
