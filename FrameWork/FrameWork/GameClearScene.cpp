#include "stdafx.h"
#include "GameClearScene.h"
#include "ObjectPool.h"
#include "GameClearSceneUIEvent.h"

cGameClearScene::cGameClearScene(SceneType T)
	:cScene(T)
{
}

cGameClearScene::~cGameClearScene()
{
}

void cGameClearScene::Setup()
{

	cPopup* pGmaeClearBackgound = new cPopup;
	pGmaeClearBackgound->Setup("data/UI/GameClear","NW_BackGround.png",
		D3DXVECTOR3(0, -50, 0), 1, true, true, TAG_UI::TagUI_GameClear);

	//RETRY
	cButton* pButton = new cButton;
	pButton->Setup("data/UI/GameClear/NW_Retry", "NW_Retry_Idle.png",
		D3DXVECTOR3(590, 540, 0), 0, 0, 0, 1, true, true);
	pGmaeClearBackgound->cButtonPushBack(pButton);
	pButton->EventProcess = GameClearSceneRetryBtnEvent;
	
	//MainMenu
	pButton = new cButton;
	pButton->Setup("data/UI/GameClear/NW_MainMenu", "NW_MainMenu_Idle.png",
		D3DXVECTOR3(575, 620, 0), 0, 0, 0, 1, true, true);
	pGmaeClearBackgound->cButtonPushBack(pButton);
	pButton->EventProcess = GameClearSceneMainMenuBtnEvent;

	//Exit
	pButton = new cButton;
	pButton->Setup("data/UI/GameClear/NW_Exit","NW_Exit_Idle.png",
		D3DXVECTOR3(595, 700, 0), 0, 0, 0, 1, true, true);
	pGmaeClearBackgound->cButtonPushBack(pButton);
	pButton->EventProcess = GameClearSceneExitBtnEvent;

	EventManager->Attach(pGmaeClearBackgound);
	ObjectManager->AddUIChild(pGmaeClearBackgound);

}

void cGameClearScene::Reset(int sceneType)
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

	popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_GameClear);
	EventManager->Detach(*popup);
	ObjectManager->RemoveUIChild(*popup);
}
