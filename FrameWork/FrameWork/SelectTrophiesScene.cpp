#include "stdafx.h"
#include "SelectTrophiesScene.h"
#include "ObjectPool.h"
#include "TrophiesSceneUIEvent.h"


cSelectTrophiesScene::cSelectTrophiesScene(SceneType T)
	:cScene(T)
{
}

cSelectTrophiesScene::~cSelectTrophiesScene()
{
}

void cSelectTrophiesScene::Setup()
{
	//전리품 선택
	cPopup* pTrophiesSelectSceneBackground = new cPopup;
	pTrophiesSelectSceneBackground->Setup("data/UI/Trophies", "NW_Attriselect_Back.png",
		D3DXVECTOR3(0, 0, 0), 0, 0, 0, 1, true, true, TAG_UI::TagUI_SelectTrophies);

	//하늘의 구슬
	cButton* pTropiesBizzButton = new cButton;
	pTropiesBizzButton->Setup("data/UI/Trophies", "NW_Attriselect_Backgound_Off_SkyOrb.png",
		D3DXVECTOR3(280, 230, 0), 0, 0, 0, 1, true, true);
	pTrophiesSelectSceneBackground->cButtonPushBack(pTropiesBizzButton);
	pTropiesBizzButton->EventProcess = SelectSkyBizzEvent;

	cButton* pTrophiesImage = new cButton;
	pTrophiesImage->Setup("data/UI/Trophies", "NW_Attriselect_SkyOrb.png",
		D3DXVECTOR3(435, 375, 0), 0, 0, 0, 1, true, true);
	pTropiesBizzButton->cButtonPushBack(pTrophiesImage);


	//용발
	pTropiesBizzButton = new cButton;
	pTropiesBizzButton->Setup("data/UI/Trophies", "NW_Attriselect_Backgound_Off_DragonFoot.png",
		D3DXVECTOR3(890, 230, 0), 0, 0, 0, 1, true, true);
	pTrophiesSelectSceneBackground->cButtonPushBack(pTropiesBizzButton);
	pTropiesBizzButton->EventProcess = SelectDragonFootEvent;

	pTrophiesImage = new cButton;
	pTrophiesImage->Setup("data/UI/Trophies", "NW_Attriselect_Dragonfoot.png",
		D3DXVECTOR3(1045, 375, 0), 0, 0, 0, 1, true, true);
	pTropiesBizzButton->cButtonPushBack(pTrophiesImage);

	EventManager->Attach(pTrophiesSelectSceneBackground);
	ObjectManager->AddUIChild(pTrophiesSelectSceneBackground);

}

void cSelectTrophiesScene::Reset(int SceneType)
{
	
	cPopup* popup = NULL;
	switch (SceneType)
	{
	case SceneType::SCENE_BOSS_1:
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_InGame);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}

		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_player_Debuff1);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}

		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_player_Debuff2);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}

		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_Hp);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}

		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_Stamina);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}

		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_TrophiesGauge);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}

		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_ESC_Menu);
		if (popup != NULL)
		{
			popup->PowerOnOff_OnlySelf(true);
		}

		break;
	default:
		break;
	}

	popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_SelectTrophies);
	EventManager->Detach(*popup);
	ObjectManager->RemoveUIChild(*popup);
	

}
