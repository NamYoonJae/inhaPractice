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


//�̸� ������ ��
void Opton_ESC_Event(EventType message, cPopup* btn)
{
	bool child_power = 0;
	int currentSceneType = g_pSceneManager->GetCurrentSceneType();

	// TODO ������ �ڵ�
	
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
				cout << "�ȶ�� Hp: " << btn->GetPaladinReference()->GetHp() << endl;
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
		//�ȶ���� HP�� ��������
		//���� HP �� 0���� ������ ���� ����
		
		//���� HP / �ִ� HP * 100
		//ImageInfoWidth �� ���� �־ ���� ����
		

		
	}

	/*
	if (btn->GetPaladinReference() != NULL) 
	{
		//HP�� Staminer �� �̾Ƽ� �ۼ�Ʈȭ ��Ű�� �̹����� ����

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
			cout << "�ȶ�� Staminer: " << btn->GetPaladinReference()->GetStaminer() << endl;
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



