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
#include "Trophies.h"


//이름 수정할 것
void InGamePause_Event(EventType message, cPopup* btn)
{
	bool child_power = 0;
	int currentSceneType = g_pSceneManager->GetCurrentSceneType();

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

			/*
			int hp = btn->GetPaladinReference()->GetHp();
			int maxHp = btn->GetPaladinReference()->GetMaxHp();
			float result = ((float)hp / (float)maxHp) * 100;
			btn->SetImageInfoWidth(result);
			*/
		}
		break;

	case EventType::EVENT_PLUS_HP:
		break;

	case EventType::EVENT_MINUS_HP:
		break;

	default:
		break;
	}
			
	}//switchEnd

	//실시간으로 변동 가능하게 해둠 / 만약 호출 렉이 발생할 경우 switch문 안에서 hp가 변동이 있을 때만 부르도록 수정할 것
	if (btn->GetPaladinReference() != NULL) 
	{
		int hp = btn->GetPaladinReference()->GetHp();
		int maxHp = btn->GetPaladinReference()->GetMaxHp();
		float result = ((float)hp / (float)maxHp) * 100;
		btn->SetImageInfoWidth(result);
	}


}

void StaminaGaugeEvent(EventType message, cPopup * btn)
{
	switch (message)
	{
	case EventType::EVENT_CREATE_PALADIN:
	{
		if (btn->GetPaladinReference() == NULL)
		{
			cPaladin *paladin = (cPaladin*)ObjectManager->SearchChild(Tag::Tag_Player);
			btn->SetPaladinReference(paladin);
			cout << "팔라딘 Stamina: " << btn->GetPaladinReference()->GetStamina() << endl;
		}
	}
	break;

	case EventType::EVENT_PLUS_STAMINA:
		break;

	case EventType::EVENT_MINUS_STAMINA:
		break;

	default:
		break;
	}

	if (btn->GetPaladinReference() != NULL)
	{
		int stamina = btn->GetPaladinReference()->GetStamina();
		int maxStamina = btn->GetPaladinReference()->GetMaxStamina();
		float result = ((float)stamina / (float)maxStamina) * 100;
		btn->SetImageInfoWidth(result);
	}
}

void TrophiseGaugeEvent(EventType message, cPopup* btn)
{
	switch (message)
	{
	case EventType::EVENT_SKYBEEZ:
		{
		cPaladin* pal = (cPaladin*)ObjectManager->SearchChild(Tag::Tag_Player);
		pal->CreateTrophies(EventType::EVENT_SKYBEEZ);

		cTrophies* trophies = 
			(cTrophies*)ObjectManager->SearchChildUI(TAG_UI::TagUI_Trophies_SkyBeez);

		btn->SetTrophiesReference(trophies);

		break;
		}
	case EventType::EVENT_DRAGONFOOT:
		{
		cPaladin* pal = (cPaladin*)ObjectManager->SearchChild(Tag::Tag_Player);
		pal->CreateTrophies(EventType::EVENT_DRAGONFOOT);

		cTrophies* trophies = 
			(cTrophies*)ObjectManager->SearchChildUI(TAG_UI::TagUI_Trophies_DragonFoot);

		btn->SetTrophiesReference(trophies);
		}
		break;


	default:
		break;
	}

	if (btn->GetTrophiesReference() != NULL) 
	{
		int trophiesGauge = btn->GetTrophiesReference()->GetGauge();
		int trophiesMaxGauge = btn->GetTrophiesReference()->GetMaxGauge();
		float result = ((float)trophiesGauge / (float)trophiesMaxGauge) * 100;
		btn->SetImageInfoWidth(result);
	}
}


