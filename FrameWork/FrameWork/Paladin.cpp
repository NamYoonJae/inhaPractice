#include "stdafx.h"
#include "cOBB.h"
#include "SkinnedMesh.h"
#include "PaladinState.h"
#include "TimerManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

#include "Paladin.h"

#include "AllocateHierarchy.h"

cPaladin::cPaladin()
	:m_fvelocity(0.0f)
	,m_isMoving(false)
	,m_pSkinnedUnit(NULL)
	,m_pCurState(NULL)
	, m_Hp(0)
	, m_Staminer(0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cPaladin::~cPaladin()
{
	SafeDelete(m_pOBB);
	SafeDelete(m_pCurState);
	SafeDelete(m_pSkinnedUnit);
}

void cPaladin::Setup(char* szFolder, char* szFile)
{
	m_Hp = 1000;
	m_Staminer = 1000;
	m_pSkinnedUnit = new cSkinnedMesh;
	m_pSkinnedUnit->Setup(szFolder, szFile);
	m_pSkinnedUnit->SetAnimationIndex(9);

	m_vPos = D3DXVECTOR3(20, 0, 30);
	m_vScale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	m_pSkinnedUnit->Update();
	EventManager->Attach(this);

	m_pOBB = new cOBB;
	m_pOBB->Setup(m_pSkinnedUnit, &m_matWorld);

	ZeroMemory(&m_Mstl, sizeof(D3DMATERIAL9));
	m_Mstl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_Mstl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_Mstl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	ShaderSetup();
}

void cPaladin::ShaderSetup()
{
	LPD3DXEFFECT pShader = g_pShaderManager->GetShader(eShader::Normal_DSNL);

	D3DLIGHT9   Light;
	g_pD3DDevice->GetLight(0, &Light);
	D3DXVECTOR4 vLightPos = D3DXVECTOR4(Light.Direction.x, Light.Direction.y, Light.Direction.z, 1);
	//D3DXVECTOR4 vLightPos = D3DXVECTOR4(Light.Position.x, Light.Position.y, Light.Position.z, 1);
	//D3DXVECTOR4 vLightPos = D3DXVECTOR4(500.00, 500.00, -500.00, 1.00);
	D3DXCOLOR c = Light.Diffuse;
	D3DXVECTOR4 LightColor = D3DXVECTOR4(c.r, c.g, c.b, c.a);

	pShader->SetVector("gWorldLightPos", &vLightPos);
	pShader->SetVector("gLightColor", &LightColor);
}

void cPaladin::Update()
{
	D3DXMatrixScaling(&m_matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationY(&m_matRot, m_vRot.y);
	D3DXMatrixTranslation(&m_matTranse, m_vPos.x, m_vPos.y, m_vPos.z);

	m_matWorld = m_matScale * m_matRot * m_matTranse;
	m_pSkinnedUnit->m_matWorldTM = m_matWorld;

	if (m_fvelocity != 0 && !m_isMoving)
	{
		m_isMoving = true;
	}
	else if (m_fvelocity == 0 && m_isMoving)
	{
		m_isMoving = false;
	}

	m_pSkinnedUnit->Update();

	m_pOBB->Update(&m_matWorld);
}

void cPaladin::Update(EventType event)
{
	D3DXMATRIXA16 TempRot;
	D3DXMatrixIdentity(&TempRot);

	//float delta = g_pTimeManager->GetElapsedTime();
	float delta = 0.001f;
	static bool isKeyDown = false;

	if (event == EventType::EVENT_ARROW_UP)
	{
		m_fvelocity = 300.0f * delta;
		isKeyDown = true;
	}
	if (event == EventType::EVENT_ARROW_LEFT)
	{
		D3DXVec3TransformNormal(&m_vDir, &m_vDir, D3DXMatrixRotationY(&TempRot, -125.0f * delta));
		m_vRot.y -= 125.0f * delta;
		isKeyDown = true;
	}
	if (event == EventType::EVENT_ARROW_DOWN)
	{
		m_fvelocity = -118.5f * delta;
		isKeyDown = true;
	}
	if (event == EventType::EVENT_ARROW_RIGHT)
	{
		D3DXVec3TransformNormal(&m_vDir, &m_vDir, D3DXMatrixRotationY(&TempRot, 125.0f * delta));
		m_vRot.y += 125.0f * delta;
		isKeyDown = true;
	}

	/// new Code 11-28 차현빈 3:#8
	if (event == EventType::EVENT_KEYUP && isKeyDown)
	{
		m_fvelocity = 0;
		isKeyDown = false;
	}

	D3DXVec3Normalize(&m_vDir, &m_vDir);
	m_vPos += m_vDir * m_fvelocity;

	static int n = 0;

	if (event == EventType::EVENT_LBUTTONDOWN)
	{
		m_pSkinnedUnit->SetAnimationIndexBlend(n++);
	}
}

void cPaladin::Render(D3DXMATRIXA16* pmat)
{
	ShaderRender();
	m_pOBB->OBBBOX_Render(D3DCOLOR_XRGB(255, 255, 255));
}

void cPaladin::ShaderRender()
{
	LPD3DXEFFECT pShader = g_pShaderManager->GetShader(eShader::Specular_DSL);

	if (pShader)
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		
		D3DXMATRIXA16	matView;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

		D3DXMATRIXA16	matProjection;
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

		D3DXMATRIXA16	matWVP;
		matWVP = matView * matProjection * m_matScale;

		// 쉐이더 전역변수들을 설정
		pShader->SetMatrix("gWorldMatrix", &m_matScale);
		pShader->SetMatrix("gWorldViewProjectionMatrix", &matWVP);
		
		pShader->SetTexture("DiffuseMap_Tex", g_pTextureManager->GetTexture("data/XFile/Paladin/Paladin_diffuse.png"));
		pShader->SetTexture("SpecularMap_Tex", g_pTextureManager->GetTexture("data/XFile/Paladin/Paladin_specular.png"));
		
		UINT numPasses = 0;
		pShader->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; ++i)
			{
				pShader->BeginPass(i);
				{
					m_pSkinnedUnit->Render();
				}
				pShader->EndPass();
			}
		}
		pShader->End();
	}
}

void cPaladin::SetTranseform(D3DXMATRIXA16* pmat)
{
}
