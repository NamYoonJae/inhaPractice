#include "stdafx.h"
#include "Camera.h"
#include "Grid.h"
//#include "TimerManager.h"
//#include "FontManager.h"
//#include "ObjObject.h"
//#include "Observer.h"
#include "cTerrain.h"
#include "Button.h"
#include "cCharater.h"
#include "SkyBox.h"

// >>
#include "SkinnedMesh.h"
#include "Arthur.h"
// <<

#include "GameScene.h"
#include "ObjectPool.h"
#include "DragonSoulEater.h"
//

#include "SystemUIEvent.h"
#include "OptionUIEvent.h"
#include "GameSceneUIEvent.h"
#pragma once


cGameScene::cGameScene(SceneType T)
	:cScene(T)
{
}


cGameScene::~cGameScene()
{
}

void cGameScene::Setup() // boss1map  boss2map
{
	// 
	{
		SkyBox* pSkyBox;

		if (ObjectManager->SearchChild(Tag::Tag_SkyBox) == NULL)
		{
			pSkyBox = new SkyBox;
			pSkyBox->Setup("data/HeightMapData", "Earth.png");
			ObjectManager->AddStaticChild(pSkyBox);
		}
		else
		{
			pSkyBox = (SkyBox*)ObjectManager->SearchChild(Tag::Tag_SkyBox);
		}

		cCamera *pCamera;
		if (ObjectManager->SearchChild(Tag::Tag_Camera) == NULL)
		{
			pCamera = new cCamera;
			pCamera->Tagging(Tag::Tag_Camera);
		}
		else
		{
			pCamera = (cCamera*)ObjectManager->SearchChild(Tag::Tag_Camera);
		}
		
		pSkyBox->SetPos(pCamera->GetEye());
		pSkyBox->Tagging(Tag::Tag_SkyBox);

		if(ObjectManager->SearchChild(Tag::Tag_Camera) == NULL)
		{
			EventManager->Attach(pCamera);
			ObjectManager->AddStaticChild(pCamera);	
		}


		if(ObjectManager->SearchChild(Tag::Tag_Player) == NULL)
		{
			cArthur* pArthur = new cArthur;
			pArthur->Setup("data/XFile/Arthur", "arthur_TBorn.X");
			pArthur->SetScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
			pCamera->Setup(pArthur->GetPos());
			pArthur->Tagging(Tag::Tag_Player);
			ObjectManager->AddStaticChild(pArthur);
		}

		


	}
	// 예외 처리 

	
	cGrid *pGrid = new cGrid;
	pGrid->Setup();

	ObjectManager->AddChild(pGrid);

	// TODO json 파일 쓸 때 대비해서 주석남겨둠
	// pPopup = new cPopUp;
	// pPopup->Setup(파일위치, D3DXVECTOR3(x축 중앙 - 이미지 x크기 - 위치조정, y축 중앙 - 이미지 y 크기 - 위치조정, 0), 배율);
	// pPopup->Setup("data/UI/TitleScene", "게임 타이틀 사이즈 조정.png", D3DXVECTOR3(800 - 450, 450 - 150 - 200, 0), 2, false, false);

	//EventManager->Attach(pPopup);
	//ObjectManager->AddUIChild(pPopup);
	

	cTerrain* pTerrain = new cTerrain;
	//pTerrain->Setup("data/HeightMapData", "terrain.jpg", "HeightMap.raw");
	pTerrain->Setup("data/HeightMapData", "Ground_Soil.png", "StageA_Raw.raw",1,600);
	pTerrain->Tagging(Tag::Tag_Map);
	
	cCharater* player = (cCharater*)ObjectManager->SearchChild(Tag::Tag_Player);

	pTerrain->GetTarget(player->GetPos());
	ObjectManager->AddStaticChild(pTerrain);

	cCamera* Camera = (cCamera*)ObjectManager->SearchChild(Tag::Tag_Camera);

	//
	DragonSoulEater* m_pDragon = new DragonSoulEater;
	m_pDragon->Setup("data/XFile/Dragon", "Model.X");
	D3DXMATRIXA16 matWorld;
	D3DXMatrixScaling(&matWorld, 0.2f, 0.2f, 0.2f);
	m_pDragon->GetSkinnedMesh().SetTransform(&matWorld);
	m_pDragon->GetSkinnedMesh().SetAnimationIndex(0);

	m_pDragon->GetWorldMatrix(&matWorld);
	m_pDragon->Tagging(Tag::Tag_Boss);
	ObjectManager->AddChild(m_pDragon);
	//m_pSkinnedUnit->SetTransform();

	
	//ObjectManager->AddChild(m_pSkinnedUnit);

	D3DLIGHT9 m_Light;
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
	m_Light.Type = _D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL;
	m_Light.Ambient  = D3DXCOLOR(0.7F, 0.7F, 0.7F, 1.0F);
	m_Light.Diffuse  = D3DXCOLOR(0.7F, 0.7F, 0.7F, 1.0F);
	m_Light.Specular = D3DXCOLOR(0.7F, 0.7F, 0.7F, 1.0F);
	D3DXVECTOR3 vDir(0.0f, 5.0f, 5.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	m_Light.Direction = vDir;

	g_pD3DDevice->SetLight(0, &m_Light);
	g_pD3DDevice->LightEnable(0, true);


	
	//	
	//#pragma region jsonfileload
	//	// json에서 파일, 값을 불러와 렌더하는 테스트 코드니까 삭제해도 됩니다.
	//	m_p_jsonValue = json_parse_file("data/json/example box test.json");
	//	m_p_jsonRootObj = json_value_get_object(m_p_jsonValue);
	//
	//	m_p_jsonObjUnit = new cObjMesh;
	//	m_p_jsonObjUnit->Setup(
	//		json_Fuction::object_get_pChar(m_p_jsonRootObj, "Box/FileDirectory"),
	//		json_Fuction::object_get_pChar(m_p_jsonRootObj, "Box/FileName")
	//	);
	//	m_p_jsonObjUnit->SetPosition(
	//		json_Fuction::get_D3DXVECTOR3(m_p_jsonRootObj, "Box/Pos_x", "Box/Pos_y", "Box/Pos_z")
	//	);
	//
	//	m_p_jsonSubObj = json_Fuction::object_get_object(m_p_jsonRootObj, "Box/");
	//	json_object_set_number(m_p_jsonSubObj, "Pos_x", m_p_jsonObjUnit->GetPosition().x - 5.f);
	//	json_object_set_number(m_p_jsonSubObj, "Pos_y", m_p_jsonObjUnit->GetPosition().y + 5.f);
	//	json_object_set_number(m_p_jsonSubObj, "Pos_z", m_p_jsonObjUnit->GetPosition().z - 3.f);
	//	json_serialize_to_file_pretty(m_p_jsonValue, "data/example box test save.json");
	//	
	//	m_p_jsonObjUnit->SetScale(D3DXVECTOR3(0.3f, 0.3f, 0.3f));
	//
	//#pragma endregion jsonfileload


	
#pragma region UI

	// 중개자 역할을 수행하는 임시 cPopUp 객체
	cPopUp * pTmp = new cPopUp();
	// 이미지는 임의로 불러옴
	pTmp->Setup("data/UI/TitleScene", "NW_Titleletter.png",D3DXVECTOR3(-1000, -1000, -100), 1, true, false);

	// TODO 시스템창 불러오기
	Setup_SystemWindow(pTmp);

	EventManager->Attach(pTmp);
	ObjectManager->AddUIChild(pTmp);
	
#pragma region UI
	
}
