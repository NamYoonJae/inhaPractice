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

	// TODO 생성시 파일 불러올 것 -> 이벤트 함수로 옮기는 것 고려
	pChkButton->SetStateChange(enum_On);

	if (EventFuction)
		pChkButton->EventProcess = EventFuction;
	else
		cout << "Setup_CheckBtn() EventFuction is NULL" << endl;

	return pChkButton;
}

void CheckBtnEvent(EventType message, cPopup* btn)
{
	// json object 포인터 생성
	static JSON_Object* p_json_object_UI = g_p_jsonManager->get_json_object_UI();
	static JSON_Object* p_json_object_setting = g_p_jsonManager->get_json_object_Setting();

	cButton* button = (cButton*)btn;

	D3DXVECTOR3 btnPosition = button->GetPosition();

	// 변할값이 아니기에 static 선언, static 삭제 고려할 것
	static float btn_width = button->GetImageInfoWidth() * button->GetPercent();
	static float btn_height = button->GetImageInfoHeight() * button->GetPercent();

	// 마우스 위치를 기억해야하기때문에 static 선언
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
					// TODO 세팅 저장하기
				}
				else if (button->GetState() == enum_Off) {
					string full_path = json_Fuction::object_get_string(p_json_object_UI, "UI/Settings/directory")
						+ '/' + json_Fuction::object_get_string(p_json_object_UI, "UI/Settings/ToggleButton_Off/filename");
					char c_path[200] = { 0 };
					strcpy(c_path, full_path.c_str());

					button->ChangeSprite(c_path);
					// TODO 세팅 저장하기
				}


			}
		}
	}
	break;

	default:
		break;
	}

}


// 셋업함수 종료후 json파일에서 데이터를 불러와 위치이동
cButton* Setup_BarSliderPopupBtn(cPopup* popup, D3DXVECTOR3 position, function<void(EventType&, cPopup*)> EventFuction)
{
	// TODO UI관련 주석 확인
	// pBarGauge의 위치를 벡터를 기준으로 pBarButton의 위치를 제한함,
	// pBarGauge의 위치와 pBarButton의 위치를 기준으로 0 ~ 100의 값을 반환하게 함
	// 반환하는 시점은 좌클릭업이 시작되는 부분
	
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

// 이 함수를 템플릿으로 사용할 예정
void BarSliderMoveEvent(EventType message, cPopup* btn)
{
	// json object 포인터 생성
	static JSON_Object * p_json_object_setting = g_p_jsonManager->get_json_object_Setting();
	
	cButton* button = (cButton*)btn;

	const int movement_range = 290;
	//const int tick = movement_range / 10;
	const int tick = json_Fuction::object_get_double(p_json_object_setting, "BarSliderTick");

	// 생성시 버튼의 위치를 기억함
	static D3DXVECTOR3 startBtnPosition = button->GetPosition();
	D3DXVECTOR3 btnPosition = button->GetPosition();

	// 변할값이 아니기에 static 선언
	static float btn_width = button->GetImageInfoWidth() * button->GetPercent();
	static float btn_height = button->GetImageInfoHeight() *  button->GetPercent();
	
	// 마우스 위치를 기억해야하기때문에 static 선언
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
				vec2distance.y = 0; // y값은 이동하지 않게 한다
				button->MovePosition(vec2distance);
				prev_cur = crnt_cur;
				// TODO json 여기서 바로 저장할것
				// 값을 반환해야하나? 반환한다면 반환한 값은 어디로가지?
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

		// TODO json 저장 테스트
		json_object_set_number(p_json_object_setting, "BarSliderMoveEvent", (btnPosition.x - startBtnPosition.x) / tick);
	}
	break;
	};//switch End
}

void BarSliderMoveEvent2(EventType message, cPopup* btn)
{
	cButton* button = (cButton*)btn;

	const int movement_range = 290;
	// 생성시 버튼의 위치를 기억함
	static D3DXVECTOR3 startBtnPosition = button->GetPosition();
	D3DXVECTOR3 btnPosition = button->GetPosition();

	// 변할값이 아니기에 static 선언
	static float btn_width = button->GetImageInfoWidth() * button->GetPercent();
	static float btn_height = button->GetImageInfoHeight() *  button->GetPercent();

	// 마우스 위치를 기억해야하기때문에 static 선언
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
				vec2distance.y = 0; // y값은 이동하지 않게 한다
				button->MovePosition(vec2distance);
				prev_cur = crnt_cur;
				// TODO json 여기서 바로 저장할것
				// 값을 반환해야하나? 반환한다면 반환한 값은 어디로가지?
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



// 해당 셋업함수에서 이벤트를 넣지 않습니다.
// 바 이미지를 받아 
cButton* Setup_BarGaugePopupBtn_Legacy(cPopup* popup, D3DXVECTOR3 position)
{
	cPopup * pBarGauge = new cPopup;
	pBarGauge->Setup(
		"data/UI/ConfigurationSettings",
		"설정창 바 게이지 사이즈 조정.png",
		popup->GetPosition(),
		//-100, 60, 0,
		position.x, position.y, position.z,
		1,
		true, false);
	popup->cButtonPushBack(pBarGauge);

	// pBarGauge의 위치를 벡터를 기준으로 pBarButton의 위치를 제한함,
	// pBarGauge의 위치와 pBarButton의 위치를 기준으로 0 ~ 100의 값을 반환하게 함
	// 반환하는 시점은 좌클릭업이 시작되는 부분
	cButton * pBarButton = new cButton;
	pBarButton->Setup("data/UI/ConfigurationSettings", "설정창 바게이지 조절 버튼 사이즈조정.png",
		pBarGauge->GetPosition(),
		185, -8, 0, // << x의 위치만 변화하게
					// pBarButton의 x값의 범위 -15 ~ 385, 4만큼 움직일때마다 이벤트에서 1만큼 값을 변경하기
		1,
		true, false);
	pBarGauge->cButtonPushBack(pBarButton);

	return pBarButton;
}

void GaugeBarMoveEvent_Legacy(EventType message, cPopup* btn)
{
	cButton* button = (cButton*)btn;
	cPopup* up = btn->GetUpPopUp();

	// 마우스 위치를 기억해야하기때문에 static 선언
	static D3DXVECTOR2 prev_cur;
	static D3DXVECTOR2 crnt_cur;
	crnt_cur = EventManager->GetMouseCurrent();
	
	D3DXVECTOR3 btnPosition = button->GetPosition();
	D3DXVECTOR3 upPopupPosition = up->GetPosition();

	// 변할값이 아니기에 static 선언
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
				// TODO json 여기서 바로 저장할것
				// 값을 반환해야하나? 반환한다면 반환한 값은 어디로가지?
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


