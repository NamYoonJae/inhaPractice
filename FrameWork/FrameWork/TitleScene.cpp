#include "stdafx.h"
#include "TitleScene.h"
#include "PopUp.h"
#include "Button.h"
#include "ObjectPool.h"
#include "TitleSceneBtnEvent.h"

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

	float nRight = 0.33;
	float nBottom = 0.37;

	cPopUp *pBackgroundPopup = new cPopUp;
	pBackgroundPopup->Setup("data/UI/TitleScene", "배경 사이즈 조정.png",
		D3DXVECTOR3(0, 0, 0), 2);

	cPopUp *pBackGoundBtnPopup = new cPopUp;
	pBackGoundBtnPopup->Setup("data/UI/TitleScene", "버튼 배경 사이즈 조정.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 2);
	pBackgroundPopup->cButtonPushBack(pBackGoundBtnPopup);

	//게임시작
	cButton *pButton = new cButton;
	pButton->Setup("data/UI/TitleScene", "버튼 비활성화 사이즈 조정.png", 
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 180, 60, 0, 2);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = StartGameBtnEvent;

	//이어하기
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene", "버튼 비활성화 사이즈 조정.png", 
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 180, 160, 0, 2);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = ContinueGameBtnEvent;

	//설정
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene", "버튼 비활성화 사이즈 조정.png", 
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 180, 260, 0, 2);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = SetupGameBtnEvent;

	//게임종료
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene", "버튼 비활성화 사이즈 조정.png", 
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 180, 360, 0, 2);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = EndGameBtnEvent;

	//EventManager->Attach(pPopup);
	//ObjectManager->AddUIChild(pPopup);

	EventManager->Attach(pBackgroundPopup);
	ObjectManager->AddUIChild(pBackgroundPopup);
}

