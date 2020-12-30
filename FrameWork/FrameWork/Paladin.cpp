#include "stdafx.h"
#include "cOBB.h"
#include "SkinnedMesh.h"
#include "PaladinState.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "FontManager.h"
#include "FontTmp.h"

#include "Paladin.h"

#include "AllocateHierarchy.h"
#include "ArenaMap.h"
#include "cTerrain.h"
#include "ObjectPool.h"
#include "Trophies.h"

#include "PaladinAttack.h"
#include "PaladinEvade.h"
#include "PaladinIdle.h"
#include "PaladinMove.h"
#include "PaladinSpecialAttack.h"
#include "PaladinStun.h"
#include "Orb.h"
#include "Rune.h"
#include "Scene.h"
#include "BackViewCamera.h"
#include "jsonManager.h"

#include "DragonSoulEater.h"
#include "LavaGolem.h"
#include "Wall.h"

cPaladin::cPaladin()
	: m_fvelocity(0.0f)
	, m_isMoving(false)
	, m_pSkinnedUnit(NULL)
	, m_pCurState(NULL)
	//, m_fInvincibleTime(0)
	, m_isInvincible(false)

	, m_Hp(0)
	, m_Stamina(0)
	, m_MaxHp(0)
	, m_MaxStamina(0)
	, m_fSpeed(0)
	, m_IsStaminaState(true)

	, m_Attack_Melee_Damage(0)
	, m_Melee_rate_1(0)
	, m_Melee_rate_2(0)
	, m_Melee_rate_3(0)
	, m_Attack_Elemental_Damage(0)

	, m_Attack_StunRate(0)
	, m_Attack_RigidRate(0)

	, m_Critical_probability(0)
	, m_Critical_Additional_Damage(0)

	, m_Melee_Defense(0)
	, m_Elemental_Defense(0)

	, m_char_Poison_Rate(0)
	, m_Char_Poison_Damage(0)
	, m_Char_Poison_Duration(0)
	, m_Char_StunRate(0)
	, m_Char_Stun_Reduce(0)
	, m_Char_Stun_Duration(0)
	, m_Char_Scream_Duration(0)

	, m_pTrophies(NULL)
	, m_pShadowRenderTarget(NULL)
	, m_pShadowDepthStencil(NULL)

	, m_pShadowMap(NULL)
	, m_dwDeverffStartTime(GetTickCount())
	, m_dwDeverffPreTime(100.0f)
	, m_IsChangeScene(false)
	, m_dwStaminaStartTime(GetTickCount())
	, m_dwStaminaPreTime(100.0f)
	, m_isStuned(false)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&TempRot);
}


cPaladin::~cPaladin()
{
	SafeDelete(m_pOBB);
	SafeDelete(m_pCurState);
	SafeDelete(m_pSkinnedUnit);
	SafeDelete(m_pTrophies);

	SafeRelease(m_pShadowRenderTarget);
	SafeRelease(m_pShadowDepthStencil);
	
	for (cParts* parts : m_vecParts)
	{
		SafeDelete(parts);
	}
	m_vecParts.clear();
}

void cPaladin::Setup(char* szFolder, char* szFile)
{
#pragma region json
	// paladin
	{
		JSON_Object* p_root_object = g_p_jsonManager->get_json_object_Character();
		JSON_Object* p_Character_object = json_object_get_object(p_root_object, "Character");

		m_MaxHp = (int)json_object_get_number(p_Character_object, "Max HP");
		m_MaxStamina = (float)json_Function::object_get_double(p_Character_object, "Stamina/Stamina");
		m_fOriginSpeed = m_fSpeed = (float)json_object_get_number(p_Character_object, "Move speed");

		//m_Hp = 500;
		m_Hp = m_MaxHp;
		//m_Stamina = 500;
		m_Stamina = m_MaxStamina;

		m_StaminaRestoreValue = (float)json_Function::object_get_double(p_Character_object, "Stamina/Restore");

		m_Attack_Melee_Damage = (int)json_Function::object_get_double(p_Character_object, "Attack/Melee");
		m_Melee_rate_1 = (float)json_Function::object_get_double(p_Character_object, "Attack/Melee 1 rate");
		m_Melee_rate_2 = (float)json_Function::object_get_double(p_Character_object, "Attack/Melee 2 rate");
		m_Melee_rate_3 = (float)json_Function::object_get_double(p_Character_object, "Attack/Melee 3 rate");

		m_Attack_Elemental_Damage = (int)json_Function::object_get_double(p_Character_object, "Attack/Elemental");

		m_Attack_StunRate = (float)json_Function::object_get_double(p_Character_object, "Attack/Stun rate");
		m_Attack_RigidRate = (float)json_Function::object_get_double(p_Character_object, "Attack/Rigid rate");
		m_Critical_probability = (float)json_Function::object_get_double(p_Character_object, "Attack/Critical probability");
		m_Critical_Additional_Damage = (float)json_Function::object_get_double(p_Character_object, "Attack/Critical additional damage");

		m_Melee_Defense = (int)json_Function::object_get_double(p_Character_object, "Defense/Melee");
		m_Elemental_Defense = (int)json_Function::object_get_double(p_Character_object, "Defense/Elemental");


		m_Char_Poison_Damage = (int)json_Function::object_get_double(p_Character_object, "Dot damage/Poison/Damage");
		m_Char_Poison_Duration = (int)json_Function::object_get_double(p_Character_object, "Dot damage/Poison/Duration time");

		m_Char_StunRate = 0;
		m_Char_Stun_Reduce = (int)json_Function::object_get_double(p_Character_object, "Stun/Rate reduce");
		m_Char_Stun_Duration = (int)json_Function::object_get_double(p_Character_object, "Stun/Duration time");
		m_Char_Scream_Duration = (int)json_Function::object_get_double(p_Character_object, "Scream/Duration time");

		m_Char_Invincibility_Duration = (float)json_Function::object_get_double(p_Character_object, "Invincibility/Duration time");

		m_Aggro = (int)json_object_get_number(p_Character_object, "Aggro");
	}

	// Log
	{
		cout << "Paladin jsonValue  MaxHp : " << m_MaxHp << endl;
		cout << "Paladin jsonValue  MaxStamina : " << m_MaxStamina << endl;
		cout << "Paladin jsonValue  Stamina Restore Value : " << m_StaminaRestoreValue << endl;
		cout << "Paladin jsonValue  fSpeed : " << m_fSpeed << endl;
		cout << "Paladin jsonValue  Attack_Melee_Damage : " << m_Attack_Melee_Damage << endl;
		cout << "Paladin jsonValue  Melee_rate_1 : " << m_Melee_rate_1 << endl;
		cout << "Paladin jsonValue  Melee_rate_2 : " << m_Melee_rate_2 << endl;
		cout << "Paladin jsonValue  Melee_rate_2 : " << m_Melee_rate_2 << endl;
		cout << "Paladin jsonValue  Attack_Elemental_Damage : " << m_Attack_Elemental_Damage << endl;
		cout << "Paladin jsonValue  Attack_StunRate : " << m_Attack_StunRate << endl;
		cout << "Paladin jsonValue  Attack_RigidRate : " << m_Attack_RigidRate << endl;
		cout << "Paladin jsonValue  Critical_probability : " << m_Critical_probability << endl;
		cout << "Paladin jsonValue  Critical_Additional_Damage : " << m_Critical_Additional_Damage << endl;
		cout << "Paladin jsonValue  Melee_Defense : " << m_Melee_Defense << endl;
		cout << "Paladin jsonValue  Elemental_Defense : " << m_Elemental_Defense << endl;
		cout << "Paladin jsonValue  Char_Poison_Damage : " << m_Char_Poison_Damage << endl;
		cout << "Paladin jsonValue  Char_Poison_Duration : " << m_Char_Poison_Duration << endl;
		cout << "Paladin jsonValue  Char_Stun_reduce : " << m_Char_Stun_Reduce << endl;
		cout << "Paladin jsonValue  Char_Stun_Duration : " << m_Char_Poison_Duration << endl;
		cout << "Paladin jsonValue  Char_Scream_Duration : " << m_Char_Scream_Duration << endl;
		cout << "Paladin jsonValue  Char_Invincibility_Duration : " << m_Char_Invincibility_Duration << endl;
		cout << "Paladin jsonValue  Aggro : " << m_Aggro << endl;
	}

	// object interaction
	{
		JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
		JSON_Object* p_Obj_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/Object/");

		m_Orb_effect_Duration = json_Function::object_get_double(p_Obj_object, "4/Duration");
	}

#pragma endregion json


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

	ShadowShaderSetup();
	ShaderSetup();

	m_pShadowMap = new cPopup;
	m_pShadowMap->Setup(m_pShadowRenderTarget, 2048);
	m_pShadowMap->SetPercent(0.1f);
	m_pShadowMap->SetPosition(D3DXVECTOR2(1000, 0));

	m_pCurState = new cPaladinIdle(this);

	//if (m_pDebuff1 == NULL || m_pDebuff2 == NULL)
	{
		cPopup* popup1 = (cPopup*)ObjectManager->SearchChildUI(TagUI_player_Debuff1);
		cPopup* popup2 = (cPopup*)ObjectManager->SearchChildUI(TagUI_player_Debuff2);

		m_vecDebuff_UI.push_back(popup1);
		m_vecDebuff_UI.push_back(popup2);
	}
}

void cPaladin::ShadowShaderSetup()
{
	const int shadowMapSize = 2048;
	if (FAILED(g_pD3DDevice->CreateTexture(shadowMapSize, shadowMapSize,
		1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F,
		D3DPOOL_DEFAULT, &m_pShadowRenderTarget, NULL)))
	{
		cout << "CreateTexture FAILED" << endl;
	}

	if (FAILED(g_pD3DDevice->CreateDepthStencilSurface(shadowMapSize, shadowMapSize,
		D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, TRUE,
		&m_pShadowDepthStencil, NULL)))
	{
		cout << "CreateDepthStencilSurface FAILED" << endl;
	}

	cArenaMap* pArenaMap = (cArenaMap*)ObjectManager->SearchChild(Tag::Tag_Map);
	
	if(pArenaMap)
	{
		pArenaMap->AddShadowMap(m_pShadowRenderTarget);
		pArenaMap = nullptr;
	}
}

void cPaladin::ShaderSetup()
{
	LPD3DXEFFECT pShader = g_pShaderManager->GetShader(eShader::Specular_DSL);

	D3DLIGHT9   Light;
	g_pD3DDevice->GetLight(0, &Light);
	D3DXVECTOR4 vLightPos = D3DXVECTOR4(Light.Direction.x, Light.Direction.y, Light.Direction.z, 1);
	//D3DXVECTOR4 vLightPos = D3DXVECTOR4(Light.Position.x, Light.Position.y, Light.Position.z, 1);
	D3DXCOLOR c = Light.Diffuse;
	D3DXVECTOR4 LightColor = D3DXVECTOR4(c.r, c.g, c.b, c.a);

	pShader->SetVector("gWorldLightPos", &vLightPos);
	pShader->SetVector("gLightColor", &LightColor);
}

void cPaladin::Update()
{
	if (m_Hp <= 0 && m_IsChangeScene == false) 
	{
		cBackViewCamera* pCamera = (cBackViewCamera*)ObjectManager->SearchChild(Tag::Tag_Camera);
		pCamera->SetUpdate(false);
		m_IsChangeScene = true;
		g_pSceneManager->ChangeScene(SceneType::SCENE_GAMEOVER);
		return;
	}

	//if (m_fvelocity != 0)
	{
		m_vDir = D3DXVECTOR3(0, 0, -1);

		D3DXVec3TransformNormal(&m_vDir, &m_vDir, &TempRot);
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtRH(&matView, &D3DXVECTOR3(0, 0, 0),
			&m_vDir, &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixInverse(&matView, NULL, &matView);
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationY(&matR, m_vCameraRot.y);

		D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matR);

		m_vPos += m_vDir * m_fvelocity;

		D3DXMatrixScaling(&m_matScale, m_vScale.x, m_vScale.y, m_vScale.z);

		D3DXMatrixTranslation(&m_matTranse, m_vPos.x, m_vPos.y, m_vPos.z);

		m_matWorld = m_matScale * matView * matR * m_matTranse;
	}



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

	for (cParts* parts : m_vecParts)
	{
		parts->Update(&m_matWorld);
	}

	DWORD endTime = GetTickCount();

	for (int i = 0; i < m_vecDebuff.size(); i++)
	{
		switch (m_vecDebuff[i])
		{
		case enum_Idle:
			break;

		case enum_Poison:
			// if (endTime - m_vecDebuffStartTime[i] >= 10000)
			if (endTime - m_vecDebuffStartTime[i] >= m_Char_Poison_Duration) // Attribute Character  posion Duration 값 적용
			{
				m_vecDebuff_UI[m_vecDebuff.size() - 1]->ChangeSprite("data/UI/InGame/Player_Condition/Condition_None.png");
				m_vecDebuff.erase(m_vecDebuff.begin() + i);
				m_vecDebuffStartTime.erase(m_vecDebuffStartTime.begin() + i);
				ReloadSpriteDebuff();

			}
			break;

		case enum_Stun:
			//if (endTime - m_vecDebuffStartTime[i] >= 5000)
			if (endTime - m_vecDebuffStartTime[i] >= m_Char_Stun_Duration) // Attribute Character  Stun Duration 값 적용
			{
				m_vecDebuff_UI[m_vecDebuff.size() - 1]->ChangeSprite("data/UI/InGame/Player_Condition/Condition_None.png");
				m_vecDebuff.erase(m_vecDebuff.begin() + i);
				m_vecDebuffStartTime.erase(m_vecDebuffStartTime.begin() + i);
				ReloadSpriteDebuff();

			}
			break;

		case enum_Roar:
			//if (endTime - m_vecDebuffStartTime[i] >= 5000)
			if (endTime - m_vecDebuffStartTime[i] >= m_Char_Scream_Duration) // Attribute Character  Scream Duration 값 적용
			{
				m_vecDebuff_UI[m_vecDebuff.size() - 1]->ChangeSprite("data/UI/InGame/Player_Condition/Condition_None.png");
				m_vecDebuff.erase(m_vecDebuff.begin() + i);
				m_vecDebuffStartTime.erase(m_vecDebuffStartTime.begin() + i);
				ReloadSpriteDebuff();

			}
			break;

		default:
			break;
		}
	}


	if (m_pCurState)
		m_pCurState->StateUpdate();

	// 필수
	//CollisionInfoCheck();


	if (GetTickCount() - m_dwDeverffStartTime >= m_dwDeverffPreTime)
	{
		if (SearchDebuff(enum_Poison))
		{
			m_Hp -= 1;
			//m_Hp -= 독데미지;

			//JSON_Object* pBoss = json_Function::object_get_object(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/BOSS/");
			//JSON_Object* pBossSkill = json_Function::object_get_object(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/BOSS SKILL/");
			//json_Function::object_get_double(pBoss, "Attack/");
			//json_Function::object_get_double(pBossSkill, "SKILL 3/Attribute/Melee Rate");
			g_pLogger->ValueLog(__FUNCTION__, __LINE__, "f",m_Hp);
		}

		if (SearchDebuff(enum_Stun))
		{
			//스턴 애니메이션
		}

		if (SearchDebuff(enum_Roar))
		{
			//경직 애니메이션
		}
		
		m_dwDeverffStartTime = GetTickCount();
	}

	//팔라딘 동작중에는 스태미너 막기 // 스턴치 감소 처리 추가
	if (m_IsStaminaState == true)
	{
		//m_Stamina += 0.3;
		if (GetTickCount() - m_dwStaminaPreTime >= m_dwStaminaPreTime)
		{
			//m_Stamina += 0.5;
			m_Stamina += m_StaminaRestoreValue;

			if (m_Stamina >= m_MaxStamina)
			{
				m_Stamina = m_MaxStamina;
			}

			if (0 < m_Char_StunRate) //
			{
				m_Char_StunRate -= m_Char_Stun_Reduce * 0.1;
			}
		}
	}

}

void cPaladin::Update(EventType event)
{
	if (m_isStuned)
	{
		m_fvelocity = 0;
		return;
	}
	
	JSON_Object* p_root_object = g_p_jsonManager->get_json_object_Character();
	JSON_Object* p_Character_object = json_object_get_object(p_root_object, "Character");

	//D3DXMATRIXA16 TempRot;
	//D3DXMatrixIdentity(&TempRot);

	//float delta = g_pTimeManager->GetElapsedTime();
	float delta = 0.001f;
	static bool isKeyDown = false;


	if (m_pCurState->GetStateIndex() >= m_pCurState->Attack3)
	{
		m_fSpeed = (float)json_object_get_number(p_Character_object, "Move speed") * 0.1f;
	}
	else
	{
		m_fSpeed = (float)json_object_get_number(p_Character_object, "Move speed");
	}

	if (event == EventType::EVENT_ARROW_UP)
	{
		D3DXMatrixRotationY(&TempRot, 0);
		m_fvelocity = m_fSpeed * delta;
		isKeyDown = true;
	}
	if (event == EventType::EVENT_ARROW_LEFT)
	{
		D3DXMatrixRotationY(&TempRot, D3DX_PI * 1.5);
		m_fvelocity = m_fSpeed * delta;
		isKeyDown = true;
	}
	if (event == EventType::EVENT_ARROW_DOWN)
	{
		D3DXMatrixRotationY(&TempRot, D3DX_PI);
		m_fvelocity = m_fSpeed * delta;
		isKeyDown = true;
	}
	if (event == EventType::EVENT_ARROW_RIGHT)
	{
		m_fvelocity = m_fSpeed * delta;
		D3DXMatrixRotationY(&TempRot, D3DX_PI * 0.5);
		isKeyDown = true;
	}
	if (event == EventType::EVENT_UPLEFT)
	{
		m_fvelocity = m_fSpeed * delta;
		D3DXMatrixRotationY(&TempRot, D3DX_PI * 1.5 + D3DX_PI / 6);
		isKeyDown = true;
	}
	if (event == EventType::EVENT_UPRIGHT)
	{
		m_fvelocity = m_fSpeed * delta;
		D3DXMatrixRotationY(&TempRot, D3DX_PI * 0.5 - D3DX_PI / 6);
		isKeyDown = true;
	}
	if (event == EventType::EVENT_DOWNLEFT)
	{
		m_fvelocity = m_fSpeed * delta;
		D3DXMatrixRotationY(&TempRot, D3DX_PI + D3DX_PI / 6);
		isKeyDown = true;
	}
	if (event == EventType::EVENT_DOWNRIGHT)
	{
		m_fvelocity = m_fSpeed * delta;
		D3DXMatrixRotationY(&TempRot, D3DX_PI - D3DX_PI / 6);
		isKeyDown = true;
	}



	if (event == EventType::EVENT_KEYUP && isKeyDown)
	{
		m_fvelocity = 0;
		isKeyDown = false;

		if (m_pCurState->GetStateIndex() == m_pCurState->Run)
		{
			SafeDelete(m_pCurState);
			m_pCurState = new cPaladinIdle(this);
		}
	}

	if(isKeyDown)
	{
		if (m_pCurState->GetStateIndex() == m_pCurState->Idle)
		{
			SafeDelete(m_pCurState);
			m_pCurState = new cPaladinMove(this);
		}
	}
	

	static int n = 0;

	if (event == EventType::EVENT_LBUTTONDOWN)
	{
		if (m_pCurState->GetStateIndex() >= m_pCurState->Attack3)
		{
			dynamic_cast<cPaladinAttack*>(m_pCurState)->ComboAttack();

		}
		else
		{
			if (m_Stamina > 5.0f)
			{
				m_Stamina -= 50;
				if (m_Stamina < 0.0f) m_Stamina = 0.0f;
				SafeDelete(m_pCurState);
				m_pCurState = new cPaladinAttack(this);
			}
			m_IsStaminaState = false;
		}
	}

	if (event == EventType::EVENT_RBUTTONDOWN)
	{
		if (m_pCurState->GetStateIndex() == m_pCurState->Idle ||
			m_pCurState->GetStateIndex() == m_pCurState->Run ||
			m_pCurState->GetStateIndex() == m_pCurState->Walk)
		{
			if (m_Stamina > 5.0f)
			{
				m_Stamina -= 50;
				if (m_Stamina < 0.0f) m_Stamina = 0.0f;

				SafeDelete(m_pCurState);
				if(m_pTrophies->GetTag() == TagUI_Trophies_DragonFoot)
					m_pCurState = new cPaladinSpecialAttack(this, m_pCurState->Kick);
				else if(m_pTrophies->GetTag() == TagUI_Trophies_SkyBeez)
					m_pCurState = new cPaladinSpecialAttack(this, m_pCurState->Roar);
			}
			m_IsStaminaState = false;
		}
	}

	if (event == EventType::EVENT_JUMP)
	{
		if (m_pCurState->GetStateIndex() == m_pCurState->Idle ||
			m_pCurState->GetStateIndex() == m_pCurState->Run  ||
			m_pCurState->GetStateIndex() == m_pCurState->Walk)
		{
			if (m_Stamina > 5.0f)
			{
				m_Stamina -= 100.0f;
				if (m_Stamina < 0.0f) { m_Stamina = 0.0f; };			
			}
			SafeDelete(m_pCurState);
			m_pCurState = new cPaladinEvade(this);
			m_IsStaminaState = false;
		}
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
	//CreateShadow();
	ShaderRender();
	m_pOBB->OBBBOX_Render(D3DCOLOR_XRGB(255, 255, 255));

	for (cParts* parts : m_vecParts)
	{
		parts->Render();
	}

	//m_pShadowMap->Render();
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

void cPaladin::CreateShadow()
{
	LPD3DXEFFECT pShader = g_pShaderManager->GetShader(eShader::CreateShadow);

	if (pShader)
	{
		LPDIRECT3DSURFACE9 pHWBackBuffer = NULL;
		LPDIRECT3DSURFACE9 pHWDepthStencilBuffer = NULL;
		g_pD3DDevice->GetRenderTarget(0, &pHWBackBuffer);
		g_pD3DDevice->GetDepthStencilSurface(&pHWDepthStencilBuffer);

		LPDIRECT3DSURFACE9 pShadowSurface = NULL;
		if (SUCCEEDED(m_pShadowRenderTarget->GetSurfaceLevel(0, &pShadowSurface)))
		{
			g_pD3DDevice->SetRenderTarget(0, pShadowSurface);
			pShadowSurface->Release();
			pShadowSurface = NULL;
		}
		g_pD3DDevice->SetDepthStencilSurface(m_pShadowDepthStencil);

		g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), 0xFFFFFFFF, 1.0f, 0);

		D3DLIGHT9   Light;
		g_pD3DDevice->GetLight(0, &Light);
		//D3DXVECTOR4 vLightPos = D3DXVECTOR4(Light.Direction.x, Light.Direction.y, Light.Direction.z, 1);
		D3DXVECTOR4 vLightPos = D3DXVECTOR4(Light.Position.x, Light.Position.y, Light.Position.z, 1);

		D3DXMATRIXA16 matLightView;
		{
			D3DXVECTOR3 vEyePt(vLightPos.x, vLightPos.y, vLightPos.z);
			D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
			D3DXMatrixLookAtLH(&matLightView, &vEyePt, &vLookatPt, &vUpVec);
		}

		D3DXMATRIXA16 matLightProjection;
		{
			D3DXMatrixPerspectiveFovLH(&matLightProjection, D3DX_PI / 4.0f, 1, 1, 3000);
		}

		pShader->SetMatrix("gWorldMatrix", &MatrixIdentity);
		pShader->SetMatrix("gLightViewMatrix", &matLightView);
		pShader->SetMatrix("gLightProjectionMatrix", &matLightProjection);
		

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

		g_pD3DDevice->SetRenderTarget(0, pHWBackBuffer);
		g_pD3DDevice->SetDepthStencilSurface(pHWDepthStencilBuffer);

		pHWBackBuffer->Release();
		pHWBackBuffer = NULL;
		pHWDepthStencilBuffer->Release();
		pHWDepthStencilBuffer = NULL;

		cArenaMap* pArenaMap = (cArenaMap*)ObjectManager->SearchChild(Tag::Tag_Map);

		if (pArenaMap)
		{
			pArenaMap->ReplaceShadowMap(m_pShadowRenderTarget);
			pArenaMap = nullptr;
		}
	}
}

void cPaladin::CollisionProcess(cObject* pObject)
{
	cOBB* pOtherOBB = pObject->GetOBB();
	int	  iOtherTag = pObject->GetTag();

	if (m_pCurState && (iOtherTag == Tag::Tag_Boss || iOtherTag == Tag::Tag_LavaGolem))
	{
		//내가 공격 중이라면
		if (m_pCurState->GetStateIndex() >= m_pCurState->Attack3 ||
			m_pCurState->GetStateIndex() == m_pCurState->Kick)
		{
			if (cOBB::IsCollision(pOtherOBB, m_vecParts[0]->GetOBB())
				&& pObject->GetCollsionInfo(m_nTag) == nullptr)
			{
				pObject->HitSound();
				PlayAttackSound();
				CollisionInfo info;
				info.dwCollsionTime = GetTickCount();
				info.dwDelayTime = 1500.0f;

				g_pLogger->ValueLog(__FUNCTION__, __LINE__, "ds", iOtherTag, "iOtherTag");

#pragma region Paladin to Monster damage
				// To BOSS
				if (pObject->GetTag() == Tag::Tag_Boss)
				{
					srand(GetTickCount());
					int iDamage = 0;
					cDragonSoulEater* pDragon = (cDragonSoulEater*)pObject;

					bool bIsCritical = m_Critical_probability > (float)rand() / (float)32767 ? true : false;
					bool bDamageType = true;
					float fDamageRate = 0;
					
					switch (m_pCurState->GetStateIndex())
					{
					case cPaladinState::eAnimationSet::Attack1:
						bDamageType = true;
						iDamage = m_Attack_Melee_Damage;
						fDamageRate = m_Melee_rate_1;
						break;
					case cPaladinState::eAnimationSet::Attack2:
						bDamageType = true;
						iDamage = m_Attack_Melee_Damage;
						fDamageRate = m_Melee_rate_2;
						break;
					case cPaladinState::eAnimationSet::Attack3:
						bDamageType = true;
						iDamage = m_Attack_Melee_Damage;
						fDamageRate = m_Melee_rate_3;
						break;
					case cPaladinState::eAnimationSet::Kick:
						{
							fDamageRate = json_Function::object_get_double(g_p_jsonManager->get_json_object_Trophies(), "Trophy/Dragonfoot/Active/Melee rate");
							iDamage = m_Attack_Melee_Damage;
							bIsCritical = true;
							g_pLogger->ValueLog(__FUNCTION__, __LINE__, "fs", fDamageRate, " Trophy/Dragonfoot/Active/Melee rate");
						}
						break;
					case cPaladinState::eAnimationSet::Roar:
						{
							iDamage = m_Attack_Melee_Damage + m_Attack_Elemental_Damage;
							fDamageRate = 1;
							bDamageType = false;
						}
						break;
					}

					iDamage = iDamage * fDamageRate;
					if (bIsCritical)
						iDamage += m_Critical_Additional_Damage;


					if (0 < iDamage)
					{
						pObject->AddCollisionInfo(m_nTag, info, iDamage, bDamageType, 10.0f);

						g_pLogger->ValueLog(__FUNCTION__, __LINE__, "fs", pDragon->GetSTUN(), " Dragon Stun Gauge");
						g_pLogger->ValueLog(__FUNCTION__, __LINE__, "fs", pDragon->GetRigid(), " Dragon Rigid Gauge");
						g_pLogger->ValueLog(__FUNCTION__, __LINE__, "fs", pDragon->GetCURHP(), " Dragon Current HP");
					}
				}

				// To LavaGolem // 테스트 안됨
				if (pObject->GetTag() == Tag::Tag_LavaGolem)
				{
					pObject->AddCollisionInfo(m_nTag, info, 1);
				}
#pragma endregion 
			}

		}
	}


//	// 벽을 공격하는 것에 대한 처리
//	if (m_pCurState && (iOtherTag == Tag::Tag_Wall))
//	{
//		//내가 공격 중이라면
//		if (m_pCurState->GetStateIndex() >= m_pCurState->Attack3)
//		{
//			if (cOBB::IsCollision(pOtherOBB, m_vecParts[0]->GetOBB())
//				&& pObject->GetCollsionInfo(m_nTag) == nullptr)
//			{
//				pObject->HitSound();
//				CollisionInfo info;
//				info.dwCollsionTime = GetTickCount();
//				info.dwDelayTime = 1500.0f;
//				pObject->AddCollisionInfo(m_nTag, info);
//
//#pragma region Paladin to Wall
//				cWall* pWall = (cWall*)pObject;
//				pWall->SetCurHP(pWall->GetCurHP() - 1);
//
//				cout << "Wall HP" << pWall->GetCurHP() << endl;
//#pragma endregion
//			}
//		}
//	}

	cOBB* pObb;
	D3DXMATRIXA16 matW;
	switch (iOtherTag)
	{

	case Tag::Tag_Orb:
	{
		//팔라딘 피 회복 및 해당 오브 제거
		cOrb* pOrb = (cOrb*)pObject;
		//pObb = pOrb->GetOBB();
		//matW = pOrb->GetOBB()->GetWorldMatrix();

		if (pOrb->GetOnOff() == true)
		{
			if (cOBB::IsCollision(m_vecParts[1]->GetOBB(), pOrb->GetOBB())
				&& pOrb->GetCollsionInfo(m_nTag) == nullptr)
			{
				m_Hp += 250;
				if (m_Hp >m_MaxHp)
				{
					m_Hp = m_MaxHp;
				}
			}
		}

	}
		return;

	case Tag::Tag_RunStone:
	{
		cRune* pRune = (cRune*)pObject;

		pObb = pRune->GetSubOBB();
		matW = pRune->GetSubOBB()->GetWorldMatrix();
	}
		break;
	case Tag::Tag_SwampA: // 늪
	case Tag::Tag_SwampB: // 보스 장판
	case Tag::Tag_FireBall:
	case Tag::Tag_Breath:
		return;
	default:
		pObb = pOtherOBB;
		matW = pObb->GetWorldMatrix();
		break;
	}

	D3DXVECTOR3 vOtherPos = pObject->GetPos();
	float dist = pow(m_vPos.x - vOtherPos.x, 2)
		+ pow(m_vPos.z - vOtherPos.z, 2);

	D3DXVECTOR3 vOtherPoint0 = pObb->GetList().at(0);
	
	D3DXVec3TransformCoord(&vOtherPoint0, &vOtherPoint0, &matW);
	float Radian0 = pow(vOtherPos.x - vOtherPoint0.x, 2) + pow(vOtherPos.z - vOtherPoint0.z, 2);

	D3DXVECTOR3 vPoint0 = m_vecParts.at(1)->GetOBB()->GetList().at(0);
	matW = m_pOBB->GetWorldMatrix();
	D3DXVec3TransformCoord(&vPoint0, &vPoint0, &matW);
	float Radian1 = pow(m_vPos.x - vPoint0.x, 2) + pow(m_vPos.z - vPoint0.z, 2);

	float Radian = Radian0 + Radian1;

	if (dist <= Radian && m_pCurState->GetStateIndex() == cPaladinState::eAnimationSet::Run)
	{
		D3DXVECTOR3 vDir = vOtherPos - m_vPos;
		D3DXMATRIXA16 matRy;
		D3DXMatrixRotationY(&matRy, D3DX_PI);
		D3DXVec3TransformNormal(&vDir, &vDir, &matRy);
		vDir.y = 0;
		D3DXVec3Normalize(&vDir, &vDir);
		D3DXVECTOR3 Pos = m_vPos;
		while (dist < Radian)
		{
			Pos += vDir * m_fvelocity;
			dist = pow(Pos.x - vOtherPos.x, 2)
				+ pow(Pos.z - vOtherPos.z, 2);

			if (sqrt(pow(Pos.x, 2) + pow(Pos.z, 2)) > 520)
			{
				return;
			}
		}

		m_vPos = Pos;

	}


}

void cPaladin::StateFeedback()
{
	SafeDelete(m_pCurState);
	m_pCurState = new cPaladinIdle(this);
	m_IsStaminaState = true;
}

cParts::cParts()
	: m_pOBB(NULL)
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

	switch (debuff)
	{
	case enum_Poison:
		{
			if (vecDebuffFind(enum_Poison) == -1) 
			{
				m_vecDebuff.push_back(enum_Poison);
				m_vecDebuffStartTime.push_back(GetTickCount());
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
					m_vecDebuffStartTime.push_back(GetTickCount());
				}
				else if (vecDebuffFind(enum_Roar) != -1) //스턴 없고 로어 있을 경우
				{
					int n = vecDebuffFind(enum_Roar);
					m_vecDebuff.erase(m_vecDebuff.begin() + n);
					m_vecDebuffStartTime.erase(m_vecDebuffStartTime.begin() + n);
					
					m_vecDebuff.push_back(enum_Stun);
					m_vecDebuffStartTime.push_back(GetTickCount());
				}
			}
			
		}
	break;

	case enum_Roar:
		{
			if ((vecDebuffFind(enum_Roar) == -1) && (vecDebuffFind(enum_Stun) == -1)) //로어와 스턴 둘 다 없을 경우
			{
				m_vecDebuff.push_back(enum_Roar);
				m_vecDebuffStartTime.push_back(GetTickCount());
			}
	
		}
	break;

	default:
		break;
	}


	ReloadSpriteDebuff();


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

void cPaladin::ReloadSpriteDebuff()
{
	for (int i = 0; i < m_vecDebuff.size(); i++)
	{
		if (m_vecDebuff[i] == enum_Idle)
		{
		}
		else if (m_vecDebuff[i] == enum_Poison)
		{
			m_vecDebuff_UI[i]->ChangeSprite("data/UI/InGame/Player_Condition/NW_Poison.png");
		}
		else if (m_vecDebuff[i] == enum_Stun)
		{
			m_vecDebuff_UI[i]->ChangeSprite("data/UI/InGame/Player_Condition/NW_Stun.png");
		}
		else if (m_vecDebuff[i] == enum_Roar)
		{
			m_vecDebuff_UI[i]->ChangeSprite("data/UI/InGame/Player_Condition/NW_Roar.png");
		}
	}
}

int cPaladin::SearchDebuff(int debuff)
{
	for (int i = 0; i < m_vecDebuff.size(); i++) 
	{
		if (m_vecDebuff[i] == debuff)
		{
			return true;
		}
		
	}
	return false;
}

void cPaladin::AddCollisionInfo(
	int nTag, CollisionInfo Info,
	float fDMG, bool bDamageType,
	float fStunDamage, float fRigidDamage)
{
	if (m_isInvincible)
		return;
	mapCollisionList.insert(pair<int, CollisionInfo>(nTag, Info));

	// 밑에서 데미지처리
	srand(GetTickCount());

	float fResult = 0;
	if (bDamageType)
	{
		fResult = fDMG - m_Melee_Defense;
	}
	else
	{
		fResult = fDMG - m_Elemental_Defense;
	}

	if (0 >= fResult )
		return;

	//GenerateRandomNum(); <<
	random_device rd;
	mt19937_64 gen(rd());
	uniform_real_distribution<> randNum(-fResult * 0.2, fResult * 0.2);

	fResult = fResult + randNum(gen);

	m_Hp = m_Hp - (int)fResult;
	if (0 > m_Hp)
	{
		m_Hp = 0;
	}

	// 이 아래에서 폰트띄우기
	{
		cFontTmp* pDamageFont = new cFontTmp;
		pDamageFont->Tagging(TAG_UI::TagUI_Damage);

		pDamageFont->Setup(to_string((int)fResult), Red);
		D3DXVECTOR3 vPos = m_vPos;
		vPos.y += 30;
		pDamageFont->SetPos(vPos);

		ObjectManager->AddUIChild(pDamageFont);
	}

	// 스턴치 경직치 처리
	m_Char_StunRate += fStunDamage;

	if (100 <= m_Char_StunRate)
	{
		m_Char_StunRate = 0;
		OnStun(true);
	}
	else
	{
		OnStun(false);
	}


}

void cPaladin::PlayAttackSound()
{
	int Min(Paladin_Attack_Hit1), Max(Paladin_Attack_Hit4);
	g_pSoundManager->PlaySFX(GenerateRandomNum(Min, Max));
}

void cPaladin::OnStun(bool isHardStun)
{
	if(m_pCurState->GetStateIndex() != m_pCurState->BodyHit &&
		m_pCurState->GetStateIndex() != m_pCurState->HeadHit)
	{
		SafeDelete(m_pCurState);
		m_pCurState = new cPaladinStun(this, isHardStun);
		m_IsStaminaState = true;
	}
}


//Legacy
/*
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

	long endTime = GetTickCount();

	for (int i = 0; i < m_vecDebuff.size(); i++)
	{
		switch (m_vecDebuff[i])
		{
		case enum_Idle:
			break;

		case enum_Poison:
			if (endTime - m_vecDebuffStartTime[i] >= 5000)
			{
				m_vecDebuff_UI[m_vecDebuff.size()-1]->ChangeSprite("data/UI/InGame/Player_Condition/Condition_None.png");
				m_vecDebuff.erase(m_vecDebuff.begin() + i);
				m_vecDebuffStartTime.erase(m_vecDebuffStartTime.begin() + i);
				ReloadSpriteDebuff();

			}
			break;

		case enum_Stun:
			if (endTime - m_vecDebuffStartTime[i] >= 5000)
			{
				m_vecDebuff_UI[m_vecDebuff.size()-1]->ChangeSprite("data/UI/InGame/Player_Condition/Condition_None.png");
				m_vecDebuff.erase(m_vecDebuff.begin() + i);
				m_vecDebuffStartTime.erase(m_vecDebuffStartTime.begin() + i);
				ReloadSpriteDebuff();

			}
			break;

		case enum_Roar:
			if (endTime - m_vecDebuffStartTime[i] >= 5000)
			{
				m_vecDebuff_UI[m_vecDebuff.size()-1]->ChangeSprite("data/UI/InGame/Player_Condition/Condition_None.png");
				m_vecDebuff.erase(m_vecDebuff.begin() + i);
				m_vecDebuffStartTime.erase(m_vecDebuffStartTime.begin() + i);
				ReloadSpriteDebuff();

			}
			break;

		default:
			break;
		}
	}


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
*/