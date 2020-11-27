#pragma once
#include "basic.h"
#include "Observer.h"
#include "cObject.h"
#include <functional>

class cButton;
class cPopUp;

//자식 뿐만 아니라 버튼 이벤트 헤더에서도 사용하기 때문에 전역으로 설정
enum
{
	enum_Off = 1000,
	enum_On = 1001,
	enum_Hover = 1002,
};


class cPopUp : public cObserver , public cObject
{
protected:
	bool m_Fixed;
	//Power OnOff 기능이 있는지 없는지 고정이면 true 고정 아니면 false
	bool m_Power;

	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_ImageInfo;
	LPDIRECT3DTEXTURE9 m_pTextureUI;
	float m_Percentage;	//스케일링 할 값

	int m_State;
	D3DXVECTOR3 m_Position;
	RECT m_Rect;

	vector<cPopUp*> m_vecPopupBtnList;

	cPopUp * pParent;

	string str_filename;
public:
	
	cPopUp();
	~cPopUp();

	virtual void Setup(
		char* root, 
		char* fileName, 
		D3DXVECTOR3 positionXYZ, 
		float percent, 
		bool powerOnOff, 
		bool fixed
	);
	virtual void Setup(
		char* root,
		char* fileName,
		D3DXVECTOR3 position,
		float x,
		float y,
		float z,
		float percent,
		bool powerOnOff,
		bool fixed
	);

	void Update() override {};
	virtual void Update(EventType message);
	virtual void Render(D3DXMATRIXA16 * pmat = NULL);
	void cButtonPushBack(cPopUp*);
	virtual int GetState();
	virtual void SetStateChange(int state);
	virtual D3DXVECTOR3 GetPosition();
	function<void(EventType&, cPopUp*)> EventProcess;

	virtual float GetImageInfoWidth();
	virtual float GetImageInfoHeight();

	virtual void LoadTexture(char* szFullPath);
	virtual void ChangeSprite(char* szFullPath);
	
	virtual float GetPercent();

	virtual void PowerOnOff();
	virtual void PowerOnOff(bool power);
	virtual void vecListPowerOnOff();
	virtual void vecListPowerOnOff(bool power);
	virtual void PowerOnOffSelf();
	virtual void PowerOnOffSelf(bool power);

	void SetFix(bool Fixed);
	
	virtual void Destroy();

	virtual cPopUp* GetTopPopUp();
	virtual cPopUp* GetUpPopUp();
	
	virtual cPopUp* GetPopupBtn();
	virtual cPopUp* GetPopupBtn(int index);

	void MovePosition(D3DXVECTOR2 distance);
	void SetPosition(D3DXVECTOR2 position);
	
	int GetPopUpListSize();
	bool GetPowerState();
};

