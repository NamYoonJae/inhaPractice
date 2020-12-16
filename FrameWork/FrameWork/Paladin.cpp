#include "stdafx.h"
#include "cOBB.h"
#include "SkinnedMesh.h"
#include "PaladinState.h"
#include "TimerManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

#include "Paladin.h"

#include "AllocateHierarchy.h"
#include "ObjectPool.h"
#include "Trophies.h"

#include "PaladinAttack.h"
#include "PaladinEvade.h"
#include "PaladinIdle.h"
#include "PaladinMove.h"

cPaladin::cPaladin()
	:m_fvelocity(0.0f)
	,m_isMoving(false)
	,m_pSkinnedUnit(NULL)
	,m_pCurState(NULL)
	, m_Hp(0)
	, m_Stamina(0)
	, m_MaxHp(1000)
	, m_MaxStamina(500)
	, m_pTrophies(NULL)
	, m_vecDebuff(NULL)
	, m_pDebuff1(NULL)
	, m_pDebuff2(NULL)
	,m_fSpeed(300.0f)
	//, m_Debuff_Time(0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cPaladin::~cPaladin()
{
	SafeDelete(m_pOBB);
	SafeDelete(m_pCurState);
	SafeDelete(m_pSkinnedUnit);
	SafeDelete(m_pTrophies);
	for (cParts* parts : m_vecParts)
	{
		SafeDelete(parts);
	}
	m_vecParts.clear();
}

void cPaladin::Setup(char* szFolder, char* szFile)
{
	m_MaxHp = 1000;
	m_MaxStamina = 500;

	m_Hp = 1000;
	m_Stamina = 500;
	
	m_pSkinnedUnit = new cSkinnedMesh;
	m_pSkinnedUnit->Setup(szFolder, szFile);
	m_pSkinnedUnit->SetAnimationIndex(0);

	m_vPos = D3DXVECTOR3(20, 0, 30);
	m_vScale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

	D3DXMatrixScaling(&m_matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationY(&m_matRot, m_vRot.y);
	D3DXMatrixTranslation(&m_matTranse, m_vPos.x, m_vPos.y, m_vPos.z);

	m_matWorld = m_matScale * m_matRot * m_matTranse;
	m_pSkinnedUnit->m_matWorldTM = m_matWorld;
	
	m_pSkinnedUnit->Update();
	EventManager->Attach(this);

	cParts* pWeapon = new cPaladinWeapon;
	pWeapon->Setup(D3DXFrameFind(m_pSkinnedUnit->GetFrame(), "Sword_joint"),
		D3DXFrameFind(m_pSkinnedUnit->GetFrame(), "Paladin_J_Nordstrom_Sword")->pMeshContainer, &m_matWorld);
	m_vecParts.push_back(pWeapon);

	cParts* pBody = new cPaladinBody;
	pBody->Setup(m_pSkinnedUnit, (D3DXMATRIXA16*)m_pSkinnedUnit->m_pTransformationMatrix);
	pBody->SetColor(D3DCOLOR_XRGB(255, 0, 0));
	m_vecParts.push_back(pBody);

	D3DXMATRIXA16 mat;
	D3DXMatrixScaling(&mat, 1, 3, 1.5f);
	
	if (m_pSkinnedUnit->m_pTransformationMatrix)
		mat *= *m_pSkinnedUnit->m_pTransformationMatrix;
	
	m_pOBB = new cOBB;
	m_pOBB->Setup(m_pSkinnedUnit, &mat);

	ZeroMemory(&m_Mstl, sizeof(D3DMATERIAL9));
	m_Mstl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_Mstl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_Mstl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	ShaderSetup();

	m_pCurState = new cPaladinIdle(this);

	//if (m_pDebuff1 == NULL || m_pDebuff2 == NULL)
	{
		cPopup* popup1 = (cPopup*)ObjectManager->SearchChildUI(TagUI_player_Debuff1);
		cPopup* popup2 = (cPopup*)ObjectManager->SearchChildUI(TagUI_player_Debuff2);
		m_pDebuff1 = popup1;
		m_pDebuff2 = popup2;
	}
}

void cPaladin::ShaderSetup()
{
	LPD3DXEFFECT pShader = g_pShaderManager->GetShader(eShader::Specular_DSL);

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
	
	for(cParts* parts : m_vecParts)
	{
		parts->Update(&m_matWorld);
	}

	//디버프에 따른 효과 적용
	//현재 디버프 지속시간이 20초라 가정
	/*
	switch (m_Debuff)
	{
	case enum_Poison:
		{

			m_EndTime = time(NULL);
			if ((double)m_EndTime - m_StartTime > 20)
			{
				SetDebuff(enum_Idle);
			}
			break;
		}
	case enum_Stun:
		{
			m_EndTime = time(NULL);
			if ((double)m_EndTime - m_StartTime > 20)
			{
				SetDebuff(enum_Idle);
			}
			break;
		}
	case enum_Roar:
		{
			m_EndTime = time(NULL);
			if ((double)m_EndTime - m_StartTime > 20)
			{
				SetDebuff(enum_Idle);
			}
			break;
		}
	default:
		break;
	}
	*/

	if (m_pCurState)
		m_pCurState->StateUpdate();
}

void cPaladin::Update(EventType event)
{
	D3DXMATRIXA16 TempRot;
	D3DXMatrixIdentity(&TempRot);

	float delta = g_pTimeManager->GetElapsedTime();
	//float delta = 0.001f;
	static bool isKeyDown = false;

	
	if(m_pCurState->GetStateIndex() >= m_pCurState->Attack3)
	{
		m_fSpeed = 300.f * 0.1f;
	}
	else
	{
		m_fSpeed = 300.0f;
	}

	if (event == EventType::EVENT_ARROW_UP)
	{
		if(m_pCurState->GetStateIndex() == m_pCurState->Idle)
		{
			SafeDelete(m_pCurState);
			m_pCurState = new cPaladinMove(this);
		}
		m_fvelocity = m_fSpeed * delta;
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
		m_fvelocity = m_fSpeed * -0.5f * delta;
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
		if(m_pCurState->GetStateIndex() >= m_pCurState->Attack3)
		{
			dynamic_cast<cPaladinAttack*>(m_pCurState)->ComboAttack();
		}
		else
		{
			SafeDelete(m_pCurState);
			m_pCurState = new cPaladinAttack(this);
		}
	}

	if(event == EventType::EVENT_JUMP)
	{
		SafeDelete(m_pCurState);
		m_pCurState = new cPaladinEvade(this);
	}

	//팔라딘 디버프 상태 테스트
	if (event == EventType::EVENT_NUMPAD_6)
	{
		SetDebuff(enum_Idle);
	}
	if (event == EventType::EVENT_NUMPAD_7)
	{
		SetDebuff(enum_Poison);
	}
	if (event == EventType::EVENT_NUMPAD_8)
	{
		SetDebuff(enum_Stun);
	}
	if (event == EventType::EVENT_NUMPAD_9)
	{
		SetDebuff(enum_Roar);
	}
}

void cPaladin::Render(D3DXMATRIXA16* pmat)
{
	ShaderRender();
	m_pOBB->OBBBOX_Render(D3DCOLOR_XRGB(255, 255, 255));

	for (cParts* parts : m_vecParts)
	{
		parts->Render();
	}
}

void cPaladin::ShaderRender()
{
	LPD3DXEFFECT pShader = g_pShaderManager->GetShader(eShader::Specular_DSL);

	if (pShader)
	{
		D3DXMATRIXA16	matView;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

		D3DXMATRIXA16	matProjection;
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

		// 쉐이더 전역변수들을 설정
		pShader->SetMatrix("gWorldMatrix", &MatrixIdentity);
		
		D3DXMATRIXA16 matWVP = matView * matProjection;
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

void cPaladin::CollisionProcess(cObject* pObject)
{
	cOBB* pOtherOBB = pObject->GetOBB();
	int	  iOtherTag = pObject->GetTag();

	// 상태 체크 
	if(m_pCurState)
	{
		//if(m_pCurState) 어떤 상태인지 검사
	}

	// 내가 맞을것
	if (mapCollisionList.find(iOtherTag) != mapCollisionList.end())
	{
		// 이미 맞았다면
		return;
	}
	else
	{
		// 어느 부위에 맞을것인지
		if (cOBB::IsCollision(pOtherOBB, m_vecParts[1]->GetOBB()))
		{
			cout << "Body Hit" << endl;
		}

		CollisionInfo info;
		info.dwCollsionTime = GetTickCount();
		info.dwDelayTime = 1500.0f;

		mapCollisionList.insert(pair<int, CollisionInfo>(iOtherTag, info));

	}
}

void cPaladin::StateFeedback()
{
	SafeDelete(m_pCurState);
	m_pCurState = new cPaladinIdle(this);
}

cParts::cParts()
	:m_pOBB(NULL)
	, m_pBone(NULL)
	, m_color(D3DCOLOR_XRGB(255, 255, 255))
	, m_vPos(0, 0, 0)
	, m_vScale(1, 1, 1)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cParts::~cParts()
{
	SafeDelete(m_pOBB);
}

void cParts::Setup(D3DXFRAME* pFrame, D3DXMESHCONTAINER* pMesh, D3DXMATRIXA16* pmat)
{
	m_pOBB = new cOBB;
	m_pOBB->Setup(pFrame, pMesh, pmat);

	m_pBone = (ST_BONE*)pFrame;
}

void cParts::Setup(cSkinnedMesh* pSkinnedMesh, D3DXMATRIXA16* pmat)
{
	m_pOBB = new cOBB;
	m_pOBB->Setup(pSkinnedMesh, pmat);
}

void cParts::Update(D3DXMATRIXA16* pmat)
{
	D3DXMatrixScaling(&m_matScale, m_vScale.x, m_vScale.y, m_vScale.z);

	D3DXMATRIXA16 matRx, matRy, matRz;
	D3DXMatrixRotationX(&matRx, D3DXToRadian(m_vRot.x));
	D3DXMatrixRotationY(&matRy, D3DXToRadian(m_vRot.y));
	D3DXMatrixRotationZ(&matRz, D3DXToRadian(m_vRot.z));
	m_matRot = matRx * matRy * matRz;
	D3DXMatrixTranslation(&m_matTranse, m_vPos.x, m_vPos.y, m_vPos.z);

	m_matWorld = m_matScale * m_matRot * m_matTranse;

	if (pmat)
		m_matWorld *= *pmat;

	m_pOBB->Update(&m_matWorld);
}

void cParts::Render()
{
	m_pOBB->OBBBOX_Render(m_color);
}

void cPaladinWeapon::Setup(D3DXFRAME* pFrame, D3DXMESHCONTAINER* pMesh, D3DXMATRIXA16* pmat)
{
	cParts::Setup(pFrame, pMesh, pmat);
	m_vScale = D3DXVECTOR3(0.4f, 1.0f, 2.5f);
	m_vRot	 = D3DXVECTOR3(-93, -8.0f, 15.0f);
	m_vPos	 = D3DXVECTOR3(-13.0f, 5.0f, 1.0f);
}

void cPaladinWeapon::Update(D3DXMATRIXA16* pmat)
{
	cParts::Update(&m_pBone->CombinedTransformationMatrix);
}

void cPaladinBody::Setup(cSkinnedMesh* pSkinnedMesh, D3DXMATRIXA16* pmat)
{
	cParts::Setup(pSkinnedMesh, pmat);
	m_vScale = D3DXVECTOR3(0.2f, 0.7f, 0.3f);
	m_vRot	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vPos   = D3DXVECTOR3(0.0f, 13.0f, 0.0f);
}

void cPaladinBody::Update(D3DXMATRIXA16* pmat)
{
	cParts::Update(pmat);
}

void cPaladin::CreateTrophies(EventType message)
{

	if (message == EventType::EVENT_SKYBEEZ)
	{
		m_pTrophies = new cTrophies;
		m_pTrophies->Setup("data/UI/Trophies",
			"NW_Attriselect_SkyOrb.png", 
			D3DXVECTOR3(1310, 633, 0), 
			1.0, 
			true, 
			true,
			TAG_UI::TagUI_Trophies_SkyBeez, 
			1000, 
			1000);

		EventManager->Attach((cObserver*)m_pTrophies);
		ObjectManager->AddUIChild((cObject*)m_pTrophies);

	}

	if (message == EventType::EVENT_DRAGONFOOT)
	{
		m_pTrophies = new cTrophies;
		m_pTrophies->Setup("data/UI/Trophies", 
			"NW_Attriselect_Dragonfoot.png", 
			D3DXVECTOR3(1310, 633, 0), 
			1.0, 
			true, true, 
			TAG_UI::TagUI_Trophies_DragonFoot, 
			1000, 
			1000);

		EventManager->Attach((cObserver*)m_pTrophies);
		ObjectManager->AddUIChild((cObject*)m_pTrophies);
	}
}

void cPaladin::SetDebuff(int debuff)
{

	/*
	if (m_Debuff == enum_Idle) 
	{
		m_Debuff = debuff;
		switch (debuff)
		{

		case enum_Poison:
			popup->ChangeSprite("data/UI/InGame/Player_Condition/NW_Poison.png");
			popup->PowerOnOff_OnlySelf();
			m_StartTime = time(NULL);
			break;

		case enum_Stun:
			popup->ChangeSprite("data/UI/InGame/Player_Condition/NW_Stun.png");
			popup->PowerOnOff_OnlySelf();
			m_StartTime = time(NULL);
			break;

		case enum_Roar:
			popup->ChangeSprite("data/UI/InGame/Player_Condition/NW_Roar.png");
			popup->PowerOnOff_OnlySelf();
			m_StartTime = time(NULL);
			break;

		default:
			break;
		}
	}

	if (m_Debuff != enum_Idle && debuff == enum_Idle)
	{
		m_Debuff = debuff;
		popup->PowerOnOff_OnlySelf();
	}
	*/

	switch (debuff)
	{
	case enum_Poison:
		{
			if (vecDebuffFind(enum_Poison) == -1) 
			{
				m_vecDebuff.push_back(enum_Poison);
			}

		}
		break;

	case enum_Stun:
		{
			if ((vecDebuffFind(enum_Stun) == -1))	//스턴이 없을 경우
			{
				if (vecDebuffFind(enum_Roar) == -1) //스턴이 없고 로어도 없을 경우
				{
					m_vecDebuff.push_back(enum_Stun);
				}
				else if (vecDebuffFind(enum_Roar) != -1) //스턴 없고 로어 있을 경우
				{
					//m_vecDebuff[vecDebuffFind(enum_Roar)] 로어부분 삭제하고
					m_vecDebuff.push_back(enum_Stun);
				}
			}
			
		}
		break;

	case enum_Roar:
		{
			if ((vecDebuffFind(enum_Roar) == -1) && (vecDebuffFind(enum_Stun) == -1)) //로어와 스턴 둘 다 없을 경우
			{
				m_vecDebuff.push_back(enum_Roar);
			}
	
		}
		break;

	default:
		break;
	}
	
	if (m_vecDebuff.size() == 1)
	{
		if (m_vecDebuff[0] == enum_Idle) 
		{
			m_pDebuff1->ChangeSprite("");
		}
		else if (m_vecDebuff[0] == enum_Poison)
		{
			m_pDebuff1->ChangeSprite("data/UI/InGame/Player_Condition/NW_Poison.png");
		}
		else if (m_vecDebuff[0] == enum_Stun)
		{
			m_pDebuff1->ChangeSprite("data/UI/InGame/Player_Condition/NW_Stun.png");
		}
		else if (m_vecDebuff[0] == enum_Roar)
		{
			m_pDebuff1->ChangeSprite("data/UI/InGame/Player_Condition/NW_Roar.png");
		}

	}
	else if (m_vecDebuff.size() == 2)
	{
		switch (m_vecDebuff[0])
		{
		case enum_Idle:
		{
			m_pDebuff1->ChangeSprite("");
		}
		break;

		case enum_Poison:
		{
			m_pDebuff1->ChangeSprite("data/UI/InGame/Player_Condition/NW_Poison.png");
		}
		break;

		case enum_Stun:
		{
			m_pDebuff1->ChangeSprite("data/UI/InGame/Player_Condition/NW_Stun.png");
		}
		break;

		case enum_Roar:
		{
			m_pDebuff1->ChangeSprite("data/UI/InGame/Player_Condition/NW_Roar.png");
		}
		break;

		default:
			break;
		}

		switch (m_vecDebuff[1])
		{
		case enum_Idle:
		{
			m_pDebuff2->ChangeSprite("");
		}
		break;

		case enum_Poison:
		{
			m_pDebuff2->ChangeSprite("data/UI/InGame/Player_Condition/NW_Poison.png");
		}
		break;

		case enum_Stun:
		{
			m_pDebuff2->ChangeSprite("data/UI/InGame/Player_Condition/NW_Stun.png");
		}
		break;

		case enum_Roar:
		{
			m_pDebuff2->ChangeSprite("data/UI/InGame/Player_Condition/NW_Roar.png");
		}
		break;

		default:
			break;
		}
	}




	for (int i = 0; i < m_vecDebuff.size(); i++) 
	{
		cout << "vecDebuff [" << i << "] :" << m_vecDebuff[i] << endl;

	}
}

int cPaladin::vecDebuffFind(int debuff)
{
	if (m_vecDebuff.size() > 0)
	{
		for (int i = 0; i < m_vecDebuff.size(); i++)
		{
			if (m_vecDebuff[i] == debuff)
			{
				return i;
			}
		}
	}
	return -1;
}

int cPaladin::GetStateIndex()
{
	return m_pCurState->GetStateIndex();
}
