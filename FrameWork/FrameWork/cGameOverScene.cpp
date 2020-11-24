#include "stdafx.h"
#include "cGameOverScene.h"
#include "ObjectPool.h"
#include "GameOverSceneBtnEvent.h"


cGameOverScene::cGameOverScene(SceneType T)
	:cScene(T)
{
}

cGameOverScene::~cGameOverScene()
{
}

void cGameOverScene::Setup()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	float nRight = 0.34;
	float nBottom = 0.45;

	cPopUp *pBackgroundPopup = new cPopUp;
	pBackgroundPopup->Setup("data/UI/TitleScene", "NW_Background.png",
		D3DXVECTOR3(0, 0, 0), 1, true, true);

	
	cPopUp * pTitleImagePopup = new cPopUp;
	pTitleImagePopup->Setup("data/UI/TitleScene", "NW_Titleletter.png",
		D3DXVECTOR3(370, 140, 0), 1, true, true);
	pBackgroundPopup->cButtonPushBack(pTitleImagePopup);

	//RETRY
	cButton *pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/START", "NW_StartButton_Idle.png",
		D3DXVECTOR3(rc.right *nRight, rc.bottom * nBottom, 0), 105, 30, 0, 1, true, true);
	pBackgroundPopup->cButtonPushBack(pButton);
	pButton->EventProcess = RetryGameBtnEvent;

	//처음으로
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/CONTINUE", "NW_ContinueButton_Idle.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 105, 150, 0, 1, true, true);
	pBackgroundPopup->cButtonPushBack(pButton);
	pButton->EventProcess = MainMenuBtnEvent;

	//게임종료
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/END", "NW_EndButton_Idle.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 105, 270, 0, 1, true, true);
	pBackgroundPopup->cButtonPushBack(pButton);
	pButton->EventProcess = ExitGameBtnEvent;

	EventManager->Attach(pBackgroundPopup);
	ObjectManager->AddUIChild(pBackgroundPopup);

}
