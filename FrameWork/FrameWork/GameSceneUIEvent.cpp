#include "stdafx.h"
#include "GameSceneUIEvent.h"
#include "EventManager.h"
#include "PopUp.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PopUp.h"
#include "Button.h"
#include "ObjectPool.h"
#include "Paladin.h"


//이름 수정할 것
void Opton_ESC_Event(EventType message, cPopup* btn)
{
	bool child_power = 0;
	int currentSceneType = g_pSceneManager->GetCurrentSceneType();

	// TODO 디버깅용 코드
	
	switch (message)
	{
	case EventType::EVENT_ESC:
	{
		if (currentSceneType == SceneType::SCENE_BOSS_1 || currentSceneType == SceneType::SCENE_BOSS_2)
		{
			for (size_t i = 0; i < btn->GetPopUpListSize(); i++)
			{
				cPopup * pchild = btn->GetPopupBtn(i);
				if (pchild)
				{
					child_power = pchild->GetPowerState();

					if (child_power == true)
						break; // << for
				}
			}

			if (child_power)
			{
				btn->PowerOnOff_List_OnlySelf(false);
			}
			else
			{
				btn->PowerOnOff_List_OnlySelf(false);
				btn->GetPopupBtn(0)->PowerOnOff_OnlySelf(true);
			}
			cout << "ESC_Event call & active" << endl;
		}
	}
	break;
		
	default:
		break;
	}
}

void HpGaugeEvent(EventType message, cPopup * btn)
{
	switch (message)
	{
	case EventType::EVENT_CREATE_PALADIN:
		{
			if (btn->GetPaladinReference() == NULL)
			{
				cPaladin *paladin = (cPaladin*)ObjectManager->SearchChild(Tag::Tag_Player);
				btn->SetPaladinReference(paladin);
				cout << "팔라딘 Hp: " << btn->GetPaladinReference()->GetHp() << endl;
			}
		}
		break;

	case EventType::EVENT_PLUS_HP:
		break;

	case EventType::EVENT_MINUS_HP:
		break;

	default:
		break;
	}

	if (btn->GetPaladinReference() != NULL)
	{
		btn->GetPaladinReference()->GetHp();
		//팔라딘의 HP를 가져오기
		//만약 HP 가 0보다 작으면 게임 오버
		
		//현재 HP / 최대 HP * 100
		//ImageInfoWidth 에 비율 넣어서 새로 셋팅
		

		
	}

	/*
	if (btn->GetPaladinReference() != NULL) 
	{
		//HP와 Staminer 값 뽑아서 퍼센트화 시키고 이미지에 적용

	}
	*/
}

void StaminerGaugeEvent(EventType message, cPopup * btn)
{
	switch (message)
	{
	case EventType::EVENT_CREATE_PALADIN:
	{
		if (btn->GetPaladinReference() == NULL)
		{
			cPaladin *paladin = (cPaladin*)ObjectManager->SearchChild(Tag::Tag_Player);
			btn->SetPaladinReference(paladin);
			cout << "팔라딘 Staminer: " << btn->GetPaladinReference()->GetStaminer() << endl;
		}
	}
	break;

	case EventType::EVENT_PLUS_STAMINER:
		break;

	case EventType::EVENT_MINUS_STAMINER:
		break;

	default:
		break;
	}

}



