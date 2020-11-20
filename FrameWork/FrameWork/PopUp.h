#pragma once
#include "basic.h"
#include "Observer.h"
#include <functional>
#include "cObject.h"
class cButton;

//자식 뿐만 아니라 버튼 이벤트 헤더에서도 사용하기 때문에 전역으로 설정
enum
{
	enum_Off = 1000,
	enum_On = 1001,
	enum_Hover = 1002,
};


class cPopUp  : public cObserver ,public cObject
{
protected:

	bool m_Power;

	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_ImageInfo;
	LPDIRECT3DTEXTURE9 m_pTextureUI;

	int m_State;
	D3DXVECTOR3 m_Position;
	RECT m_Rect;

	vector<cPopUp*> m_vecBtnList;
	cButton* m_pButton;

	float m_Percentage;


public:
	cPopUp();
	~cPopUp();

	virtual void Setup(char* root, char* fileName, D3DXVECTOR3 positionXYZ, float percent);
	virtual void Update(EventType message);
	virtual void Render(D3DXMATRIXA16 * pmat = NULL);
	void Update() override{};
	void cButtonPushBack(cPopUp*);
	virtual int GetState();
	virtual void SetStateChange(int state);
	virtual D3DXVECTOR3 GetPosition();
	std::function<void(EventType&, cPopUp*)> EventProcess;
	
	virtual float GetImageInfoWidth();
	virtual float GetImageInfoHeight();

	virtual void LoadTexture(char* szFullPath);
	virtual void ChangeSprite(char* szFullPath);

	virtual float GetPercent();

	virtual void PowerOnOff();

};

