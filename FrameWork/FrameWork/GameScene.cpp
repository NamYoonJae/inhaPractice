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
#include "Paladin.h"
// <<

#include "GameScene.h"
#include "ObjectPool.h"
#include "DragonSoulEater.h"
//

#include "SystemUIEvent.h"
#include "OptionUIEvent.h"
#include "GameSceneUIEvent.h"

//
#include "ObjObject.h"
#include "ObjLoader.h"
#include "ObjMap.h"
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
	// pPopup = new cPopup;
	// pPopup->Setup(파일위치, D3DXVECTOR3(x축 중앙 - 이미지 x크기 - 위치조정, y축 중앙 - 이미지 y 크기 - 위치조정, 0), 배율);
	// pPopup->Setup("data/UI/TitleScene", "게임 타이틀 사이즈 조정.png", D3DXVECTOR3(800 - 450, 450 - 150 - 200, 0), 2, false, false);

	//EventManager->Attach(pPopup);
	//ObjectManager->AddUIChild(pPopup);
	

	//cTerrain* pTerrain = new cTerrain;
	//pTerrain->Setup("data/HeightMapData", "terrain.jpg", "HeightMap.raw");
	//pTerrain->Setup("data/HeightMapData", "Ground_Soil.png", "StageA_Raw.raw",1,600);
	//pTerrain->Setup("data/HeightMapData", "Ground_ClayRough_Moss.png","StageB_Raw.raw");
	//pTerrain->Tagging(Tag::Tag_Map);
	
	//cCharater* player = (cCharater*)ObjectManager->SearchChild(Tag::Tag_Player);
	//ObjectManager->AddStaticChild(pTerrain);
	cObjMap* pMap = new cObjMap("data/ObjFile/NW_Testmap","testmap3.obj");
	pMap->Tagging(Tag::Tag_Map);
	
	pMap->GetScaling(D3DXVECTOR3(0.1f, 1.0f, 0.1f));
	ObjectManager->AddStaticChild(pMap);


	cCamera* Camera = (cCamera*)ObjectManager->SearchChild(Tag::Tag_Camera);

	//
	DragonSoulEater* m_pDragon = new DragonSoulEater;
	m_pDragon->Setup("data/XFile/Dragon", "Basic Attack.X");
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

	cObjMesh *Lava = new cObjMesh;
	Lava->Setup("data/OBjFile/LavaGolem", "fb.obj");
	Lava->Tagging(Tag::Tag_cObj);
	D3DXMATRIX LavaT;
	D3DXMatrixTranslation(&LavaT, -30,30,0);
	Lava->SetWorldMatrix(&LavaT);
	//cObjObject *Lava = new cObjObject;
	//Lava->Setup("data/OBjFile/LavaGolem", "fb.obj");
	//Lava->Tagging(Tag::Tag_cObj);
	ObjectManager->AddChild(Lava);

	cPaladin* Paladin = new cPaladin;
	Paladin->Setup("data/XFile/Paladin", "Pal_Merge.X");
	Paladin->SetPosition(D3DXVECTOR3(10, 0, 0));
	ObjectManager->AddChild(Paladin);
	
#pragma region Popup UI
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cout << "Left : " << rc.left << endl; // 0
	cout << "Right : " << rc.right << endl; // 1584
	cout << "Bottom : " << rc.bottom << endl; //860
	cout << "Top : " << rc.top << endl; // 0

	float nRight = 0.33;
	float nBottom = 0.37;
	
	// TODO 시스템창 불러오기
	cButton * pMediator = new cButton;
	pMediator->Setup(
		"",
		"",
		D3DXVECTOR3(-1,-1,0), 
		0, 0, 0,
		1,
		true, true);
	pMediator->EventProcess = Opton_ESC_Event;
	
	cPopup* pSystemPopUp = Setup_SystemWindow(pMediator);
	cPopup * pOptionPopUp = Setup_OptionWindow(pMediator);
	
	EventManager->Attach(pMediator);
	ObjectManager->AddUIChild(pMediator);
#pragma region Popup UI
	
}

void cGameScene::Reset(int sceneType)
{
	cPopup* popup = NULL;
	switch (sceneType)
	{
	case SceneType::SCENE_TITLE:
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_InGame);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}
		break;


	case SceneType::SCENE_BOSS_2:
		//UI 유지 및 데이터 수정
		break;
		

	case SceneType::SCENE_GAMEOVER:
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_GameOver);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}
		break;

		
	default:
		break;
	}

	popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_InGame);
	if (popup != NULL)
	{
		popup->PowerOnOff();
	}
}
