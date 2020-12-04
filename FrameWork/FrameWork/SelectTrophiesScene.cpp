#include "stdafx.h"
#include "SelectTrophiesScene.h"
#include "ObjectPool.h"



cSelectTrophiesScene::cSelectTrophiesScene(SceneType T)
	:cScene(T)
{
}

cSelectTrophiesScene::~cSelectTrophiesScene()
{
}

void cSelectTrophiesScene::Setup()
{
}

void cSelectTrophiesScene::Reset(int SceneType)
{
	cPopup* popup = NULL;
	switch (SceneType)
	{
	case SceneType::SCENE_TITLE:
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_Title);
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

	popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_Trophies);
	if (popup != NULL) 
	{
		popup->PowerOnOff();
	}


}
