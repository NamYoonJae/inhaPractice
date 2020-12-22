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

#include "jsonManager.h"

#pragma once
cDragonSoulEater::cDragonSoulEater()
	:m_pSkinnedUnit(NULL)
	, m_pCurState(NULL)
	, m_pvTarget(NULL)
	, m_nPrevStateIndex(0)
{
	JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* p_BOSS_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS");

	m_pOBB = NULL;
	D3DXMatrixIdentity(&m_matRotation);

	m_fCurHeathpoint = m_fMaxHeathPoint = json_Function::object_get_double(p_BOSS_object, "HP");

	m_fPhysicDamage = json_Function::object_get_double(p_BOSS_object, "Attack/Melee");
	m_fElementalDamage = json_Function::object_get_double(p_BOSS_object, "Attack/Elemental");
	
	//m_fPhysicDamage = 200;
	m_fPhysicsDefence = json_Function::object_get_double(p_BOSS_object, "Defence/Melee");
	m_fElementalDefence = json_Function::object_get_double(p_BOSS_object, "Defence/Elemental");

	m_IsRage = false;
	m_fRagegauge = 0.0f;
	m_fStungauge = 0.0f;
	m_nPhase = 1;

	m_IsBreathe = false;
	m_IsFireball = false;
	m_dwSwampCreateCoolTime = 15000.0f;
	m_dwSwampElapsedTime = 0.0f;
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
			m_dwSwampElapsedTime = GetTickCount();
	}

	//if (m_nPhase >= 2 &&
	//	GetTickCount() - m_dwSwampElapsedTime >= m_dwSwampCreateCoolTime)
	//{
	//	iMap *map = (iMap*)ObjectManager->SearchChild(Tag::Tag_Map);
	//	map->CreateSwamp();
	//	map->RenderTrigger();
	//}
	
	if (m_nPhase == 3)
	{
		// 룬스톤 활성화
	}

	CollisionInfoCheck();

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
		if (m_pCurState)
		{
			int nCurStateIndex = m_pCurState->GetIndex();
			int BoxNum = 0;
			switch (nCurStateIndex)
			{
			case 0:
				BoxNum = INT_MAX;
				break;
			case 1:		//머리
				BoxNum = 0;
				break;
			case 2:		//
				BoxNum = 1;
				break;
			default:
				BoxNum = 9;
				break;

			}
			if (BoxNum == INT_MAX)
			{
				// Idle 상태
			}
			else if (BoxNum == 9)
			{
				if (pObject->GetCollsionInfo(m_nTag) == nullptr)
				{
					CollisionInfo info;
					info.dwCollsionTime = GetTickCount();
					info.dwDelayTime = 1500;
					pObject->AddCollisionInfo(m_nTag, info);
				}
			}
			else
			{
				if (cOBB::IsCollision(pOBB, m_vecBoundingBoxList.at(BoxNum).Box))
				{

					if (pObject->GetCollsionInfo(m_nTag) == nullptr)
					{
						CollisionInfo info;
						info.dwCollsionTime = GetTickCount();
						info.dwDelayTime = 1500;
						pObject->AddCollisionInfo(m_nTag, info);

						if (BoxNum == 0)
						{
							g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "BasicAttack");
						}
						else if (BoxNum == 1)
						{
							g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "TailAttack");
						}
					}
				}
			}


		}

		// 내가 맞을것
	//	if (mapCollisionList.find(nTag) != mapCollisionList.end())
	//	{
	//		// 이미 맞았다면
	//		return;
	//	}
	//	else
	//	{
	//		//int i;
	//		// 어느 부위에 맞을것인지
	//		//for (i = 0; i < m_vecBoundingBoxList.size(); ++i)
	//		//{
	//		//	if (cOBB::IsCollision(pOBB, m_vecBoundingBoxList.at(i).Box))
	//		//	{
	//		//		break;
	//		//	}
	//		//}
	//		CollisionInfo info;
	//		info.dwCollsionTime = GetTickCount();
	//		info.dwDelayTime = 500.0f;
	//		AddCollisionInfo(nTag, info);
	//	}

	//}
	}
	else 
	{
		if (m_pCurState)
		{
			int nCurStateIndex = m_pCurState->GetIndex();

			switch (nCurStateIndex)
			{
			case Tag::Tag_SwampA:
			case Tag::Tag_SwampB:
				break;
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
				if(nCurStateIndex != 0)
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

	//static DWORD time = GetTickCount();
	//if (GetTickCount() - time > 1500.0f)
	//{
	//	m_pCurState = (cSoulEaterState*)new cSoulEater_Sleep(this);
	//	return;
	//}


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
	JSON_Object* p_Stage_B_object = g_p_jsonManager->get_json_object_Stage_B();
	JSON_Object* p_BOSS_object = json_Function::object_get_object(p_Stage_B_object, "Stage B/BOSS");



	if (m_fStungauge >= 1000)
	{
		m_pCurState = (cSoulEaterState*)new cSoulEater_Stun(this, json_Function::object_get_double(p_BOSS_object, "Stun/Duration"));
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
