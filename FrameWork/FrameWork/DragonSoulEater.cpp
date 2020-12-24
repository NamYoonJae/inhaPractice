#include "stdafx.h"
#include "TextureManager.h"
#include "DragonSoulEater.h"
#include "cOBB.h"
#include "AllocateHierarchy.h"
#include "ObjectPool.h"
#include "cCharater.h"

#include "SoulEaterState.h"
#include "SoulEater_Idle.h"
#include "SoulEater_BasicAttack.h"
#include "SoulEater_TailAttack.h"
#include "SoulEater_Rush.h"
#include "SoulEater_Scream.h"
#include "SoulEater_FireBall.h"
#include "SoulEater_Sleep.h"
#include "SoulEater_Breath.h"
#include "SoulEater_Flood.h"
#include "SoulEater_Stun.h"
#include "LavaFlood.h"
#include "Map.h"
#include "SoundManager.h"
#include "Paladin.h"
#include "jsonManager.h"

#pragma once

cDragonSoulEater::cDragonSoulEater()
	:m_pSkinnedUnit(NULL)
	, m_pCurState(NULL)
	, m_pvTarget(NULL)
	, m_nPrevStateIndex(0)
{
	m_fPhysicDamage = 200;

	m_pOBB = NULL;
	D3DXMatrixIdentity(&m_matRotation);

	m_IsRage = false;
	m_fRagegauge = 0.0f;
	m_fStungauge = 0.0f;
	m_nPhase = 1;

	m_IsBreathe = false;
	m_IsFireball = false;

	//m_dwSwampCreateCoolTime = 15000.0f;
	//m_dwSwampElapsedTime = 0.0f;

	//
	m_nTestStateIndex = INT_MAX;
}


cDragonSoulEater::~cDragonSoulEater()
{
	SafeDelete(m_pOBB);
	SafeDelete(m_pCurState);
	SafeDelete(m_pSkinnedUnit);
}

void cDragonSoulEater::Update()
{	
	m_pSkinnedUnit->Update();

	D3DXMATRIXA16 matOBB,matT;
	

	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.2, 0.2, 0.2);
	matOBB = m_matRotation * matT;

	m_pOBB->Update(&matOBB);
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matOBB = matS *m_matRotation *matT;



	ST_BONE* pBone;

	for (int i = 0; i < m_vecBoundingBoxList.size(); ++i)
	{
		pBone = (ST_BONE*)D3DXFrameFind(m_pSkinnedUnit->GetFrame(),
			&m_vecBoundingBoxList.at(i).szName[0]);
		
		D3DXMatrixScaling(&matS, m_vecBoundingBoxList.at(i).m_vScale.x,
			m_vecBoundingBoxList.at(i).m_vScale.y, 
			m_vecBoundingBoxList.at(i).m_vScale.z);

		matOBB = matS * (pBone->CombinedTransformationMatrix) *m_matRotation *matT;

		m_vecBoundingBoxList.at(i).Box->Update(&matOBB);
	}


	if (m_pvTarget == NULL)
	{
		cCharater* pObj = (cCharater*)ObjectManager->SearchChild(Tag::Tag_Player);
		m_pvTarget = pObj->GetpPos();
	}

	if (m_pCurState)
		m_pCurState->handle();

	if(	(m_fCurHeathpoint <= m_fMaxHeathPoint * 0.8 && m_nPhase == 1) ||
		(m_fCurHeathpoint <= m_fMaxHeathPoint * 0.5 && m_nPhase == 2) ||
		(m_fCurHeathpoint <= m_fMaxHeathPoint * 0.3 && m_nPhase == 3))
	{
		++m_nPhase;
		if (m_nPhase == 2)
		{
			//m_dwSwampElapsedTime = GetTickCount(); // << 사용 안함
			// 오브젝트 풀에서 맵을 SearchChild
			// iMap에 bool값을 True로 변경해주기
		}

	}


	
	if (m_nPhase == 3)
	{
		// 룬스톤 활성화
	}

#ifdef NDEBUG
	for (int i = 0x31; i <= 0x39; i++)
	{
		if (GetKeyState(i) & 0x8000)
		{
			g_pLogger->ValueLog(__FUNCTION__, __LINE__, "sd", "RELEASE", i);
			m_nTestStateIndex = i;
		}
	}
#endif // DEBUG


	//CollisionInfoCheck();

}

void cDragonSoulEater::Render(D3DXMATRIXA16* pmat)
{
	D3DXMATRIXA16 matWorld, matT,
	matR, matRx,matRy,matRz;
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixRotationX(&matRx,m_vRot.x);
	D3DXMatrixRotationY(&matRy,m_vRot.y);
	D3DXMatrixRotationZ(&matRz, m_vRot.z);
	matR = matRx * m_matRotation * matRz;
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);

	matWorld = matR * matT;
	m_pTexture = g_pTextureManager->GetTexture("data/XFile/Dragon/BlueHP.png");
	g_pD3DDevice->SetTransform(D3DTS_WORLD,&matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	
	//ZeroMemory(&m_Mstl, sizeof(D3DXMATRIXA16));
//	g_pD3DDevice->SetMaterial(&m_Mstl);

	g_pD3DDevice->SetMaterial(&m_Mstl);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pSkinnedUnit->Render();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, NULL);
	m_pOBB->OBBBOX_Render(D3DXCOLOR(0,1.0f,0,1.0f));

	for (int i = 0; i < m_vecBoundingBoxList.size(); i++)
		m_vecBoundingBoxList.at(i).Box->OBBBOX_Render(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	

}

void cDragonSoulEater::Setup(char* szFolder, char* szFileName)
{
#pragma region json
	// BOSS
	{
		JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
		JSON_Object* p_BOSS_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS/");

		m_fCurHeathpoint = m_fMaxHeathPoint = json_object_get_number(p_BOSS_object, "HP");

		m_fPhysicDamage = json_Function::object_get_double(p_BOSS_object, "Attack/Melee");
		m_fElementalDamage = json_Function::object_get_double(p_BOSS_object, "Attack/Elemental");

		m_fPhysicsDefence = json_Function::object_get_double(p_BOSS_object, "Defence/Melee");
		m_fElementalDefence = json_Function::object_get_double(p_BOSS_object, "Defence/Elemental");

		m_AttackCooldown = json_Function::object_get_double(p_BOSS_object, "Attack/Cooldown");

		m_RageRate = json_Function::object_get_double(p_BOSS_object, "Rage/Rate");
		m_RageDuration = json_Function::object_get_double(p_BOSS_object, "Rage/Duration");
		m_RageDecreaseDefence = json_Function::object_get_double(p_BOSS_object, "Rage/Decrease Defense");
		m_RageIncreaseAttack = json_Function::object_get_double(p_BOSS_object, "Rage/Increase Attack");

		m_Rigid_Rate = json_Function::object_get_double(p_BOSS_object, "Rigid/Rate");
		m_Rigid_DecreaseRateValue = json_Function::object_get_double(p_BOSS_object, "Rigid/Decrease value");
		m_Rigid_Duration = json_Function::object_get_double(p_BOSS_object, "Rigid/Duration");

		m_Stun_Rate = json_Function::object_get_double(p_BOSS_object, "Stun/Rate");
		m_Stun_Decrease_Value = json_Function::object_get_double(p_BOSS_object, "Stun/Decrease Value");
		m_Stun_Duration = json_Function::object_get_double(p_BOSS_object, "Stun/Duration");

		m_Skill_Weight_1 = json_Function::object_get_double(p_BOSS_object, "SKILL Weight/1");
		m_Skill_Weight_2 = json_Function::object_get_double(p_BOSS_object, "SKILL Weight/2");
		m_Skill_Weight_3 = json_Function::object_get_double(p_BOSS_object, "SKILL Weight/3");
		m_Skill_Weight_4 = json_Function::object_get_double(p_BOSS_object, "SKILL Weight/4");

		m_Speed = json_object_get_number(p_BOSS_object, "Move Speed");
	}

	// BOSS log
	{
		cout << "BOSS_jsonValue  BOSS MAX HP : " << m_fMaxHeathPoint << endl;
		cout << "BOSS_jsonValue  fPhysicDamage : " << m_fPhysicDamage << endl;
		cout << "BOSS_jsonValue  fElementalDamage : " << m_fElementalDamage << endl;
		cout << "BOSS_jsonValue  fPhysicsDefence : " << m_fPhysicsDefence << endl;
		cout << "BOSS_jsonValue  fElementalDefence : " << m_fElementalDefence << endl;
		cout << "BOSS_jsonValue  AttackCooldown : " << m_AttackCooldown << endl;
		cout << "BOSS_jsonValue  RageRate : " << m_RageRate << endl;
		cout << "BOSS_jsonValue  RageDuration : " << m_RageDuration << endl;
		cout << "BOSS_jsonValue  RageDecreaseDefence : " << m_RageDecreaseDefence << endl;
		cout << "BOSS_jsonValue  RageIncreaseAttack : " << m_RageIncreaseAttack << endl;
		cout << "BOSS_jsonValue  Rigid_Rate : " << m_Rigid_Rate << endl;
		cout << "BOSS_jsonValue  Rigid_DecreaseRateValue : " << m_Rigid_DecreaseRateValue << endl;
		cout << "BOSS_jsonValue  Rigid_Duration : " << m_Rigid_Duration << endl;
		cout << "BOSS_jsonValue  Stun_Rate : " << m_Stun_Rate << endl;
		cout << "BOSS_jsonValue  Stun_Decrease_Value : " << m_Stun_Decrease_Value << endl;
		cout << "BOSS_jsonValue  Stun_Duration : " << m_Stun_Duration << endl;
		cout << "BOSS_jsonValue  Skill_Weight_1 : " << m_Skill_Weight_1 << endl;
		cout << "BOSS_jsonValue  Skill_Weight_2 : " << m_Skill_Weight_2 << endl;
		cout << "BOSS_jsonValue  Skill_Weight_3 : " << m_Skill_Weight_3 << endl;
		cout << "BOSS_jsonValue  Skill_Weight_4 : " << m_Skill_Weight_4 << endl;
	}

	// BOSS SKILL status
	{
		JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
		JSON_Object* p_SKILL_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS SKILL/");
		JSON_Object* p_ExtraPattern_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/Extra Pattern/");

		// 기본공격 // 패턴 1
		m_BasicAttack_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 1/Attribute 1/Melee rate");
		m_BasicAttack_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 1/Attribute 1/Elemental rate");
		// 브레스 // 패턴 4
		m_Breath_Duration = json_Function::object_get_double(p_SKILL_object, "SKILL 4/Attribute/Duration");
		m_Breath_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 4/Attribute/Melee rate");
		m_Breath_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 4/Attribute/Elemental rate");;
		// 파이어볼 // 즉사기 패턴
		m_FireBall_Physic_Rate = json_Function::object_get_double(p_ExtraPattern_object, "FireBall/Attribute/Melee rate");
		m_FireBall_Elemental_Rate = json_Function::object_get_double(p_ExtraPattern_object, "FireBall/Attribute/Elemental rate");
		m_FireBall_Range = json_Function::object_get_double(p_ExtraPattern_object, "FireBall/Attribute/Range");
		//// 장판 // 패턴 3 // swamp 로 이동됨
		//m_Flood_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 3/Attribute/Melee rate");
		//m_Flood_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 3/Attribute/Elemental rate");
		//m_Flood_Condition = json_Function::object_get_string(p_SKILL_object, "SKILL 3/Attribute/Condition"); // 상태이상 부여 종류
		//m_Flood_Condition_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 3/Attribute/Condition rate"); // 상태이상 부여치
		// 돌진 // 패턴 2
		m_Rush_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 2/Attribute/Melee rate");
		m_Rush_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 2/Attribute/Elemental rate");
		// 포효 // 포효 패턴
		m_Scream_Range = json_Function::object_get_double(p_ExtraPattern_object, "Scream/Attribute/Range");
		// 수면 // 체력회복 패턴
		m_Sleep_Duration = json_Function::object_get_double(p_ExtraPattern_object, "Sleep/Attribute/Duration");
		// 꼬리치기 // 패턴 1
		m_TailAttack_Physic_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 1/Attribute 2/Melee rate");
		m_TailAttack_Elemental_Rate = json_Function::object_get_double(p_SKILL_object, "SKILL 1/Attribute 2/Elemental rate");
	}

	// BOSS SKILL log
	{
		cout << "BOSS_jsonValue BasicAttack_Physic_Rate : " << m_BasicAttack_Physic_Rate << endl;
		cout << "BOSS_jsonValue BasicAttack_Elemental_Rate : " << m_BasicAttack_Elemental_Rate << endl;
		cout << "BOSS_jsonValue Breath_Duration : " << m_Breath_Duration << endl;
		cout << "BOSS_jsonValue Breath_Physic_Rate : " << m_Breath_Physic_Rate << endl;
		cout << "BOSS_jsonValue Breath_Elemental_Rate : " << m_Breath_Elemental_Rate << endl;
		cout << "BOSS_jsonValue FireBall_Physic_Rate : " << m_FireBall_Physic_Rate << endl;
		cout << "BOSS_jsonValue FireBall_Elemental_Rate : " << m_FireBall_Elemental_Rate << endl;
		cout << "BOSS_jsonValue FireBall_Range : " << m_FireBall_Range << endl;
		//cout << "BOSS_jsonValue Flood_Physic_Rate : " << m_Flood_Physic_Rate << endl;
		//cout << "BOSS_jsonValue Flood_Elemental_Rate : " << m_Flood_Elemental_Rate << endl;
		//cout << "BOSS_jsonValue Flood_Condition : " << m_Flood_Condition << endl;
		//cout << "BOSS_jsonValue Flood_Condition_Rate : " << m_Flood_Condition_Rate << endl;
		cout << "BOSS_jsonValue Rush_Physic_Rate : " << m_Rush_Physic_Rate << endl;
		cout << "BOSS_jsonValue Rush_Elemental_Rate : " << m_Rush_Elemental_Rate << endl;
		cout << "BOSS_jsonValue Scream_Range : " << m_Scream_Range << endl;
		cout << "BOSS_jsonValue Sleep_Duration : " << m_Sleep_Duration << endl;
		cout << "BOSS_jsonValue TailAttack_Physic_Rate : " << m_TailAttack_Physic_Rate << endl;
		cout << "BOSS_jsonValue TailAttack_Elemental_Rate : " << m_TailAttack_Elemental_Rate << endl;
	}

	//// object interaction
	//{
	//	JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
	//	JSON_Object* p_Obj_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/Object/");

	//	m_Wall_Stun_Damage = json_Function::object_get_double(p_Obj_object, "1/Stun Damage");
	//	m_Wall_Rigid_Damage = json_Function::object_get_double(p_Obj_object, "1/Rigid Damage");
	//}

	//// object interaction log
	//{
	//	cout << "OBJ_jsonValue  Wall Stun Damage : " << m_Wall_Stun_Damage << endl;
	//	cout << "OBJ_jsonValue  Wall Rigid Damage : " << m_Wall_Rigid_Damage << endl;
	//}


#pragma endregion json


	m_pSkinnedUnit = new cSkinnedMesh(szFolder, szFileName);
	m_pOBB = new cOBB;

	D3DXMATRIXA16 mat;
	D3DXMatrixScaling(&mat, 0.2, 0.2, 0.2);

	m_pSkinnedUnit->Update();

	if (m_pSkinnedUnit->m_pTransformationMatrix)
		mat *= *m_pSkinnedUnit->m_pTransformationMatrix;

	m_pOBB->Setup(m_pSkinnedUnit, &mat);

	ZeroMemory(&m_Mstl, sizeof(D3DMATERIAL9));
	m_Mstl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_Mstl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_Mstl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	// obb
	D3DXVECTOR3 vecSize;
	D3DXVECTOR3 vecJointOffset;

	LPD3DXFRAME pFrame = m_pSkinnedUnit->GetFrame();
	GetBoundingBoxSize(pFrame,
		pFrame->pMeshContainer,
		&vecSize,
		&vecJointOffset);

	BuildBoneData(0, pFrame, pFrame->pMeshContainer);
	SetupBoundingBox();

	//state
	m_pCurState = (cSoulEaterState*)new cSoulEater_Idle(this);

	//
	m_vPos = D3DXVECTOR3(100, 0, 200);
}


void cDragonSoulEater::GetWorldMatrix(D3DXMATRIXA16* matWorld)
{
	m_matWorld = *matWorld;
}

void cDragonSoulEater::SetupBoundingBox()
{
	if (m_vBoneArray.empty())
		return;

	std::vector<ST_PC_VERTEX> Body, Tail,
		Leg_R, Leg_L,
		Arm_R, Arm_L,
		Wing_R, Wing_L;


	ST_BONE* pBone;

	D3DXMATRIXA16 mat = *m_pSkinnedUnit->m_pTransformationMatrix;
	for (int i = 0; i < m_vBoneArray.size(); ++i)
	{
		string szName = m_vBoneArray.at(i)->szName;

		//pBone = (ST_BONE*)D3DXFrameFind(m_pSkinnedUnit->GetFrame(), szName.c_str());
		//mat = pBone->CombinedTransformationMatrix;
		ST_PC_VERTEX Vertex;
		Vertex.c = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		if (STRCMP(&szName[0], "Spine") ||
			STRCMP(&szName[0], "Chest") ||
			STRCMP(&szName[0], "Neck") ||
			STRCMP(&szName[0], "Head") ||
			STRCMP(&szName[0], "NeckFat_Left") ||
			STRCMP(&szName[0], "NeckFat_Right") ||
			STRCMP(&szName[0], "UpperMouth") ||
			STRCMP(&szName[0], "Jaw") ||
			STRCMP(&szName[0], "Eye_Left") ||
			STRCMP(&szName[0], "Eye_Right") ||
			STRCMP(&szName[0], "JawTip"))
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{

				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				Body.push_back(Vertex);
			}

		}
		else if (STRCMP(&szName[0], "Tail01") ||
			STRCMP(&szName[0], "Tail02") ||
			STRCMP(&szName[0], "Tail03") ||
			STRCMP(&szName[0], "TailEnd"))
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				Tail.push_back(Vertex);
			}
		}
		else if (STRCMP(&szName[0], "UpperLeg_Right")||
			STRCMP(&szName[0], "LowerLeg_Right") || 
			STRCMP(&szName[0], "ReverseLeg_Right") ||
			STRCMP(&szName[0], "Feet_Right") ||
			STRCMP(&szName[0], "Toe_Right"))
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				Leg_R.push_back(Vertex);
			}
		}
		else if (STRCMP(&szName[0], "UpperLeg_Left") ||
			STRCMP(&szName[0], "LowerLeg_Left") ||
			STRCMP(&szName[0], "ReverseLeg_Left") ||
			STRCMP(&szName[0], "Feet_Left") ||
			STRCMP(&szName[0], "Toe_Left"))
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				Leg_L.push_back(Vertex);
			}
		}
		else if (szName[0] == 'W' && szName[szName.size() - 4] == 'L')
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				Wing_L.push_back(Vertex);
			}
		}
		else if (szName[0] == 'W' && szName[szName.size() - 5] == 'R')
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				Wing_R.push_back(Vertex);
			}
		}
		else if (STRCMP(&szName[0],"UpperArm_Right") || 
			STRCMP(&szName[0], "LowerArm_Right") || 
			STRCMP(&szName[0], "Hand_Right") || 
			STRCMP(&szName[0], "HandTip_Right"))
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				Arm_R.push_back(Vertex);
			}
		}
		else if (STRCMP(&szName[0], "UpperArm_Left") ||
			STRCMP(&szName[0], "LowerArm_Left") ||
			STRCMP(&szName[0], "Hand_Left") ||
			STRCMP(&szName[0], "HandTip_Left"))
		{
			for (int j = 0; j < m_vBoneArray.at(i)->vPoints.size(); ++j)
			{
				D3DXVec3TransformCoord(&Vertex.p, &m_vBoneArray.at(i)->vPoints.at(j).p, &mat);
				Arm_L.push_back(Vertex);
			}
		}
	}

	std::vector<cOBB*> vecOBBList;
	D3DXVECTOR3 vMin(0, 0, 0), vMax(0, 0, 0);
	D3DXMATRIXA16 matT, matW;
	D3DXMATRIXA16 matS;
	
	//body
	{

		cOBB* BodyOBB = new cOBB;

		for (int i = 0; i < Body.size(); ++i)
		{
			vMin.x = min(vMin.x, Body.at(i).p.x);
			vMin.y = min(vMin.y, Body.at(i).p.y);
			vMin.z = min(vMin.z, Body.at(i).p.z);

			vMax.x = max(vMax.x, Body.at(i).p.x);
			vMax.y = max(vMax.y, Body.at(i).p.y);
			vMax.z = max(vMax.z, Body.at(i).p.z);
		}

		BodyOBB->Setup(vMin, vMax);
		vecOBBList.push_back(BodyOBB);
	}
	//Tail
	{
		cOBB* TailOBB = new cOBB;
		vMax = vMin = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < Tail.size(); ++i)
		{
			vMin.x = min(vMin.x, Tail.at(i).p.x);
			vMin.y = min(vMin.y, Tail.at(i).p.y);
			vMin.z = min(vMin.z, Tail.at(i).p.z);

			vMax.x = max(vMax.x, Tail.at(i).p.x);
			vMax.y = max(vMax.y, Tail.at(i).p.y);
			vMax.z = max(vMax.z, Tail.at(i).p.z);
		}


		TailOBB->Setup(vMin, vMax);

		vecOBBList.push_back(TailOBB);
	}

	//Leg_Right
	{
		cOBB* UpperLegR = new cOBB;
		vMax = vMin = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < Leg_R.size(); ++i)
		{
			vMin.x = min(vMin.x, Leg_R.at(i).p.x);
			vMin.y = min(vMin.y, Leg_R.at(i).p.y);
			vMin.z = min(vMin.z, Leg_R.at(i).p.z);

			vMax.x = max(vMax.x, Leg_R.at(i).p.x);
			vMax.y = max(vMax.y, Leg_R.at(i).p.y);
			vMax.z = max(vMax.z, Leg_R.at(i).p.z);
		}
		
		//D3DXMatrixScaling(&matS, 1, 1, 0.7);
		//D3DXMatrixTranslation(&matT, 0, 0, -(vMax.z - vMin.z) * 0.5);

		//matW =matS * matT;
		UpperLegR->Setup(vMin, vMax);
		vecOBBList.push_back(UpperLegR);
	}
	//UpperLeg_Left
	{
		cOBB* UpperLegL = new cOBB;
		vMax = vMin = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < Leg_L.size(); ++i)
		{
			vMin.x = min(vMin.x, Leg_L.at(i).p.x);
			vMin.y = min(vMin.y, Leg_L.at(i).p.y);
			vMin.z = min(vMin.z, Leg_L.at(i).p.z);

			vMax.x = max(vMax.x, Leg_L.at(i).p.x);
			vMax.y = max(vMax.y, Leg_L.at(i).p.y);
			vMax.z = max(vMax.z, Leg_L.at(i).p.z);
		}
		//D3DXMatrixScaling(&matS, 1, 1, 0.7);
		//D3DXMatrixTranslation(&matT, 0, 0, -(vMax.z - vMin.z) * 0.5);

		//matW =matS * matT;

		UpperLegL->Setup(vMin, vMax);

		vecOBBList.push_back(UpperLegL);
	}



	//Arm_Right
	{
		cOBB* LowerLegR = new cOBB;
		vMax = vMin = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < Arm_R.size(); ++i)
		{
			vMin.x = min(vMin.x, Arm_R.at(i).p.x);
			vMin.y = min(vMin.y, Arm_R.at(i).p.y);
			vMin.z = min(vMin.z, Arm_R.at(i).p.z);

			vMax.x = max(vMax.x, Arm_R.at(i).p.x);
			vMax.y = max(vMax.y, Arm_R.at(i).p.y);
			vMax.z = max(vMax.z, Arm_R.at(i).p.z);
		}

		LowerLegR->Setup(vMin, vMax);
		
		vecOBBList.push_back(LowerLegR);
	}
	//Arm_Left
	{
		cOBB* LowerLegL = new cOBB;
		vMax = vMin = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < Arm_L.size(); ++i)
		{
			vMin.x = min(vMin.x, Arm_L.at(i).p.x);
			vMin.y = min(vMin.y, Arm_L.at(i).p.y);
			vMin.z = min(vMin.z, Arm_L.at(i).p.z);

			vMax.x = max(vMax.x, Arm_L.at(i).p.x);
			vMax.y = max(vMax.y, Arm_L.at(i).p.y);
			vMax.z = max(vMax.z, Arm_L.at(i).p.z);
		}

		LowerLegL->Setup(vMin, vMax);
		
		vecOBBList.push_back(LowerLegL);
	}
	//Wing_Right
	{
		cOBB* WingR = new cOBB;
		vMax = vMin = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < Wing_R.size(); ++i)
		{
			vMin.x = min(vMin.x, Wing_R.at(i).p.x);
			vMin.y = min(vMin.y, Wing_R.at(i).p.y);
			vMin.z = min(vMin.z, Wing_R.at(i).p.z);

			vMax.x = max(vMax.x, Wing_R.at(i).p.x);
			vMax.y = max(vMax.y, Wing_R.at(i).p.y);
			vMax.z = max(vMax.z, Wing_R.at(i).p.z);
		}

		D3DXMATRIXA16 matS, matT, matW;
		D3DXMatrixScaling(&matS, 1, 0.3, 1);
		D3DXMatrixTranslation(&matT, 0, (vMax.y - vMin.y) * 0.7, 0);

		matW = matS * matT;

		WingR->Setup(vMin, vMax, &matW);

		vecOBBList.push_back(WingR);
	}
	//Wing_Left
	{
		cOBB* WingL = new cOBB;
		vMax = vMin = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < Wing_L.size(); ++i)
		{
			vMin.x = min(vMin.x, Wing_L.at(i).p.x);
			vMin.y = min(vMin.y, Wing_L.at(i).p.y);
			vMin.z = min(vMin.z, Wing_L.at(i).p.z);

			vMax.x = max(vMax.x, Wing_L.at(i).p.x);
			vMax.y = max(vMax.y, Wing_L.at(i).p.y);
			vMax.z = max(vMax.z, Wing_L.at(i).p.z);
		}
		D3DXMATRIXA16 matS, matT, matW;
		D3DXMatrixScaling(&matS, 1, 0.3, 1);
		D3DXMatrixTranslation(&matT, 0, (vMax.y - vMin.y) * 0.7, 0);

		matW = matS * matT;

		WingL->Setup(vMin, vMax, &matW);

		vecOBBList.push_back(WingL);
	}

	//m_vecBoundingBoxList = vecOBBList;
	m_vecBoundingBoxList.resize(vecOBBList.size());
	for (int i = 0; i < vecOBBList.size(); ++i)
	{
		if (m_vecBoundingBoxList.size() <= i) break;
	
		m_vecBoundingBoxList[i].Box = vecOBBList[i];
		
		string szName;
		D3DXVECTOR3 scale;
		switch (i)
		{
			case 0:
				szName = "Head";
				scale = D3DXVECTOR3(3, 4, 2);
				break;
			case 1:
				szName = "TailEnd";
				scale = D3DXVECTOR3(4, 4, 4);
				break;
			case 2:
				szName = "UpperLeg_Right";
				scale = D3DXVECTOR3(4, 4, 4);
				break;
			case 3:
				szName = "UpperLeg_Left";
				scale = D3DXVECTOR3(4, 4, 4);
				break;
			case 4:
				szName = "UpperArm_Right";
				scale = D3DXVECTOR3(4, 4, 4);
				break;
			case 5:
				szName = "UpperArm_Left";
				scale = D3DXVECTOR3(4, 4, 4);
				break;
			case 6:
				szName = "Wing02_Right";
				scale = D3DXVECTOR3(2, 2, 1);
				break;
			case 7:
				szName = "Wing02_Left";
				scale = D3DXVECTOR3(2, 2, 1);
				break;
			default:
				szName = "NULL";
				scale = D3DXVECTOR3(1, 1, 1);
				break;
		}

		m_vecBoundingBoxList[i].szName = szName;
		m_vecBoundingBoxList[i].m_vScale = scale;
		
	}
}

void cDragonSoulEater::CollisionProcess(cObject* pObject)
{
	cOBB* pOBB = pObject->GetOBB();
	int nTag = pObject->GetTag();

	if (nTag == Tag::Tag_Player) // 벽도 필요함 
	{
		// 내가 때릴것
		if (m_pCurState) // << 드래곤상태
		{
			int nCurStateIndex = m_pCurState->GetIndex();
			switch (nCurStateIndex)
			{
			case 1:		// 머리
				if (cOBB::IsCollision(pOBB, m_vecBoundingBoxList.at(0).Box))
				{
					if (pObject->GetCollsionInfo(m_nTag) == nullptr)
					{
						//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "head");
						CollisionInfo info;
						info.dwCollsionTime = GetTickCount();
						info.dwDelayTime = 1500;
						pObject->AddCollisionInfo(m_nTag, info);

						// 스테이트 클래스에서 get매서드로 값 가져오기
					}
				}
				break;
			case 2:		// 
				if (cOBB::IsCollision(pOBB, m_vecBoundingBoxList.at(1).Box))
				{
					if (pObject->GetCollsionInfo(m_nTag) == nullptr)
					{
						//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "tail");
						CollisionInfo info;
						info.dwCollsionTime = GetTickCount();
						info.dwDelayTime = 1500;
						pObject->AddCollisionInfo(m_nTag, info);
					}
				}
				break;
			case 3:
				if (pObject->GetCollsionInfo(m_nTag) == nullptr)
				{
					//g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "Rush");
					CollisionInfo info;
					info.dwCollsionTime = GetTickCount();
					info.dwDelayTime = 1500;
					pObject->AddCollisionInfo(m_nTag, info);
				}
				break;
			}

		}
	}
	else if(nTag == Tag::Tag_RunStone || nTag== Tag::Tag_Wall)
	{
		//if (nTag == Tag::Tag_SwampA || nTag == Tag::Tag_SwampB ||
		//	nTag == Tag::Tag_FireBall || nTag == Tag::Tag_Breath || nTag == Tag::Tag_LavaGolem)
		//	return;
		
		if (m_pCurState)
		{
			int nCurStateIndex = m_pCurState->GetIndex();

			switch (nCurStateIndex)
			{
			default:
			{
				D3DXVECTOR3 vOtherPos = pObject->GetPos();
				float dist = pow(m_vPos.x - vOtherPos.x, 2)
					+ pow(m_vPos.z - vOtherPos.z, 2);

				D3DXVECTOR3 vOtherPoint0 = pOBB->GetList().at(0);
				D3DXMATRIXA16 matW = pOBB->GetWorldMatrix();
				D3DXVec3TransformCoord(&vOtherPoint0, &vOtherPoint0, &matW);
				float Radian0 = pow(vOtherPos.x - vOtherPoint0.x, 2) + pow(vOtherPos.z - vOtherPoint0.z, 2);

				D3DXVECTOR3 vPoint0 = m_pOBB->GetList().at(0);
				matW = m_pOBB->GetWorldMatrix();
				D3DXVec3TransformCoord(&vPoint0, &vPoint0, &matW);
				float Radian1 = pow(m_vPos.x - vPoint0.x, 2) + pow(m_vPos.z - vPoint0.z, 2);

				float Radian = Radian0 + Radian1;
					
				D3DXVECTOR3 vDir; 
				vDir = vOtherPos - m_vPos;
				vDir.y = 0;

				while (dist < Radian)
				{
					m_vPos += -vDir * 0.1;
					dist = pow(m_vPos.x - vOtherPos.x, 2)
						+ pow(m_vPos.z - vOtherPos.z, 2);
				}

				m_vPos += D3DXVECTOR3(0, 0, -0.3);
				if (nCurStateIndex == 3 )
				{
					if (nTag == Tag::Tag_Wall)
					{
						// 유일한 예외 
						CollisionInfo info;
						info.dwCollsionTime = GetTickCount();
						info.dwDelayTime = 1500;
						AddCollisionInfo(nTag, info);
						m_pCurState->handle();
						return;
					}
					else
					{
						this->Request();
						return;
					}
				}
				else if(nCurStateIndex != 0)
					this->m_pCurState->TargetCapture();
			}
				break;
			}

		}

	}
}

void cDragonSoulEater::Request()
{	
	if (m_pCurState && m_pCurState->GetIndex() != 0)
	{
		m_nPrevStateIndex = m_pCurState->GetIndex();
		SafeDelete(m_pCurState);
		m_pCurState = (cSoulEaterState*)new cSoulEater_Idle(this);
		return;
	}
	else
	{
		SafeDelete(m_pCurState);
	}

	//static bool	Check = false;
	//static DWORD time = GetTickCount();
	//if (GetTickCount() - time > 1500.0f && Check == false)
	//{
	//	Check = true;
	//	m_pCurState = (cSoulEaterState*)new cSoulEater_Breath(this);
	//	return;
	//}

#ifdef NDEBUG
	if (m_nTestStateIndex >= 0x31 && m_nTestStateIndex <= 0x39)
	{
		switch (m_nTestStateIndex)
		{
		case 0x31:
			m_pCurState = (cSoulEaterState*)new cSoulEater_BasicAttack(this);
			break;
		case 0x32:
			m_pCurState = (cSoulEaterState*)new cSoulEater_TailAttack(this);
			break;
		case 0x33:
			m_pCurState = (cSoulEaterState*)new cSoulEater_Rush(this);
			break;
		case 0x34:
			m_pCurState = (cSoulEaterState*)new cSoulEater_Scream(this);
			break;
		case 0x35:
			m_pCurState = (cSoulEaterState*)new cSoulEater_FireBall(this);
			break;
		case 0x36:
			m_pCurState = (cSoulEaterState*)new cSoulEater_Sleep(this);
			break;
		case 0x37:
			m_pCurState = (cSoulEaterState*)new cSoulEater_Breath(this);
			break;
		case 0x38:
			m_pCurState = (cSoulEaterState*)new cSoulEater_Flood(this);
			break;
		case 0x39:
			m_pCurState = (cSoulEaterState*)new cSoulEater_Stun(this,8000.0f);
			break;
		}
		return;
	}
#endif // DEBUG


	// TODO Remove
#pragma region before
	//if (m_fStungauge >= 1000)
	//{
	//	m_pCurState = (cSoulEaterState*)new cSoulEater_Stun(this, 8000.0f);
	//	return;
	//}

	//if (m_fRagegauge >= 1000 && !m_IsRage)
	//{
	//	m_pCurState = (cSoulEaterState*)new cSoulEater_Scream(this);
	//	m_IsRage = true;
	//	return;
	//}

	//if(m_IsRage && m_nPhase >= 3 && m_nPrevStateIndex == 4)
	//{
	//	m_pCurState = (cSoulEaterState*)new cSoulEater_FireBall(this);
	//	return;
	//}

	//if (m_fCurHeathpoint <= m_fMaxHeathPoint * 0.2 && m_nPhase >= 3 && m_IsBreathe == false)
	//{
	//	m_IsBreathe = true;
	//	m_pCurState = (cSoulEaterState*)new cSoulEater_Breath(this);
	//	return;
	//}



	//if (m_nPhase >= 2 && (rand() % 255 / 255 > 0.80))
	//{
	//	m_pCurState = (cSoulEaterState*)new cSoulEater_Flood(this);
	//	return;
	//}
	//
	//if (m_pvTarget)
	//{
	//	D3DXVECTOR3 vCurDir = *m_pvTarget - m_vPos;
	//	D3DXVec3Normalize(&vCurDir, &vCurDir);
	//	D3DXVECTOR3 vPrevDir = D3DXVECTOR3(0, 0, -1);
	//	D3DXVec3TransformNormal(&vPrevDir, &vPrevDir, &m_matRotation);

	//	float Radian = acos(D3DXVec3Dot(&vPrevDir, &vCurDir));
	//	float distance = sqrt(pow(m_vPos.x - (*m_pvTarget).x, 2) + pow(m_vPos.z - (*m_pvTarget).z, 2));

	//	if (distance >= 100.0f && m_nPrevStateIndex != 3)
	//	{
	//		//
	//		m_pCurState = (cSoulEaterState*)new cSoulEater_Rush(this);
	//		return;
	//	}
	//	else if (Radian >= D3DX_PI - D3DX_PI * 0.33 && Radian <= D3DX_PI + D3DX_PI * 0.33
	//		&& distance <= 55
	//		&& m_nPrevStateIndex != 2)
	//	{
	//		// 55
	//		m_pCurState = (cSoulEaterState*)new cSoulEater_TailAttack(this);
	//		return;
	//	}
	//	else 
	//	{
	//		m_pCurState = (cSoulEaterState*)new cSoulEater_BasicAttack(this);
	//	}
	//}
#pragma endregion before

#pragma region After
	//JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
	//JSON_Object* p_BOSS_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS");

	if (m_fStungauge >= 100)
	{
		m_pCurState = (cSoulEaterState*)new cSoulEater_Stun(this, m_Stun_Duration);
		return;
	}

	if (m_fRagegauge >= 1000 && !m_IsRage)
	{
		m_pCurState = (cSoulEaterState*)new cSoulEater_Scream(this);
		m_IsRage = true;
		return;
	}

	if (m_IsRage && m_nPhase >= 3 && m_nPrevStateIndex == 4)
	{
		m_pCurState = (cSoulEaterState*)new cSoulEater_FireBall(this);
		return;
	}

	if (m_fCurHeathpoint <= m_fMaxHeathPoint * 0.2 && m_nPhase >= 3 && m_IsBreathe == false)
	{
		m_IsBreathe = true;
		m_pCurState = (cSoulEaterState*)new cSoulEater_Breath(this);
		return;
	}



	if (m_nPhase >= 2 && (rand() % 255 / 255 > 0.80))
	{
		m_pCurState = (cSoulEaterState*)new cSoulEater_Flood(this);
	 	return;
	}

	if (m_pvTarget)
	{
		D3DXVECTOR3 vCurDir = *m_pvTarget - m_vPos;
		D3DXVec3Normalize(&vCurDir, &vCurDir);
		D3DXVECTOR3 vPrevDir = D3DXVECTOR3(0, 0, -1);
		D3DXVec3TransformNormal(&vPrevDir, &vPrevDir, &m_matRotation);

		float Radian = acos(D3DXVec3Dot(&vPrevDir, &vCurDir));
		float distance = sqrt(pow(m_vPos.x - (*m_pvTarget).x, 2) + pow(m_vPos.z - (*m_pvTarget).z, 2));

		if (distance >= 100.0f && m_nPrevStateIndex != 3)
		{
			//
			m_pCurState = (cSoulEaterState*)new cSoulEater_Rush(this);
			return;
		}
		else if (Radian >= D3DX_PI - D3DX_PI * 0.33 && Radian <= D3DX_PI + D3DX_PI * 0.33
			&& distance <= 55
			&& m_nPrevStateIndex != 2)
		{
			// 55
			m_pCurState = (cSoulEaterState*)new cSoulEater_TailAttack(this);
			return;
		}
		else
		{
			m_pCurState = (cSoulEaterState*)new cSoulEater_BasicAttack(this);
		}
	}


#pragma endregion After
}

D3DXVECTOR3 * cDragonSoulEater::GetTarget()
{
	if (m_pvTarget)
		return m_pvTarget;

	return nullptr;
}

int cDragonSoulEater::CurrentStateIndex()
{
	return m_pCurState->GetIndex();
}

void cDragonSoulEater::HitSound()
{
	g_pSoundManager->PlaySFX(GenerateRandomNum((int)eSoundList::Dragon_GetHit1, (int)eSoundList::Dragon_GetHit3));
	return;
}
