#include "stdafx.h"
#include "GameOverScene.h"
#include "ObjectPool.h"

#pragma once


cGameOverScene::cGameOverScene(SceneType T)
	:cScene(T)
{
}

cGameOverScene::~cGameOverScene()
{
}

void cGameOverScene::Setup()
{


}

// 
void cGameOverScene::Reset(int sceneType)
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

	case SceneType::SCENE_BOSS_1:
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_InGame);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}
		break;


	case SceneType::SCENE_BOSS_2:
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_InGame);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}
		break;



	default:
		break;
	}

	popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_GameOver);
	if (popup != NULL)
	{
		popup->PowerOnOff();
	}
}
