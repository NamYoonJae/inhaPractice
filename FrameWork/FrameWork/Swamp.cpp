#include "stdafx.h"
#include "Swamp.h"
#include "ShaderManager.h"
#include "cOBB.h"
#include "jsonManager.h"
#include "Paladin.h"
#pragma once

#define Box_Size 50

cSwamp::cSwamp()
	: m_pMesh(NULL)
	, m_pNoise(NULL)
	, m_pShader(NULL)
	, m_pTexcoord(NULL)
	, m_dwElapsedTime(GetTickCount())

	, m_fPhysicDamage(0)
	, m_fElementalDamage(0)
	//, m_Flood_Condition // string
	, m_Flood_Condition_Rate(0)
{
}


cSwamp::~cSwamp()
{
}

void cSwamp::Setup(Tag T)
{
	JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* p_BOSS_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS/");
	JSON_Object* p_SKILL_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS SKILL/");

	m_fPhysicDamage = json_Function::object_get_double(p_BOSS_object, "Attack/Melee");
	m_fElementalDamage = json_Function::object_get_double(p_BOSS_object, "Attack/Elemental");
	m_Flood_Condition = json_Function::object_get_string(p_SKILL_object, "SKILL 3/Attribute/Condition"); // 상태이상 부여 종류
	m_Flood_Condition_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 3/Attribute/Condition rate"); // 상태이상 부여치


	m_dwElapsedTime = GetTickCount();
	m_dwDurationTime = json_Function::object_get_double(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/Object/2/Status/Duration");


	// 100
	//m_vDir = D3DXVECTOR3(0, 0, -1);
	m_vPos = D3DXVECTOR3(0, 0.0, 0);
	m_vScale = D3DXVECTOR3(0.3, 0.001, 0.3); // << 넓이 적용하기
	m_nTag = T;
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

	if (T == Tag_SwampB || T == Tag_SwampA)
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


	// OBB

	m_pOBB = new cOBB;
	m_pOBB->Setup(D3DXVECTOR3(-50, -50, -50), D3DXVECTOR3(50, 50, 50));

}

void cSwamp::Update()
{
	if(m_dwDurationTime >= 0.0f && m_nTag == Tag::Tag_SwampB)
	{
		if(GetTickCount() - m_dwElapsedTime >= m_dwDurationTime)
		{
			m_isDelete = true;
			return;
		}
	}
	
	if (m_pOBB)
	{
		D3DXMATRIXA16 matWorld, matS, matT;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
		matWorld = matS * matT;
		m_pOBB->Update(&matWorld);
	}

	// json 값 받아와서 유지시간 넘어가면 없어지게 처리
	// m_isDelete = true; // << 오브젝트 풀에서 삭제 처리해줌
}

void cSwamp::Render(D3DXMATRIXA16 *pmat)
{
	D3DXMATRIXA16 matWorld, matS, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
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


	if (m_dwDurationTime <= GetTickCount() - m_dwElapsedTime) 
		m_isDelete = true; // 지속시간이 끝날때 제거
}

void cSwamp::CollisionProcess(cObject * pObject)
{
	if (pObject->GetTag() == Tag::Tag_Player)
	{
		cPaladin* pPaladin = (cPaladin*)pObject;
		switch (m_nTag)
		{
		case Tag::Tag_SwampA :
		{
			pPaladin->SetSpeed(pPaladin->GetOriginSpeed() - 50); // 벗어났을때 처리
		}

			// 	 이동속도 느려지는 오브젝트
			break;
		case Tag::Tag_SwampB :
			//  데미지를 주는 오브젝트
			//  여기서 데미지 처리
			//  주는 데미지 = m_fPhysicDamage* m_Flood_Physic_Rate + m_fElementalDamage * m_Flood_Elemental_Rate;
			break;
		}
	}
	

	

}
