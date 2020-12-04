#include "stdafx.h"
#include "TitleScene.h"
#include "PopUp.h"
#include "Button.h"
#include "ObjectPool.h"
#include "SettingUIEvent.h"
#include "TitleSceneUIEvent.h"
#include "GameOverSceneBtnEvent.h"
#include "GameSceneUIEvent.h"
#include "InGamePauseMenuUIEvent.h"

cTitleScene::cTitleScene(SceneType T)
	:cScene(T)
{
}


cTitleScene::~cTitleScene()
{
	
}

void cTitleScene::Setup()
{
	//예외 추가
	if(ObjectManager->GetUISize() > 0)
	{
		return;
	}
	//

	//클라이언트 값을 받아와서
	//비율화

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cout << "Left : " << rc.left << endl; // 0
	cout << "Right : " << rc.right << endl; // 1584
	cout << "Bottom : " << rc.bottom << endl; //860
	cout << "Top : " << rc.top << endl; // 0

#pragma region UI TAG::Title
	//TitleUI
	cPopup *pTitleBackgroundPopup = new cPopup;
	pTitleBackgroundPopup->Setup("data/UI/TitleScene", "NW_Background.png",
		D3DXVECTOR3(0, -20, 0), 1, true, true, TAG_UI::TagUI_Title);

	Setup_Setting_popup(pTitleBackgroundPopup);
	
	cPopup *pTitleImagePopup = new cPopup;
	pTitleImagePopup->Setup("data/UI/TitleScene", "NW_Titleletter.png",
		D3DXVECTOR3(370, 140, 0), 1, true, true);
	pTitleBackgroundPopup->cButtonPushBack(pTitleImagePopup);

	cPopup *pBackGoundBtnPopup = new cPopup;
	pBackGoundBtnPopup->Setup("data/UI/TitleScene", "NW_Start_UI_Back.png",
		D3DXVECTOR3(550, 380, 0), 1, true, true);
	pTitleImagePopup->cButtonPushBack(pBackGoundBtnPopup);

	//게임시작
	cButton *pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/START", "NW_StartButton_Idle.png", 
		D3DXVECTOR3(650, 420, 0), 0, 0, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = StartGameBtnEvent;

	//이어하기
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/CONTINUE", "NW_ContinueButton_Idle.png", 
		D3DXVECTOR3(650, 495, 0), 0, 0, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = ContinueGameBtnEvent;

	//설정
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/SETTING", "NW_SettingButton_Idle.png", 
		D3DXVECTOR3(650, 570, 0), 0, 0, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = SetupGameBtnEvent;

	//게임종료
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/END", "NW_EndButton_Idle.png", 
		D3DXVECTOR3(650, 645, 0), 0, 0, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = ExitGameBtnEvent;
	
	EventManager->Attach(pTitleBackgroundPopup);
	ObjectManager->AddUIChild(pTitleBackgroundPopup);
#pragma endregion << UI TAG::Title


#pragma region UI TAG::InGame
	//InGame UI
	cPopup* inGamePopup = new cPopup;
	inGamePopup->Setup("","",
		D3DXVECTOR3(0, 0, 0), 1, false, true, TAG_UI::TagUI_InGame);

	//Hp
	cButton* hpBar = new cButton;
	hpBar->Setup("data/UI/InGame", "NW_HP_Gauge.png",
		D3DXVECTOR3(61, 736, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(hpBar);

	cButton* hpBarBackground = new cButton;
	hpBarBackground->Setup("data/UI/InGame", "NW_HPST_BarBackground.png",
		D3DXVECTOR3(30, 730, 0), 0, 0, 0, 1, false, true);
	hpBar->cButtonPushBack(hpBarBackground);

	/* 이전버전소스 keep
	cButton* hpBarBackground = new cButton;
	hpBarBackground->Setup("data/UI/InGame", "NW_HP_BarBackground.png",
		D3DXVECTOR3(30, 730, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(hpBarBackground);

	
	cButton* hpBar = new cButton;
	hpBar->Setup("data/UI/InGame", "NW_HP_Bar_Sword.png",
		D3DXVECTOR3(60, 736, 0), 0, 0, 0, 1, false, true);
	hpBarBackground->cButtonPushBack(hpBar);

	cButton* hpBarMark = new cButton;
	hpBarMark->Setup("data/UI/InGame", "NW_HP_Bar_Mark.png",
		D3DXVECTOR3(60, 736, 0), 0, 0, 0, 1, false, true);
	hpBarBackground->cButtonPushBack(hpBarMark);
	*/

	//Staminer

	cButton* staminerBar = new cButton;
	staminerBar->Setup("data/UI/InGame", "NW_ST_Gauge.png",
		D3DXVECTOR3(61, 786, 0), 0, 0, 0, 1, false, true); // 
	inGamePopup->cButtonPushBack(staminerBar);

	cButton* staminerBarBackgound = new cButton;
	staminerBarBackgound->Setup("data/UI/InGame", "NW_HPST_BarBackground.png",
		D3DXVECTOR3(30, 780, 0), 0, 0, 0, 1, false, true);
	staminerBar->cButtonPushBack(staminerBarBackgound);

	/* 이전버전 소스 keep
	cButton* staminerBarBackgound = new cButton;
	staminerBarBackgound->Setup("data/UI/InGame", "NW_ST_BarBackground.png",
		D3DXVECTOR3(30, 780, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(staminerBarBackgound);

	
	cButton* staminerBar = new cButton;
	staminerBar->Setup("data/UI/InGame", "NW_ST_Sword.png",
		D3DXVECTOR3(60, 786, 0), 0, 0, 0, 1, false, true);
	staminerBarBackgound->cButtonPushBack(staminerBar);

	cButton* staminerBarMark = new cButton;
	staminerBarMark->Setup("data/UI/InGame", "NW_ST_Bar_Mark.png",
		D3DXVECTOR3(60, 786, 0), 0, 0, 0, 1, false, true);
	staminerBarBackgound->cButtonPushBack(staminerBarMark);
	*/


	//캐릭터 상태이상 이미지 좌표 따기위해 적어둠
	cPopup* playerDiverf = new cPopup;
	playerDiverf->Setup("data/UI/InGame", "NW_Condition_Paralyz.png",
		D3DXVECTOR3(60, 680, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(playerDiverf);

	playerDiverf = new cPopup;
	playerDiverf->Setup("data/UI/InGame", "NW_Condition_Paralyz.png",
		D3DXVECTOR3(110, 680, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(playerDiverf);

	playerDiverf = new cPopup;
	playerDiverf->Setup("data/UI/InGame", "NW_Condition_Paralyz.png",
		D3DXVECTOR3(160, 680, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(playerDiverf);

	playerDiverf = new cPopup;
	playerDiverf->Setup("data/UI/InGame", "NW_Condition_Paralyz.png",
		D3DXVECTOR3(210, 680, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(playerDiverf);

	playerDiverf = new cPopup;
	playerDiverf->Setup("data/UI/InGame", "NW_Condition_Paralyz.png",
		D3DXVECTOR3(260, 680, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(playerDiverf);

	playerDiverf = new cPopup;
	playerDiverf->Setup("data/UI/InGame", "NW_Condition_Paralyz.png",
		D3DXVECTOR3(310, 680, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(playerDiverf);



	//MiniMap
	cPopup* miniMap = new cPopup;
	miniMap->Setup("data/UI/InGame", "NW_Minimap_Background.png",
		D3DXVECTOR3(1305, 0, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(miniMap);

	//보스 분노
	cPopup* bossAnger = new cPopup;
	bossAnger->Setup("data/UI/InGame", "NW_MonAnger_0.png",
		D3DXVECTOR3(1270, 180, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossAnger);
	
	/*
	cButton* anger = new cButton;
	anger->Setup("data/UI/InGame", "NW_MonAnger_0.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1230, 180, 0, 1, false, true);
	bossAnger->cButtonPushBack(anger);
	*/

	/* //분노 이미지 테스트
	anger = new cButton;
	anger->Setup("data/UI/InGame", "NW_MonAnger_50.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1230, 180, 0, 1, false, true);
	bossAnger->cButtonPushBack(anger);

	anger = new cButton;
	anger->Setup("data/UI/InGame", "NW_MonAnger_100.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1230, 180, 0, 1, true, true);
	bossAnger->cButtonPushBack(anger);
	*/

	//보스 상태이상 이미지 좌표 따기위해 적어둠
	cPopup* bossDiverf = new cPopup;
	bossDiverf->Setup("data/UI/InGame", "NW_Condition_Sturn.png",
		D3DXVECTOR3(1330, 180, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossDiverf);


	bossDiverf = new cPopup;
	bossDiverf->Setup("data/UI/InGame", "NW_Condition_Sturn.png",
		D3DXVECTOR3(1380, 180, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossDiverf);

	bossDiverf = new cPopup;
	bossDiverf->Setup("data/UI/InGame", "NW_Condition_Sturn.png",
		D3DXVECTOR3(1430, 180, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossDiverf);

	bossDiverf = new cPopup;
	bossDiverf->Setup("data/UI/InGame", "NW_Condition_Sturn.png",
		D3DXVECTOR3(1480, 180, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossDiverf);

	bossDiverf = new cPopup;
	bossDiverf->Setup("data/UI/InGame", "NW_Condition_Sturn.png",
		D3DXVECTOR3(1530, 180, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossDiverf);


	//전리품
	cPopup* trophiesBackgound = new cPopup;
	trophiesBackgound->Setup("data/UI/InGame", "NW_trophies_Back.png",
		D3DXVECTOR3(1270, 650, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(trophiesBackgound);

	//전리품 게이지
	cButton* trophiesBarBackground = new cButton;
	trophiesBarBackground->Setup("data/UI/InGame","NW_Attri_BarBackground.png",
		D3DXVECTOR3(1130, 780, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(trophiesBarBackground);
	/*
	cButton* attriBar = new cButton;
	attriBar->Setup("data/UI/InGame", "NW_Attri_Gauge.png",
		D3DXVECTOR3(1162, 765, 0), 0, 0, 0, 1, false, true);
	attriBarBackground->cButtonPushBack(attriBar);
	
	cButton* attriMark = new cButton;
	attriMark->Setup("data/UI/InGame", "NW_AttriGauge_Mark.png",
		D3DXVECTOR3(1162, 768, 0), 0, 0, 0, 1, false, true);
	attriBarBackground->cButtonPushBack(attriMark);
	*/

	EventManager->Attach(inGamePopup);
	ObjectManager->AddUIChild(inGamePopup);
#pragma endregion << UI TAG::InGame


#pragma region UI TAG::GameObject
	//오브젝트 게이지
	cPopup* obectBar = new cPopup;
	obectBar->Setup("", "", D3DXVECTOR3(0, 0, 0), 0, 0, 0, 1, false, true, TagUI_InGameObject);

	cButton* interactionBarBackground = new cButton;
	interactionBarBackground->Setup("data/UI/InGame", "NW_InteractionGauge_Background.png",
		D3DXVECTOR3(970, 300, 0), 0, 0, 0, 1, false, true);
	obectBar->cButtonPushBack(interactionBarBackground);

	/*
	cButton* interactionBarGauge = new cButton;
	interactionBarGauge->Setup("data/UI/InGame", "NW_Interaction_Gauge.png",
		D3DXVECTOR3(972.5, 445, 0), 0, 0, 0, 1, false, true);
	interactionBarBackground->cButtonPushBack(interactionBarGauge);
	*/
	
	EventManager->Attach(obectBar);
	ObjectManager->AddUIChild(obectBar);
#pragma endregion << UI TAG::GameObject


#pragma region UI TAG::GameOver

	//GameOver UI
	cPopup* pGameOverBackgroundPopup = new cPopup;
	pGameOverBackgroundPopup->Setup("data/UI/GameOver", "NW_GameOver_BackGround.png",
		D3DXVECTOR3(0, -80, 0), 1, false, true, TAG_UI::TagUI_GameOver);

	/*
	pGameOverBackgroundPopup->Setup("data/UI/TitleScene", "NW_Background.png",
		D3DXVECTOR3(0, 0, 0), 1, false, true, TAG_UI::TagUI_GameOver);

	cPopup* pGameOverTitleImagePopup = new cPopup;
	pGameOverTitleImagePopup->Setup("data/UI/TitleScene", "NW_Titleletter.png",
		D3DXVECTOR3(370, 140, 0), 1, false, true);
	pGameOverBackgroundPopup->cButtonPushBack(pGameOverTitleImagePopup);
	*/

	//RETRY
	pButton = new cButton;
	pButton->Setup("data/UI/GameOver", "NW_GameOver_Re_Idle.png",
		D3DXVECTOR3(675, 540, 0), 0, 0, 0, 1, false, true);
	pGameOverBackgroundPopup->cButtonPushBack(pButton);
	pButton->EventProcess = RetryGameBtnEvent;
	
	/*
	//메인메뉴
	pButton = new cButton;
	pButton->Setup("data/UI/GameOver", "NW_GameOver_Re_Idle.png",
		D3DXVECTOR3(rc.right* nRight, rc.bottom* nBottom, 0), 155, 150, 0, 1, false, true);
	pGameOverBackgroundPopup->cButtonPushBack(pButton);
	pButton->EventProcess = MainMenuBtnEvent;
	*/

	//종료
	pButton = new cButton;
	pButton->Setup("data/UI/GameOver", "NW_GameOver_End_Idle.png",
		D3DXVECTOR3(675, 660, 0), 0, 0, 0, 1, false, true);
	pGameOverBackgroundPopup->cButtonPushBack(pButton);
	pButton->EventProcess = ExitGameOverBtnEvent;

	EventManager->Attach(pGameOverBackgroundPopup);
	ObjectManager->AddUIChild(pGameOverBackgroundPopup);
#pragma endregion << UI TAG::GameOver


#pragma region UI TAG::ESC_Menu
	// TODO json 파일 쓸 때 대비해서 주석남겨둠
	// pPopup = new cPopup;
	// pPopup->Setup(파일위치, D3DXVECTOR3(x축 중앙 - 이미지 x크기 - 위치조정, y축 중앙 - 이미지 y 크기 - 위치조정, 0), 배율);
	// pPopup->Setup("data/UI/TitleScene", "게임 타이틀 사이즈 조정.png", D3DXVECTOR3(800 - 450, 450 - 150 - 200, 0), 2, false, false);

	//EventManager->Attach(pPopup);
	//ObjectManager->AddUIChild(pPopup);

	// TODO 시스템창 불러오기
	cPopup * pMediator = new cPopup;
	pMediator->Setup(
		"",
		"",
		D3DXVECTOR3(-1, -1, 0),
		0, 0, 0,
		1,
		true, true, TAG_UI::TagUI_ESC_Menu);
	pMediator->EventProcess = Opton_ESC_Event;
	
	cPopup *pSystemPopUp = Setup_InGamePauseMenu(pMediator);
	cPopup *pOptionPopUp = Setup_Setting_popup(pMediator);

	EventManager->Attach(pMediator);
	ObjectManager->AddUIChild(pMediator);
#pragma endregion << UI TAG::ESC_Menu
}

//
void cTitleScene::Reset(int sceneType)
{
	cPopup* popup = NULL;

	switch (sceneType)
	{
	case SceneType::SCENE_BOSS_1:
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_InGame);
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


	case SceneType::SCENE_BOSS_2:
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_InGame);
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

	popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_Title);
	if (popup != NULL)
	{
		popup->PowerOnOff();
	}

}