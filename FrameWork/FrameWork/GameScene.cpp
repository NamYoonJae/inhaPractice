#include "stdafx.h"
#include "Camera.h"
#include "BackViewCamera.h"
#include "Grid.h"
#include "SoundManager.h"
//#include "TimerManager.h"
#include "FontManager.h"
#include "FontTmp.h"
//#include "ObjObject.h"
//#include "Observer.h"
#include "cTerrain.h"
#include "Button.h"
#include "cCharater.h"
#include "SkyBox.h"
#include "jsonManager.h"

// >>
#include "SkinnedMesh.h"
#include "Arthur.h"
#include "Paladin.h"
// <<

#include "GameScene.h"
#include "ObjectPool.h"
#include "DragonSoulEater.h"
//

#include "InGamePauseMenuUIEvent.h"
#include "SettingUIEvent.h"
#include "GameSceneUIEvent.h"

//
#include "ObjObject.h"
#include "ObjLoader.h"
#include "ObjMap.h"

#include "LavaGolem.h"


//
#include "Orb.h"
#include "Rune.h"
#include "Wall.h"

#include "ArenaMap.h"
#include "Font.h"
#pragma once

//
#include "SwampA.h"
#include "SwampB.h"


cGameScene::cGameScene(SceneType T)
	:cScene(T)
{
}


cGameScene::~cGameScene()
{
}

void cGameScene::Setup() // boss1map  boss2map
{
	D3DLIGHT9 m_Light;
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
	m_Light.Type = _D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL;
	m_Light.Ambient = D3DXCOLOR(0.7F, 0.7F, 0.7F, 1.0F);
	m_Light.Diffuse = D3DXCOLOR(0.7F, 0.7F, 0.7F, 1.0F);
	m_Light.Specular = D3DXCOLOR(0.7F, 0.7F, 0.7F, 1.0F);
	m_Light.Falloff = 1.0f;
	D3DXVECTOR3 vDir(10.0f, -2.0f,20.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	m_Light.Direction = vDir;
	m_Light.Position = D3DXVECTOR3(500.00, 500.00, -500.00);

	g_pD3DDevice->SetLight(0, &m_Light);
	g_pD3DDevice->LightEnable(0, true);

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

		//cCamera *pCamera;
		cBackViewCamera *pCamera;
		if (ObjectManager->SearchChild(Tag::Tag_Camera) == NULL)
		{
			pCamera = new cBackViewCamera;
			pCamera->Tagging(Tag::Tag_Camera);
		}
		else
		{
			pCamera = (cBackViewCamera*)ObjectManager->SearchChild(Tag::Tag_Camera);
		}
		
		pSkyBox->SetPos(pCamera->GetEye());
		pSkyBox->Tagging(Tag::Tag_SkyBox);

		if(ObjectManager->SearchChild(Tag::Tag_Camera) == NULL)
		{
			EventManager->Attach(pCamera);
			ObjectManager->AddStaticChild(pCamera);	
		}


		//if(ObjectManager->SearchChild(Tag::Tag_Player) == NULL)
		//{
		//	cArthur* pArthur = new cArthur;
		//	pArthur->Setup("data/XFile/Arthur", "arthur_TBorn.X");
		//	pArthur->SetScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
		//	pCamera->Setup(pArthur->GetPos());
		//	pArthur->Tagging(Tag::Tag_Player);
		//	ObjectManager->AddStaticChild(pArthur);
		//}

		cArenaMap* pMap = new cArenaMap;
		pMap->Tagging(Tag::Tag_Map);
		ObjectManager->AddStaticChild(pMap);

		if(ObjectManager->SearchChild(Tag::Tag_Player) == NULL)
		{
			cPaladin* pPaladin = new cPaladin;
			pPaladin->Setup("data/XFile/Paladin", "Pal_Merge.X");
			pCamera->Setup((cCharater*)pPaladin);
			pPaladin->Tagging(Tag::Tag_Player);

			ObjectManager->AddStaticChild(pPaladin);
			EventManager->PushQueue(EventType::EVENT_CREATE_PALADIN);
		}


	}

	cDragonSoulEater* m_pDragon = new cDragonSoulEater;
	m_pDragon->Setup("data/XFile/Dragon", "Merge.X");
	D3DXMATRIXA16 matWorld;
	D3DXMatrixScaling(&matWorld, 0.2f, 0.2f, 0.2f);
	m_pDragon->GetSkinnedMesh().SetTransform(&matWorld);
	m_pDragon->GetSkinnedMesh().SetAnimationIndex(0);

	m_pDragon->GetWorldMatrix(&matWorld);
	m_pDragon->Tagging(Tag::Tag_Boss);
	ObjectManager->AddChild(m_pDragon);
	
#pragma region Map Object
	JSON_Object* pObj = json_Function::object_get_object(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/Object/1/Status/");
	JSON_Array* pAryWallPos = json_object_get_array(pObj, "Position");
	for (size_t i = 0; i < json_array_get_count(pAryWallPos); i++) // 배열의 크기만큼 벽을 생성
	{
		cWall* pWall = new cWall;
		pWall->Tagging(Tag::Tag_Wall);
		pWall->Setup(
			D3DXVECTOR3( // 포지션
				(float)json_object_get_number(json_value_get_object(json_array_get_value(pAryWallPos, i)), "x"),
				(float)json_object_get_number(json_value_get_object(json_array_get_value(pAryWallPos, i)), "y"),
				(float)json_object_get_number(json_value_get_object(json_array_get_value(pAryWallPos, i)), "z")
			)
		);
		ObjectManager->AddChild(pWall);
	}
	cout << json_array_get_count(pAryWallPos) << " Number of Walls generated" << endl;
	//cout << "tmp  :  " << json_object_get_number(json_value_get_object(json_array_get_value(pAryWallPos, 0)), "x") << endl;

	pObj = json_Function::object_get_object(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/Object/3/Status/");
	JSON_Array* pAryRunePos = json_object_get_array(pObj, "Position");
	for (size_t i = 0; i < json_array_get_count(pAryRunePos); i++) // 배열의 크기만큼 벽을 생성
	{
		cRune* pRune = new cRune;
		pRune->Tagging(Tag::Tag_RunStone);
		pRune->Setup(
			D3DXVECTOR3( // 포지션
				(float)json_object_get_number(json_value_get_object(json_array_get_value(pAryRunePos, i)), "x"),
				(float)json_object_get_number(json_value_get_object(json_array_get_value(pAryRunePos, i)), "y"),
				(float)json_object_get_number(json_value_get_object(json_array_get_value(pAryRunePos, i)), "z")
			)
		);
		ObjectManager->AddChild(pRune);
	}
	cout << json_array_get_count(pAryRunePos) << " Number of RunStones generated" << endl;

	pObj = json_Function::object_get_object(g_p_jsonManager->get_json_object_Stage_B(), "Stage B/Object/4/Status/");
	JSON_Array* pAryOrbPos = json_object_get_array(pObj, "Position");
	for (size_t i = 0; i < json_array_get_count(pAryOrbPos); i++) // 배열의 크기만큼 벽을 생성
	{
		cOrb* pOrb = new cOrb;
		pOrb->Tagging(Tag::Tag_Orb);
		pOrb->Setup(
			D3DXVECTOR3( // 포지션
				(float)json_object_get_number(json_value_get_object(json_array_get_value(pAryOrbPos, i)), "x"),
				(float)json_object_get_number(json_value_get_object(json_array_get_value(pAryOrbPos, i)), "y"),
				(float)json_object_get_number(json_value_get_object(json_array_get_value(pAryOrbPos, i)), "z")
			)
		);
		ObjectManager->AddChild(pOrb);
	}
	cout << json_array_get_count(pAryOrbPos) << " Number of Orbs generated"<< endl;

#pragma region Map Object


	/*
	cSwamp* pSwamp1 = new cSwamp;
	pSwamp1->Setup(Tag::Tag_SwampA);
	pSwamp1->SetPos(D3DXVECTOR3(150.0f, 10.0f, 50.0f));
	ObjectManager->AddChild(pSwamp1);
	
	cSwamp* pSwamp2 = new cSwamp;
	pSwamp2->Setup(Tag::Tag_SwampB);
	pSwamp2->SetPos(D3DXVECTOR3(220.0f, 10.0f, 120.0f));
	ObjectManager->AddChild(pSwamp2);
	*/


	
	cSwampA* pSwampA = new cSwampA;
	pSwampA->Setup(Tag::Tag_SwampA);
	pSwampA->SetPos(D3DXVECTOR3(150.0f, 10.0f, 50.0f));
	ObjectManager->AddChild(pSwampA);

	
	cSwampB* pSwampB = new cSwampB;
	pSwampB->Setup(Tag::Tag_SwampB);
	pSwampB->SetPos(D3DXVECTOR3(0.0f, 10.0f, 0.0f));
	ObjectManager->AddChild(pSwampB);
	

	///BGM
	static JSON_Object* p_json_object_setting = g_p_jsonManager->get_json_object_Setting();
	JSON_Object* Sound_object(json_object_get_object(p_json_object_setting, "Sound"));

	g_pSoundManager->AddBGM("data/Sound/BGM/NW_Battle_BGM.mp3");
	g_pSoundManager->SetSFXSOUND((float)json_object_get_number(Sound_object, "SFX") * 0.01f);
	g_pSoundManager->SetBGMSOUND((float)json_object_get_number(Sound_object, "BGM") * 0.01f);
	//g_pSoundManager->SetBGMSOUND(0.3f);
	//g_pSoundManager->SetSFXSOUND(0.3f);
	g_pSoundManager->PlayBGM();
	

	// Font
	//{
	//	cFontTmp* pFontTest = new cFontTmp;

	//	pFontTest->Setup("tmp", eFontType::FONT_SYSTEM);
	//	ObjectManager->AddChild(pFontTest);
	//}



 }

void cGameScene::Reset(int sceneType)
{
	cPopup* popup = NULL;
	switch (sceneType)
	{
	case SceneType::SCENE_TITLE:
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_Title);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}
		break;


	case SceneType::SCENE_BOSS_2:
		//UI 유지 및 데이터 수정
		break;
		

	case SceneType::SCENE_GAMEOVER:
		/*
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_GameOver);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}
		*/
		break;
		
	case SceneType::SCENE_TROPHIES:

		break;
	default:
		break;
	}

	popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_InGame);
	if (popup != NULL)
	{
		popup->PowerOnOff();
	}

	popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_ESC_Menu);
	if (popup != NULL)
	{
		popup->PowerOnOff_OnlySelf(false);
	}
}
