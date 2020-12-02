#include "stdafx.h"
#include "TitleScene.h"
#include "PopUp.h"
#include "Button.h"
#include "ObjectPool.h"
#include "OptionUIEvent.h"
#include "TitleSceneUIEvent.h"

cTitleScene::cTitleScene(SceneType T)
	:cScene(T)
{
}


cTitleScene::~cTitleScene()
{
	
}

void cTitleScene::Setup()
{

	//클라이언트 값을 받아와서
	//비율화

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cout << "Left : " << rc.left << endl; // 0
	cout << "Right : " << rc.right << endl; // 1584
	cout << "Bottom : " << rc.bottom << endl; //860
	cout << "Top : " << rc.top << endl; // 0

	float nRight = 0.34;
	float nBottom = 0.45;

	//TitleUI
	cPopup *pBackgroundPopup = new cPopup;
	pBackgroundPopup->Setup("data/UI/TitleScene", "NW_Background.png",
		D3DXVECTOR3(0, -20, 0), 1, true, true, TagUI_Title);

	Setup_OptionWindow(pBackgroundPopup);
	
	cPopup *pTitleImagePopup = new cPopup;
	pTitleImagePopup->Setup("data/UI/TitleScene", "NW_Titleletter.png",
		D3DXVECTOR3(370, 140, 0), 1, true, true);
	pBackgroundPopup->cButtonPushBack(pTitleImagePopup);

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
	
	EventManager->Attach(pBackgroundPopup);
	ObjectManager->AddUIChild(pBackgroundPopup);



	//InGame UI
	cPopup* inGamePopup = new cPopup;
	inGamePopup->Setup("","",
		D3DXVECTOR3(0, 0, 0), 1, true, true, TagUI_InGame);

	//Hp
	cButton* hpBarBackground = new cButton;
	hpBarBackground->Setup("data/UI/InGame", "NW_HP_Bar_Background.png",
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

	//Staminer
	cButton* staminerBarBackgound = new cButton;
	staminerBarBackgound->Setup("data/UI/InGame", "NW_ST_Bar_Background.png",
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
	cPopup* spoilsBackgound = new cPopup;
	spoilsBackgound->Setup("data/UI/InGame", "NW_Spoils_Back.png",
		D3DXVECTOR3(1270, 650, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(spoilsBackgound);

	//전리품 게이지
	cButton* attriBarBackground = new cButton;
	attriBarBackground->Setup("data/UI/InGame","NW_AttriGauge_Background.png",
		D3DXVECTOR3(1130, 760, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(attriBarBackground);

	cButton* attriBar = new cButton;
	attriBar->Setup("data/UI/InGame", "NW_Attri_Gauge.png",
		D3DXVECTOR3(1162, 765, 0), 0, 0, 0, 1, false, true);
	attriBarBackground->cButtonPushBack(attriBar);
	
	cButton* attriMark = new cButton;
	attriMark->Setup("data/UI/InGame", "NW_AttriGauge_Mark.png",
		D3DXVECTOR3(1162, 768, 0), 0, 0, 0, 1, false, true);
	attriBarBackground->cButtonPushBack(attriMark);


	//오브젝트 게이지
	cButton* interactionBarBackground = new cButton;
	interactionBarBackground->Setup("data/UI/InGame", "NW_InteractionGauge_Background.png",
		D3DXVECTOR3(970, 420, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(interactionBarBackground);

	cButton* interactionBarGauge = new cButton;
	interactionBarGauge->Setup("data/UI/InGame", "NW_Interaction_Gauge.png",
		D3DXVECTOR3(972.5, 445, 0), 0, 0, 0, 1, false, true);
	interactionBarBackground->cButtonPushBack(interactionBarGauge);


	EventManager->Attach(inGamePopup);
	ObjectManager->AddUIChild(inGamePopup);
}

//
void cTitleScene::Reset()
{
	//Off 하거나 On 하거나 삭제하거나

}

