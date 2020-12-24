#pragma once
#include "basic.h"
#include "Observer.h"
#include "cObject.h"
#include <functional>

class cButton;
class cPopup;
class cPaladin;
class cTrophies;

//자식 뿐만 아니라 버튼 이벤트 헤더에서도 사용하기 때문에 전역으로 설정
enum
{
	enum_Off = 1000,
	enum_On = 1001,
	enum_Hover = 1002,
};


class cPopup : public cObserver , public cObject
{
protected:
	bool m_Fixed;
	//Power OnOff 기능이 있는지 없는지 고정이면 true 고정 아니면 false
	bool m_Power;
	//bool m_EventPower;

	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_ImageInfo;
	float m_ImageInfoWidth;
	float m_ImageInfoHeight;
	LPDIRECT3DTEXTURE9 m_pTextureUI;
	float m_Percentage;	//스케일링 할 값

	int m_State;//MouseOn MouseOff Hover
	D3DXVECTOR3 m_Position;
	RECT m_Rect;

	vector<cPopup*> m_vecPopupBtnList;

	cPopup * pParent;

	string str_filename;

	cPaladin * m_pPaladin; //다른 클래스의 값을 가져오기 위해 사용(ex> 팔라딘 체력/스테미나)
	cTrophies* m_pTrophies;

public:
	
	cPopup();
	~cPopup();

	virtual void Setup(
		char* root, 
		char* fileName, 
		D3DXVECTOR3 position, 
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



	//태그까지 추가한 Setup //2020-12-01

	virtual void Setup(
		char* root,
		char* fileName,
		D3DXVECTOR3 position,
		float percent,
		bool powerOnOff,
		bool fixed,
		int tag
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
		bool fixed,
		int tag
	);

	void Update() override;
	virtual void Update(EventType message);
	virtual void Render(D3DXMATRIXA16 * pmat = NULL);
	void cButtonPushBack(cPopup*);
	virtual int GetState();
	virtual void SetStateChange(int state); // TODO !! SetState 로 이름변경할것
	virtual D3DXVECTOR3 GetPosition();
	function<void(EventType&, cPopup*)> EventProcess;

	virtual float GetImageInfoWidth();
	virtual float GetImageInfoHeight();

	virtual void LoadTexture(char* szFullPath);
	virtual void ChangeSprite(char* szFullPath);
	
	virtual float GetPercent();

	virtual void PowerOnOff();
	virtual void PowerOnOff(bool power);
	virtual void PowerOnOff_List();
	virtual void PowerOnOff_List(bool power);
	virtual void PowerOnOff_OnlySelf();
	virtual void PowerOnOff_OnlySelf(bool power);
	virtual void PowerOnOff_List_OnlySelf();
	virtual void PowerOnOff_List_OnlySelf(bool power);
	
	//void SetFix(bool Fixed);
	
	virtual void Destroy();

	virtual cPopup* GetTopPopUp();
	virtual cPopup* GetUpPopUp();
	
	virtual cPopup* GetPopupBtn();
	virtual cPopup* GetPopupBtn(int index);

	void MovePosition(D3DXVECTOR2 distance);
	void SetPosition(D3DXVECTOR2 position);
	
	int GetPopUpListSize();
	bool GetPowerState();

	void SetPaladinReference(cPaladin*);
	cPaladin* GetPaladinReference();
	void SetImageInfoWidth(float percent);

	virtual void SetTrophiesReference(cTrophies*);
	virtual cTrophies* GetTrophiesReference();
};

