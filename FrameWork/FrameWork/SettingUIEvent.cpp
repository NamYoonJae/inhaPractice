#include "stdafx.h"
#include "EventManager.h"
#include "PopUp.h"
#include "ObjectPool.h"
#include "SettingUIEvent.h"

#include "BtnUIEvent.h"
#include "jsonManager.h"

//#include "SceneManager.h"
//#include "TextureManager.h"

// 반환되는 포인터는 최상단 팝업의 포인터 좌표
cPopup* Setup_Setting_popup(cPopup* btn)
{
	JSON_Object * p_json_object_UI = g_p_jsonManager->get_json_object_UI();
	JSON_Object * p_json_object_setting = g_p_jsonManager->get_json_object_Setting();

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	//cout << "Left : " << rc.left << endl; // 0
	//cout << "Right : " << rc.right << endl; // 1584
	//cout << "Bottom : " << rc.bottom << endl; //860
	//cout << "Top : " << rc.top << endl; // 0

	float nRight = 0.33;
	float nBottom = 0.37;

	cPopup *pBack = new cPopup;
	pBack->Setup(
		json_Function::object_get_pChar(p_json_object_UI, "UI/InGamePauseMenu/directory"),
		json_Function::object_get_pChar(p_json_object_UI, "UI/InGamePauseMenu/InGameSetting_Back/filename"),
		D3DXVECTOR3(0, 0, 0),
		json_Function::object_get_double(p_json_object_UI, "UI/InGamePauseMenu/InGameSetting_Back/scale"),
		true, true);
	
	cPopup *pOption = new cPopup;
	pBack->cButtonPushBack(pOption);
	pOption->Setup(
		json_Function::object_get_pChar(p_json_object_UI, "UI/Settings/directory"),
		json_Function::object_get_pChar(p_json_object_UI, "UI/Settings/Option/filename"),
		D3DXVECTOR3(
			json_Function::object_get_double(p_json_object_UI, "UI/Settings/Option/position_x"),
			json_Function::object_get_double(p_json_object_UI, "UI/Settings/Option/position_y"),
			0),
		json_Function::object_get_double(p_json_object_UI, "UI/Settings/Option/scale"),
		true, true);
	// 이벤트에서 상수 인덱스로 pControl를 참조하니까 수정시 유의
	pOption->EventProcess = Setting_popup_ReturnEvent_whitespace;

	cPopup* pControl = new cPopup;
	pBack->cButtonPushBack(pControl);
	pControl->Setup(
		json_Function::object_get_pChar(p_json_object_UI, "UI/Settings/directory"),
		json_Function::object_get_pChar(p_json_object_UI, "UI/Settings/Control/filename"),
		D3DXVECTOR3(
			json_Function::object_get_double(p_json_object_UI, "UI/Settings/Control/position_x"),
			json_Function::object_get_double(p_json_object_UI, "UI/Settings/Control/position_y"),
			0),
		json_Function::object_get_double(p_json_object_UI, "UI/Settings/Control/scale"),
		true, true);

	cPopup* pText = new cPopup;
	pBack->cButtonPushBack(pText);
	pText->Setup(
		json_Function::object_get_pChar(p_json_object_UI, "UI/Settings/directory"),
		json_Function::object_get_pChar(p_json_object_UI, "UI/Settings/Text/filename"),
		D3DXVECTOR3(
			json_Function::object_get_double(p_json_object_UI, "UI/Settings/Text/position_x"),
			json_Function::object_get_double(p_json_object_UI, "UI/Settings/Text/position_y"),
			0),
		json_Function::object_get_double(p_json_object_UI, "UI/Settings/Text/scale"),
		true, true);

#pragma region barSilder
	// TODO json Test
	// TODO 이벤트 세분화

	// 테스트용 객체 생성 코드
	//Setup_BarSliderPopupBtn(pOption, D3DXVECTOR3(132, 123, 0), BarSliderMoveEvent);
	//->MovePosition(D3DXVECTOR2(
	//		(float)(json_Function::object_get_double(p_json_object_setting, "Sound/BGM")
	//			* json_object_get_number(p_json_object_setting, "tick")),
	//		0));

	Setup_BarSliderPopupBtn(pOption, D3DXVECTOR3(132, 123, 0), BGM_Setting_Event)
		->MovePosition(D3DXVECTOR2((float)(json_Function::object_get_double(p_json_object_setting, "Sound/BGM") * json_object_get_number(p_json_object_setting, "tick")), 0));
	Setup_BarSliderPopupBtn(pOption, D3DXVECTOR3(132, 192, 0), SFX_Setting_Event)
		->MovePosition(D3DXVECTOR2((float)(json_Function::object_get_double(p_json_object_setting, "Sound/SFX") * json_object_get_number(p_json_object_setting, "tick")), 0));

	Setup_BarSliderPopupBtn(pOption, D3DXVECTOR3(132, 325, 0), MouseSensitivity_Total_Event)
		->MovePosition(D3DXVECTOR2((float)(json_Function::object_get_double(p_json_object_setting, "Mouse sensitivity/total") * json_object_get_number(p_json_object_setting, "tick")), 0));
	Setup_BarSliderPopupBtn(pOption, D3DXVECTOR3(132, 389, 0), MouseSensitivity_Normal_Event)
		->MovePosition(D3DXVECTOR2((float)(json_Function::object_get_double(p_json_object_setting, "Mouse sensitivity/normal") * json_object_get_number(p_json_object_setting, "tick")), 0));
	Setup_BarSliderPopupBtn(pOption, D3DXVECTOR3(132, 455, 0), MouseSensitivity_Special_Event)
		->MovePosition(D3DXVECTOR2((float)(json_Function::object_get_double(p_json_object_setting, "Mouse sensitivity/special") * json_object_get_number(p_json_object_setting, "tick")), 0));
#pragma endregion barSilder

#pragma region chk_Button
	//Setup_CheckBtn(pOption, D3DXVECTOR3(190, 175, 0), CheckBtnEvent);
	//Setup_CheckBtn(pOption, D3DXVECTOR3(190, 215, 0), CheckBtnEvent);
	//Setup_CheckBtn(pOption, D3DXVECTOR3(190, 255, 0), CheckBtnEvent);
#pragma endregion chk_Button

	if (!btn)
	{
		EventManager->Attach(pBack);
		ObjectManager->AddUIChild(pBack);
	}
	else if (btn)
	{
		pBack->PowerOnOff_OnlySelf();
		btn->cButtonPushBack(pBack);
	}

	return pBack;
}

// TODO 함수명 좀 더 간략하게 다음 풀 받을때 바로 수정하기
void Setting_popup_ReturnEvent_whitespace(EventType message, cPopup* popup)
{
	D3DXVECTOR2 cur = EventManager->GetMouseCurrent();
	D3DXVECTOR3 btnPosition = popup->GetPosition();
	float width = popup->GetImageInfoWidth() * popup->GetPercent();
	float height = popup->GetImageInfoHeight() *  popup->GetPercent();

	cPopup* pControl = popup->GetUpPopUp()->GetPopupBtn(1);
	D3DXVECTOR3 control_position = pControl->GetPosition();
	float control_width = pControl->GetImageInfoWidth() * pControl->GetPercent();
	float control_height = pControl->GetImageInfoHeight() * pControl->GetPercent();

	switch (message)
	{
	case EventType::EVENT_LBUTTONDOWN:
	{
		if ((btnPosition.x > cur.x || cur.x > btnPosition.x + width ||
				btnPosition.y > cur.y || cur.y > btnPosition.y + height) 
			&&
			(control_position.x > cur.x || cur.x > control_position.x + control_width ||
				control_position.y > cur.y || cur.y > control_position.y + control_height))
		{
			{
				popup->SetStateChange(enum_On);
			}
		}
	}

	break;
	case EventType::EVENT_LBUTTONUP:
	{
		if (popup->GetState() == enum_On)
		{
			if ((btnPosition.x > cur.x || cur.x > btnPosition.x + width ||
				btnPosition.y > cur.y || cur.y > btnPosition.y + height)
				&&
				(control_position.x > cur.x || cur.x > control_position.x + control_width ||
					control_position.y > cur.y || cur.y > control_position.y + control_height))
			{
				popup->SetStateChange(enum_Off);

				cPopup * pPopup0 = popup->GetTopPopUp();
				for (size_t i = 0; i < pPopup0->GetPopUpListSize(); i++)
				{
					pPopup0->GetPopupBtn(i)->PowerOnOff_OnlySelf();
				}
			}
		}
	}
	break;
	};//switch End
}

void Setting_popup_ReturnEvent(EventType message, cPopup* popup)
{
	D3DXVECTOR2 cur = EventManager->GetMouseCurrent();
	D3DXVECTOR3 btnPosition = popup->GetPosition();
	float width = popup->GetImageInfoWidth() * popup->GetPercent();
	float height = popup->GetImageInfoHeight() *  popup->GetPercent();

	switch (message)
	{
	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width &&
			btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
		{
			{
				popup->SetStateChange(enum_On);
			}
		}
	}

	break;
	case EventType::EVENT_LBUTTONUP:
	{
		if (popup->GetState() == enum_On)
		{
			if (btnPosition.x <= cur.x && cur.x <= btnPosition.x + width &&
				btnPosition.y <= cur.y && cur.y <= btnPosition.y + height)
			{
				popup->SetStateChange(enum_Off);

				cPopup * pPopup0 = popup->GetTopPopUp();
				for (size_t i = 0; i < pPopup0->GetPopUpListSize(); i++)
				{
					pPopup0->GetPopupBtn(i)->PowerOnOff_OnlySelf();
				}
			}
		}
	}
	break;
	};//switch End
}