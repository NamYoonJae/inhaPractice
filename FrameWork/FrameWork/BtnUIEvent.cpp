#include "stdafx.h"
#include "EventManager.h"
#include "PopUp.h"
#include "ObjectPool.h"
#include "BtnUIEvent.h"

#include "jsonManager.h"
//#include "SystemUIEvent.h"
//#include "OptionUIEvent.h"


cButton* Setup_CheckBtn(cPopup* popup, D3DXVECTOR3 position, function<void(EventType&, cPopup*)> EventFuction)
{
	JSON_Object* p_json_object_UI = g_p_jsonManager->get_json_object_UI();
	JSON_Object* p_json_object_setting = g_p_jsonManager->get_json_object_Setting();

	cButton* pChkButton = new cButton;
	pChkButton->Setup(
		json_Fuction::object_get_pChar(p_json_object_UI, "UI/Settings/directory"),
		json_Fuction::object_get_pChar(p_json_object_UI, "UI/Settings/ToggleButton_On/filename"),
		popup->GetPosition(),
		position.x, position.y, position.z,
		1,
		true, true);
	popup->cButtonPushBack(pChkButton);

	// TODO ������ ���� �ҷ��� �� -> �̺�Ʈ �Լ��� �ű�� �� ���
	pChkButton->SetStateChange(enum_On);

	if (EventFuction)
		pChkButton->EventProcess = EventFuction;
	else
		cout << "Setup_CheckBtn() EventFuction is NULL" << endl;

	return pChkButton;
}

void CheckBtnEvent(EventType message, cPopup* btn)
{
	// json object ������ ����
	static JSON_Object* p_json_object_UI = g_p_jsonManager->get_json_object_UI();
	static JSON_Object* p_json_object_setting = g_p_jsonManager->get_json_object_Setting();

	cButton* button = (cButton*)btn;

	D3DXVECTOR3 btnPosition = button->GetPosition();

	// ���Ұ��� �ƴϱ⿡ static ����, static ���� ����� ��
	static float btn_width = button->GetImageInfoWidth() * button->GetPercent();
	static float btn_height = button->GetImageInfoHeight() * button->GetPercent();

	// ���콺 ��ġ�� ����ؾ��ϱ⶧���� static ����
	static D3DXVECTOR2 prev_cur;
	static D3DXVECTOR2 crnt_cur;
	crnt_cur = EventManager->GetMouseCurrent();

	switch (message)
	{
	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= crnt_cur.x && crnt_cur.x <= btnPosition.x + btn_width)
		{
			if (btnPosition.y <= crnt_cur.y && crnt_cur.y <= btnPosition.y + btn_height)
			{
				prev_cur = EventManager->GetMouseCurrent();
			}
		}
	}
	break;

	case EventType::EVENT_LBUTTONUP:
	{
		if (btnPosition.x <= crnt_cur.x && crnt_cur.x <= btnPosition.x + btn_width)
		{
			if (btnPosition.y <= crnt_cur.y && crnt_cur.y <= btnPosition.y + btn_height)
			{
				if (button->GetState() == enum_On)
					button->SetStateChange(enum_Off);
				else if (button->GetState() == enum_Off)
					button->SetStateChange(enum_On);

				if (button->GetState() == enum_On)
				{
					string full_path = json_Fuction::object_get_string(p_json_object_UI, "UI/Settings/directory")
						+ '/' + json_Fuction::object_get_string(p_json_object_UI, "UI/Settings/ToggleButton_On/filename");
					char c_path[200] = { 0 };
					strcpy(c_path, full_path.c_str());

					button->ChangeSprite(c_path);
					// TODO ���� �����ϱ�
				}
				else if (button->GetState() == enum_Off) {
					string full_path = json_Fuction::object_get_string(p_json_object_UI, "UI/Settings/directory")
						+ '/' + json_Fuction::object_get_string(p_json_object_UI, "UI/Settings/ToggleButton_Off/filename");
					char c_path[200] = { 0 };
					strcpy(c_path, full_path.c_str());

					button->ChangeSprite(c_path);
					// TODO ���� �����ϱ�
				}


			}
		}
	}
	break;

	default:
		break;
	}

}


// �¾��Լ� ������ json���Ͽ��� �����͸� �ҷ��� ��ġ�̵�
cButton* Setup_BarSliderPopupBtn(cPopup* popup, D3DXVECTOR3 position, function<void(EventType&, cPopup*)> EventFuction)
{
	// TODO UI���� �ּ� Ȯ��
	// pBarGauge�� ��ġ�� ���͸� �������� pBarButton�� ��ġ�� ������,
	// pBarGauge�� ��ġ�� pBarButton�� ��ġ�� �������� 0 ~ 100�� ���� ��ȯ�ϰ� ��
	// ��ȯ�ϴ� ������ ��Ŭ������ ���۵Ǵ� �κ�
	
	cButton * pBarButton = new cButton;
	pBarButton->Setup("data/UI/Settings", "NW_Setting_BarSlider.png",
		popup->GetPosition(),
		position.x, position.y, position.z,
		1,
		true, true);
	popup->cButtonPushBack(pBarButton);

	if (EventFuction)
		pBarButton->EventProcess = EventFuction;
	else
		cout << "Setup_BarSliderPopupBtn() EventFuction is NULL" << endl;

	return pBarButton;
}

// �� �Լ��� ���ø����� ����� ����
void BarSliderMoveEvent(EventType message, cPopup* btn)
{
	// json object ������ ����
	static JSON_Object * p_json_object_setting = g_p_jsonManager->get_json_object_Setting();
	
	cButton* button = (cButton*)btn;

	const int movement_range = 290;
	//const int tick = movement_range / 10;
	const int tick = json_Fuction::object_get_double(p_json_object_setting, "BarSliderTick");

	// ������ ��ư�� ��ġ�� �����
	static D3DXVECTOR3 startBtnPosition = button->GetPosition();
	D3DXVECTOR3 btnPosition = button->GetPosition();

	// ���Ұ��� �ƴϱ⿡ static ����
	static float btn_width = button->GetImageInfoWidth() * button->GetPercent();
	static float btn_height = button->GetImageInfoHeight() *  button->GetPercent();
	
	// ���콺 ��ġ�� ����ؾ��ϱ⶧���� static ����
	static D3DXVECTOR2 prev_cur;
	static D3DXVECTOR2 crnt_cur;
	crnt_cur = EventManager->GetMouseCurrent();


	switch (message)
	{
	case EventType::EVENT_MOVE:
		if (button->GetState() == enum_On)
		{
			if (crnt_cur.x >= startBtnPosition.x &&
				crnt_cur.x <= startBtnPosition.x + movement_range)
			{
				D3DXVECTOR2 vec2distance = crnt_cur - prev_cur;
				vec2distance.y = 0; // y���� �̵����� �ʰ� �Ѵ�
				button->MovePosition(vec2distance);
				prev_cur = crnt_cur;
				// TODO json ���⼭ �ٷ� �����Ұ�
				// ���� ��ȯ�ؾ��ϳ�? ��ȯ�Ѵٸ� ��ȯ�� ���� ���ΰ���?
			}
		}
		//case EVENT_MOVE End:
		break;

	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= crnt_cur.x && crnt_cur.x <= btnPosition.x + btn_width)
		{
			if (btnPosition.y <= crnt_cur.y && crnt_cur.y <= btnPosition.y + btn_height)
			{
				prev_cur = EventManager->GetMouseCurrent();
				button->SetStateChange(enum_On);
			}
		}
	}
	break;

	case EventType::EVENT_LBUTTONUP:
	{
		button->SetStateChange(enum_Off);

		if (btnPosition.x < startBtnPosition.x)
			button->SetPosition(D3DXVECTOR2(startBtnPosition.x, btnPosition.y));
		if (btnPosition.x > startBtnPosition.x + movement_range)
			button->SetPosition(D3DXVECTOR2(startBtnPosition.x + movement_range, btnPosition.y));

		// TODO json ���� �׽�Ʈ
		json_object_set_number(p_json_object_setting, "BarSliderMoveEvent", (btnPosition.x - startBtnPosition.x) / tick);
	}
	break;
	};//switch End
}

void BarSliderMoveEvent2(EventType message, cPopup* btn)
{
	cButton* button = (cButton*)btn;

	const int movement_range = 290;
	// ������ ��ư�� ��ġ�� �����
	static D3DXVECTOR3 startBtnPosition = button->GetPosition();
	D3DXVECTOR3 btnPosition = button->GetPosition();

	// ���Ұ��� �ƴϱ⿡ static ����
	static float btn_width = button->GetImageInfoWidth() * button->GetPercent();
	static float btn_height = button->GetImageInfoHeight() *  button->GetPercent();

	// ���콺 ��ġ�� ����ؾ��ϱ⶧���� static ����
	static D3DXVECTOR2 prev_cur;
	static D3DXVECTOR2 crnt_cur;
	crnt_cur = EventManager->GetMouseCurrent();


	switch (message)
	{
	case EventType::EVENT_MOVE:
		if (button->GetState() == enum_On)
		{
			if (crnt_cur.x >= startBtnPosition.x &&
				crnt_cur.x <= startBtnPosition.x + movement_range)
			{
				D3DXVECTOR2 vec2distance = crnt_cur - prev_cur;
				vec2distance.y = 0; // y���� �̵����� �ʰ� �Ѵ�
				button->MovePosition(vec2distance);
				prev_cur = crnt_cur;
				// TODO json ���⼭ �ٷ� �����Ұ�
				// ���� ��ȯ�ؾ��ϳ�? ��ȯ�Ѵٸ� ��ȯ�� ���� ���ΰ���?
			}
		}
		//case EVENT_MOVE End:
		break;

	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= crnt_cur.x && crnt_cur.x <= btnPosition.x + btn_width)
		{
			if (btnPosition.y <= crnt_cur.y && crnt_cur.y <= btnPosition.y + btn_height)
			{
				prev_cur = EventManager->GetMouseCurrent();
				button->SetStateChange(enum_On);
			}
		}
	}
	break;

	case EventType::EVENT_LBUTTONUP:
	{
		button->SetStateChange(enum_Off);

		if (btnPosition.x < startBtnPosition.x)
			button->SetPosition(D3DXVECTOR2(startBtnPosition.x, btnPosition.y));
		if (btnPosition.x > startBtnPosition.x + movement_range)
			button->SetPosition(D3DXVECTOR2(startBtnPosition.x + movement_range, btnPosition.y));
	}
	break;
	};//switch End
}



// �ش� �¾��Լ����� �̺�Ʈ�� ���� �ʽ��ϴ�.
// �� �̹����� �޾� 
cButton* Setup_BarGaugePopupBtn_Legacy(cPopup* popup, D3DXVECTOR3 position)
{
	cPopup * pBarGauge = new cPopup;
	pBarGauge->Setup(
		"data/UI/ConfigurationSettings",
		"����â �� ������ ������ ����.png",
		popup->GetPosition(),
		//-100, 60, 0,
		position.x, position.y, position.z,
		1,
		true, false);
	popup->cButtonPushBack(pBarGauge);

	// pBarGauge�� ��ġ�� ���͸� �������� pBarButton�� ��ġ�� ������,
	// pBarGauge�� ��ġ�� pBarButton�� ��ġ�� �������� 0 ~ 100�� ���� ��ȯ�ϰ� ��
	// ��ȯ�ϴ� ������ ��Ŭ������ ���۵Ǵ� �κ�
	cButton * pBarButton = new cButton;
	pBarButton->Setup("data/UI/ConfigurationSettings", "����â �ٰ����� ���� ��ư ����������.png",
		pBarGauge->GetPosition(),
		185, -8, 0, // << x�� ��ġ�� ��ȭ�ϰ�
					// pBarButton�� x���� ���� -15 ~ 385, 4��ŭ �����϶����� �̺�Ʈ���� 1��ŭ ���� �����ϱ�
		1,
		true, false);
	pBarGauge->cButtonPushBack(pBarButton);

	return pBarButton;
}

void GaugeBarMoveEvent_Legacy(EventType message, cPopup* btn)
{
	cButton* button = (cButton*)btn;
	cPopup* up = btn->GetUpPopUp();

	// ���콺 ��ġ�� ����ؾ��ϱ⶧���� static ����
	static D3DXVECTOR2 prev_cur;
	static D3DXVECTOR2 crnt_cur;
	crnt_cur = EventManager->GetMouseCurrent();
	
	D3DXVECTOR3 btnPosition = button->GetPosition();
	D3DXVECTOR3 upPopupPosition = up->GetPosition();

	// ���Ұ��� �ƴϱ⿡ static ����
	static float btn_width = button->GetImageInfoWidth() * button->GetPercent();
	static float btn_height = button->GetImageInfoHeight() *  button->GetPercent();
	static float up_width = up->GetImageInfoWidth() * up->GetPercent();
	static float up_height = up->GetImageInfoHeight() *  up->GetPercent();

	switch (message)
	{
	case EventType::EVENT_MOVE:
		if (button->GetState() == enum_On)
		{
			if (crnt_cur.x >= upPopupPosition.x &&
				crnt_cur.x <= upPopupPosition.x + up_width)
			{
				D3DXVECTOR2 vec2distance = crnt_cur - prev_cur;
				vec2distance.y = 0;
				button->MovePosition(vec2distance);
				prev_cur = crnt_cur;
				// TODO json ���⼭ �ٷ� �����Ұ�
				// ���� ��ȯ�ؾ��ϳ�? ��ȯ�Ѵٸ� ��ȯ�� ���� ���ΰ���?
			}
		}
		//case EVENT_MOVE End:
		break;

	case EventType::EVENT_LBUTTONDOWN:
	{
		if (btnPosition.x <= crnt_cur.x && crnt_cur.x <= btnPosition.x + btn_width)
		{
			if (btnPosition.y <= crnt_cur.y && crnt_cur.y <= btnPosition.y + btn_height)
			{
				prev_cur = EventManager->GetMouseCurrent();
				button->SetStateChange(enum_On);
			}
		}
	}
	break;

	case EventType::EVENT_LBUTTONUP:
	{
		button->SetStateChange(enum_Off);
			
		if (btnPosition.x < upPopupPosition.x)
			button->SetPosition(D3DXVECTOR2(upPopupPosition.x, btnPosition.y));
		else if (btnPosition.x > upPopupPosition.x + up_width)
			button->SetPosition(D3DXVECTOR2(upPopupPosition.x + up_width, btnPosition.y));
	}
	break;
	};//switch End
}


