#include "stdafx.h"
#include "SwampA.h"
#include "ShaderManager.h"
#include "cOBB.h"
#include "jsonManager.h"
#include "Paladin.h"
#pragma once

#define Box_Size 50

cSwampA::cSwampA()
	: m_pMesh(NULL)
	, m_pNoise(NULL)
	, m_pShader(NULL)
	, m_pTexcoord(NULL)
	, m_dwElapsedTime(GetTickCount())

	, m_fPhysicDamage(0)
	, m_fElementalDamage(0)
	//, m_Flood_Condition // string
	, m_Flood_Condition_Rate(0)
	, m_pTex0(NULL)
{
}

cSwampA::~cSwampA()
{
	SafeRelease(m_pMesh);
	SafeRelease(m_pShader);
	SafeRelease(m_pTexcoord);
	SafeRelease(m_pTexcoord_B);
	SafeRelease(m_pTex0);
	SafeRelease(m_pNoise);
}

void cSwampA::Setup(Tag T)
{
	JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* p_BOSS_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS/");
	JSON_Object* p_SKILL_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS SKILL/");

	m_Flood_Condition_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 3/Attribute/Condition rate"); // 상태이상 부여치

	// TODO 슬로우 처리

	// 100
	//m_vDir = D3DXVECTOR3(0, 0, -1);
	m_vPos = D3DXVECTOR3(0, 0, 0);

	// 스케일 적용
	//m_vScale = D3DXVECTOR3(0.3, 0.001, 0.3); 
	m_vScale = D3DXVECTOR3(
		(float)json_Function::object_get_double(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/Object/2/Status/Radius"),
		0.001f,
		(float)json_Function::object_get_double(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/Object/2/Status/Radius")
	);

	m_nTag = T;
	// xfile
	{
		using namespace std;
		string szFullPathX = "data/XFile/Cylinder/Cylinder.x";

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


	{
		D3DXIMAGE_INFO info;
		D3DXGetImageInfoFromFileA("data/Texture/Swamp.tga", &info);

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

	m_pOBB = new cOBB;
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y + 3.0f, m_vScale.z);
	m_pOBB->Setup(D3DXVECTOR3(-50, 20, -50), D3DXVECTOR3(50, 0, 50), &matS);

}

void cSwampA::Update()
{
	if (m_pOBB)
	{
		D3DXMATRIXA16 matWorld, matT;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);

		matWorld = matT;
		m_pOBB->Update(&matWorld);
	}
}

void cSwampA::Render(D3DXMATRIXA16 * pmat)
{
	D3DXMATRIXA16 matWorld, matS, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matWorld = matS * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for (int i = 0; i < m_vecMtl.size(); ++i)
	{
		//g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);
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


	if (m_pOBB)
	{
		m_pOBB->OBBBOX_Render(D3DCOLOR_ARGB(255, 255, 255, 255));
	}

}

void cSwampA::CollisionProcess(cObject * pObject)
{
	if (pObject->GetTag() == Tag::Tag_Player)
	{
		cPaladin* pPaladin = (cPaladin*)pObject;

		cOBB *pBody = pPaladin->GetPartsList().at(1)->GetOBB();

		if (cOBB::IsCollision(m_pOBB, pBody))
		{
			switch (m_nTag)
			{
			case Tag::Tag_SwampA:
			{
				pPaladin->SetSpeed(pPaladin->GetOriginSpeed() - 50); // 벗어났을때 처리
																	 //cout << "TRUE" << endl;
			}
			// 	 이동속도 느려지는 오브젝트
			break;
			}
		}


	}
}
