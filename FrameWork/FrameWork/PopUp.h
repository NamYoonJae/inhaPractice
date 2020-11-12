#pragma once
#include "basic.h"
#include "Observer.h"
#include <functional>
class cButton;

class cPopUp  : public cObserver
{
protected:

	enum
	{
		enum_Off = 1000,
		enum_On = 1001,
		enum_Hover = 1002,
	};
	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_ImageInfo;
	LPDIRECT3DTEXTURE9 m_pTextureUI;

	int m_State;
	D3DXVECTOR3 m_Position;

	vector<cButton*> m_vecBtnList;
	cButton* m_pButton;

public:
	cPopUp();
	~cPopUp();

	virtual void Setup(char* root, char* fileName, D3DXVECTOR3 positionXYZ);
	virtual void Update(EventType message);
	virtual void Render();

	void cButtonPushBack(cButton*);
	virtual int GetState();
	virtual void SetStateChange(int state);

	//std::function<void(string&, void*, cButton*)> EventProcess;
	std::function<void(EventType&, cPopUp*)> EventProcess;
	
};

