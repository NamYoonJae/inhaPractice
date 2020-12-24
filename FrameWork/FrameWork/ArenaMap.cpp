#include "stdafx.h"
#include "ArenaMap.h"
#include "ObjLoader.h"
#include "ShaderManager.h"

#include "DragonSoulEater.h"
#include "ObjectPool.h"
#include "Swamp.h"

cArenaMap::cArenaMap()
	:iMap()
{
	m_nTag = Tag::Tag_Map;
	m_vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_dwCoolTime = 30000.0f;
	m_IsSwampCreate = false;
	
	cObjLoader ObjLoader;
	ObjLoader.LoadOBJ(m_vecMapGroup, "data/ObjFile/AreaWorld", "Arena_base.obj");

	vector<cGroup*>				m_vecDoorGroup;
	vector<cGroup*>				m_vecFlagGroup;
	vector<cGroup*>				m_vecHornGroup;
	vector<cGroup*>				m_vecPillarGroup;
	vector<cGroup*>				m_vecPollGroup;
	vector<cGroup*>				m_vecWoodSpikeGroup;
	ObjLoader.LoadOBJ(m_vecDoorGroup, "data/ObjFile/AreaWorld", "Arena_Door.obj");
	ObjLoader.LoadOBJ(m_vecFlagGroup, "data/ObjFile/AreaWorld", "Arena_Flag.obj");
	ObjLoader.LoadOBJ(m_vecHornGroup, "data/ObjFile/AreaWorld", "Arena_Horn.obj");
	ObjLoader.LoadOBJ(m_vecPillarGroup, "data/ObjFile/AreaWorld", "Arena_Pillar.obj");
	ObjLoader.LoadOBJ(m_vecPollGroup, "data/ObjFile/AreaWorld", "Arena_Poll.obj");
	ObjLoader.LoadOBJ(m_vecWoodSpikeGroup, "data/ObjFile/AreaWorld", "Arena_WoodSpike.obj");

	m_vecArenaGroup.clear();

	m_vecArenaGroup.insert(m_vecArenaGroup.end(),
		m_vecMapGroup.begin(),
		m_vecMapGroup.end());

	m_vecArenaGroup.insert(m_vecArenaGroup.end(),
		m_vecDoorGroup.begin(),
		m_vecDoorGroup.end());
	
	m_vecArenaGroup.insert(m_vecArenaGroup.end(),
		m_vecFlagGroup.begin(),
		m_vecFlagGroup.end());

	m_vecArenaGroup.insert(m_vecArenaGroup.end(),
		m_vecHornGroup.begin(),
		m_vecHornGroup.end());

	m_vecArenaGroup.insert(m_vecArenaGroup.end(),
		m_vecPillarGroup.begin(),
		m_vecPillarGroup.end());

	m_vecArenaGroup.insert(m_vecArenaGroup.end(),
		m_vecPollGroup.begin(),
		m_vecPollGroup.end());

	m_vecArenaGroup.insert(m_vecArenaGroup.end(),
		m_vecWoodSpikeGroup.begin(),
		m_vecWoodSpikeGroup.end());


	// x축 90도 로테이션
	//D3DXMATRIXA16

	
	for (int i = 0; i < m_vecArenaGroup.size(); ++i)
	{
		vector<ST_PNT_VERTEX> Group = m_vecArenaGroup.at(i)->GetVertex();
		for (int j = 0; j < m_vecArenaGroup.at(i)->GetVertex().size(); ++j)
		{
			Group.at(j).t.y = 1 - Group.at(j).t.y;
		}

		m_vecArenaGroup.at(i)->SetVertices(Group);
	}

	std::vector<ST_PNT_VERTEX> list;
	list = m_vecMapGroup.at(0)->GetVertices();

	D3DXVECTOR3 vMin, vMax;
	vMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	vMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	for(int i = 0; i < list.size(); i++)
	{
		vMin.x = min(vMin.x, list.at(i).p.x);
		vMin.z = min(vMin.z, list.at(i).p.z);
		
		vMax.x = max(vMax.x, list.at(i).p.x);
		vMax.z = max(vMax.z, list.at(i).p.z);		
	}

	m_RCArea.bottom = vMin.z;
	m_RCArea.top = vMax.z;
	m_RCArea.left = vMin.x;
	m_RCArea.right = vMax.x;
}


cArenaMap::~cArenaMap()
{
}

float cArenaMap::getHeight(D3DXVECTOR3 pos)
{
	pos.y += 10;

	std::vector<ST_PNT_VERTEX> list;
	list = m_vecMapGroup.at(0)->GetVertices();
	
	float u, v, t;
	D3DXVECTOR3 vDirection = D3DXVECTOR3(0, -1, 0);

	D3DXMATRIXA16  matS;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);

	for(int i = 0; i < list.size(); i+=3)
	{
		D3DXVECTOR3 v0, v1, v2;
		v0 = list[i + 0].p;
		v1 = list[i + 1].p;
		v2 = list[i + 2].p;

		D3DXVec3TransformCoord(&v0, &v0, &matS);
		D3DXVec3TransformCoord(&v1, &v1, &matS);
		D3DXVec3TransformCoord(&v2, &v2, &matS);
		
		bool b = D3DXIntersectTri(&v0, &v1, &v2, &pos, &vDirection, &u, &v, &t);

		if(b)
		{
			D3DXVECTOR3 vPickedPosition = pos + (t * vDirection);
			return vPickedPosition.y;
		}
		
	}

	return 0.0f;
}

void cArenaMap::Render(D3DXMATRIXA16* pmat)
{
	DefaultRender();
	//ShaderRender();
}

void cArenaMap::Update()
{
	if(m_IsSwampCreate == false)
	{
		static cDragonSoulEater* pDragon = 0;
		if (pDragon == NULL)
		{
			pDragon = (cDragonSoulEater*)ObjectManager->SearchChild(Tag::Tag_Boss);
		}
		else if (pDragon)
		{
			int nPhase = pDragon->GetPhase();

			if (nPhase >= 2)
			{
				m_dwElapseTime = GetTickCount();
				m_IsSwampCreate = true;
			}
		}
	}
	else if(m_IsSwampCreate && (GetTickCount() - m_dwElapseTime >= m_dwCoolTime))
	{
		CreateSwamp();
		m_dwElapseTime = GetTickCount();
	}
}

bool cArenaMap::CheckInMap(D3DXVECTOR3 pos)
{
	pos.y += 10;

	std::vector<ST_PNT_VERTEX> list;
	//IntersectTri

	list = m_vecMapGroup.at(0)->GetVertices();


	float u, v, t;
	bool check;

	D3DXMATRIXA16  matS;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);

	for (int i = 0; i < list.size(); i += 3)
	{
		D3DXVECTOR3 p1, p2, p3;
		p1 = list[i + 0].p;
		p2 = list[i + 1].p;
		p3 = list[i + 2].p;

		D3DXVec3TransformCoord(&p1, &p1, &matS);
		D3DXVec3TransformCoord(&p2, &p2, &matS);
		D3DXVec3TransformCoord(&p3, &p3, &matS);


		check = D3DXIntersectTri(&p1, &p2, &p3, &pos, &D3DXVECTOR3(0, -1, 0), &u, &v, &t);

		if (check)
		{
			return true;
		}
	}


	return false;

	
}

void cArenaMap::AddShadowMap(LPDIRECT3DTEXTURE9 pShadowTexture)
{
	if (pShadowTexture != NULL)
	{
		m_vecShadowMap.push_back(pShadowTexture);
	}
}

void cArenaMap::ReplaceShadowMap(LPDIRECT3DTEXTURE9 pShadowTexture)
{
	if (!m_vecShadowMap.empty())
	{
		m_vecShadowMap[0] = pShadowTexture;
	}
}

void cArenaMap::ShaderSetup()
{
	LPD3DXEFFECT pShader = g_pShaderManager->GetShader(eShader::ApplyShadow);

	if (pShader)
	{
		D3DLIGHT9   Light;
		g_pD3DDevice->GetLight(0, &Light);
		D3DXVECTOR4 vLightPos = D3DXVECTOR4(Light.Direction.x, Light.Direction.y, Light.Direction.z, 1);
		//D3DXVECTOR4 vLightPos = D3DXVECTOR4(Light.Position.x, Light.Position.y, Light.Position.z, 1);
		D3DXCOLOR c = Light.Diffuse;
		D3DXVECTOR4 LightColor = D3DXVECTOR4(c.r, c.g, c.b, c.a);

		pShader->SetVector("gWorldLightPosition", &vLightPos);
		pShader->SetVector("gLightColor", &LightColor);
	}
}

void cArenaMap::ShaderRender()
{
	LPD3DXEFFECT pShader = g_pShaderManager->GetShader(eShader::ApplyShadow);

	if (pShader)
	{
		D3DXMATRIXA16 matW, matS, matR, matT;
		D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
		matW = matS * matR * matT;

		D3DXMATRIXA16	matView;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

		D3DXMATRIXA16	matProjection;
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

		D3DXMATRIXA16 matWVP = matView * matProjection;

		D3DLIGHT9   Light;
		g_pD3DDevice->GetLight(0, &Light);
		//D3DXVECTOR4 vLightPos = D3DXVECTOR4(Light.Direction.x, Light.Direction.y, Light.Direction.z, 1);
		D3DXVECTOR4 vLightPos = D3DXVECTOR4(Light.Position.x, Light.Position.y, Light.Position.z, 1);
		pShader->SetVector("gWorldLightPosition", &vLightPos);
		
		// 광원-뷰 행렬을 만든다.
		D3DXMATRIXA16 matLightView;
		{
			D3DXVECTOR3 vEyePt(vLightPos.x, vLightPos.y, vLightPos.z);
			D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
			D3DXMatrixLookAtLH(&matLightView, &vEyePt, &vLookatPt, &vUpVec);
		}

		// 광원-투영 행렬을 만든다.
		D3DXMATRIXA16 matLightProjection;
		{
			D3DXMatrixPerspectiveFovLH(&matLightProjection, D3DX_PI / 4.0f, 1, 1, 3000);
		}

		
		
		// 그림자 입히기 쉐이더 전역변수들을 설정
		//pShader->SetMatrix("gWorldMatrix", &matW);
		pShader->SetMatrix("gWorldMatrix", &MatrixIdentity);
		pShader->SetMatrix("gViewProjectionMatrix", &matWVP);
		pShader->SetMatrix("gLightViewMatrix", &matLightView);
		pShader->SetMatrix("gLightProjectionMatrix", &matLightProjection);

		pShader->SetTexture("ShadowMap_Tex", m_vecShadowMap[0]);


		// 쉐이더를 시작한다.
		UINT numPasses = 0;
		pShader->Begin(&numPasses, NULL);
		{
			for (UINT i = 0; i < numPasses; ++i)
			{
				pShader->BeginPass(i);
				{
					for (int i = 0; i < m_vecArenaGroup.size(); ++i)
						m_vecArenaGroup[i]->Render();
				}
				pShader->EndPass();
			}
		}
		pShader->End();
	}
}

void cArenaMap::DefaultRender()
{
	D3DXMATRIXA16 matW, matS, matR, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matW = matS * matR * matT;
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);
	for (int i = 0; i < m_vecArenaGroup.size(); ++i)
		m_vecArenaGroup[i]->Render();


	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, true);
}

void cArenaMap::CreateSwamp()
{
	cSwamp* pSwamp = new cSwamp;
	pSwamp->Setup(Tag::Tag_SwampA);
	
	srand(time(NULL));

	random_device rd;
	mt19937_64 gen(rd());
	std::uniform_real_distribution<> randNumZ(m_RCArea.bottom,m_RCArea.top);
	std::uniform_real_distribution<> randNumX(m_RCArea.left, m_RCArea.right);

	float fSwampX = randNumX(gen);
	float fSwampZ = randNumZ(gen);

	D3DXVECTOR3 vSwampPos(fSwampX, 0, fSwampZ);
	pSwamp->SetPos(vSwampPos);
	pSwamp->SetScale(D3DXVECTOR3(0.5, 0.001, 0.5));
	ObjectManager->AddChild(pSwamp);
}
