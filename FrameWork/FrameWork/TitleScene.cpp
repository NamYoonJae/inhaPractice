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

	cPopUp *pBackgroundPopup = new cPopUp;
	pBackgroundPopup->Setup("data/UI/TitleScene", "NW_Background.png",
		D3DXVECTOR3(0, 0, 0), 1, true, true);

	cPopUp *pTitleImagePopup = new cPopUp;
	pTitleImagePopup->Setup("data/UI/TitleScene", "NW_Titleletter.png",
		D3DXVECTOR3(370, 140, 0), 1, true, true);
	pBackgroundPopup->cButtonPushBack(pTitleImagePopup);

	cPopUp *pBackGoundBtnPopup = new cPopUp;
	pBackGoundBtnPopup->Setup("data/UI/TitleScene", "NW_Start_UI_Back.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1, true, true);
	pTitleImagePopup->cButtonPushBack(pBackGoundBtnPopup);

	//게임시작
	cButton *pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/START", "NW_StartButton_Idle.png", 
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 105, 30, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = StartGameBtnEvent;

	//이어하기
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/CONTINUE", "NW_ContinueButton_Idle.png", 
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 105, 110, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = ContinueGameBtnEvent;

	//설정
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/SETTING", "NW_SettingButton_Idle.png", 
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 105, 190, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = SetupGameBtnEvent;

	//게임종료
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/END", "NW_EndButton_Idle.png", 
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 105, 270, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = ExitGameBtnEvent;

	Setup_OptionWindow(pBackgroundPopup);
	
	EventManager->Attach(pBackgroundPopup);
	ObjectManager->AddUIChild(pBackgroundPopup);



	//InGameUI

	nRight = 0.01;
	nBottom = 0.01;


	cPopUp* inGmaePopup = new cPopUp;
	inGmaePopup->Setup("","",
		D3DXVECTOR3(0, 0, 0), 1, true, true);


	//Hp
	cButton* hpBarBackground = new cButton;
	hpBarBackground->Setup("data/UI/InGame", "NW_HP_Bar_Background.png",
		D3DXVECTOR3(rc.right* nRight, rc.bottom * nBottom, 0), 20, 670, 0, 1, false, true);
	inGmaePopup->cButtonPushBack(hpBarBackground);

	cButton* hpBar = new cButton;
	hpBar->Setup("data/UI/InGame", "NW_HP_Bar_Sword.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 50, 676, 0, 1, false, true);
	hpBarBackground->cButtonPushBack(hpBar);

	cButton* hpBarMark = new cButton;
	hpBarMark->Setup("data/UI/InGame", "NW_HP_Bar_Mark.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 50, 676, 0, 1, false, true);
	hpBarBackground->cButtonPushBack(hpBarMark);

	//Staminer
	cButton* staminerBarBackgound = new cButton;
	staminerBarBackgound->Setup("data/UI/InGame", "NW_ST_Bar_Background.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 20, 715, 0, 1, false, true);
	inGmaePopup->cButtonPushBack(staminerBarBackgound);

	cButton* staminerBar = new cButton;
	staminerBar->Setup("data/UI/InGame", "NW_ST_Sword.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 50, 721, 0, 1, false, true);
	staminerBarBackgound->cButtonPushBack(staminerBar);

	cButton* staminerBarMark = new cButton;
	staminerBarMark->Setup("data/UI/InGame", "NW_ST_Bar_Mark.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 50, 721, 0, 1, false, true);
	staminerBarBackgound->cButtonPushBack(staminerBarMark);


	//MiniMap
	cPopUp* miniMap = new cPopUp;
	miniMap->Setup("data/UI/InGame", "NW_Minimap_Background.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1230, 0, 0, 1, false, true);
	inGmaePopup->cButtonPushBack(miniMap);


	//보스 분노
	
	//보스 상태이상 이미지

	//전리품
	



	EventManager->Attach(inGmaePopup);
	ObjectManager->AddUIChild(inGmaePopup);
}

//
void cTitleScene::Reset()
{
	
}

