#include "stdafx.h"
#include "GameOverScene.h"
#include "ObjectPool.h"
#include "GameOverSceneBtnEvent.h"

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
#pragma region UI TAG::GameOver

	//GameOver UI
	cPopup* pGameOverBackgroundPopup = new cPopup;
	pGameOverBackgroundPopup->Setup("data/UI/GameOver", "NW_GameOver_BackGround.png",
		D3DXVECTOR3(0, -50, 0), 1, true, true, TAG_UI::TagUI_GameOver);

	/*
	pGameOverBackgroundPopup->Setup("data/UI/TitleScene", "NW_Background.png",
		D3DXVECTOR3(0, 0, 0), 1, false, true, TAG_UI::TagUI_GameOver);

	cPopup* pGameOverTitleImagePopup = new cPopup;
	pGameOverTitleImagePopup->Setup("data/UI/TitleScene", "NW_Titleletter.png",
		D3DXVECTOR3(370, 140, 0), 1, false, true);
	pGameOverBackgroundPopup->cButtonPushBack(pGameOverTitleImagePopup);
	*/

	//RETRY
	cButton* pButton = new cButton;
	pButton->Setup("data/UI/GameOver/NW_Retry", "NW_GameOver_Retry_Idle.png",
		D3DXVECTOR3(590, 540, 0), 0, 0, 0, 1, true, true);
	pGameOverBackgroundPopup->cButtonPushBack(pButton);
	pButton->EventProcess = RetryGameBtnEvent;


	//메인메뉴
	pButton = new cButton;
	pButton->Setup("data/UI/GameOver/NW_MainMenu", "NW_GameOver_MainMenu_Idle.png",
		D3DXVECTOR3(575, 620, 0), 0, 0, 0, 1, true, true);
	pGameOverBackgroundPopup->cButtonPushBack(pButton);
	pButton->EventProcess = MainMenuBtnEvent;


	//종료
	pButton = new cButton;
	pButton->Setup("data/UI/GameOver/NW_Exit", "NW_GameOver_Exit_Idle.png",
		D3DXVECTOR3(595, 700, 0), 0, 0, 0, 1, true, true);
	pGameOverBackgroundPopup->cButtonPushBack(pButton);
	pButton->EventProcess = ExitGameOverBtnEvent;

	EventManager->Attach(pGameOverBackgroundPopup);
	ObjectManager->AddUIChild(pGameOverBackgroundPopup);
#pragma endregion << UI TAG::GameOver

}

// 
void cGameOverScene::Reset(int sceneType)
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

	case SceneType::SCENE_BOSS_1:
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
	EventManager->Detach(*popup);
	ObjectManager->RemoveUIChild(*popup);
}
