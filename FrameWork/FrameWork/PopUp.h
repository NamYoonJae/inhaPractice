#pragma once
#include "basic.h"
class cButton;

class cPopUp  : public cObserver
{
protected:
	enum
	{
		enum_Off = 0,
		enum_On = 1,
		enum_hover = 2,
	};
	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_ImageInfo;
	LPDIRECT3DTEXTURE9 m_pTextureUI;

	/*
	LPD3DXFONT m_pFont;
	D3DXVECTOR3 m_FontPosition;
	string m_Text;
	*/

	int m_State;
	D3DXVECTOR3 m_Position;

	POINT m_ptPrevMouse;
	POINT m_Click;

	vector<cButton*> m_vecBtnList;
	cButton* m_pccButton;

public:
	cPopUp();
	~cPopUp();

	virtual void Setup(char* root, char* fileName, D3DXVECTOR3 positionXYZ);
	virtual void Update(std::string);
	virtual void Render();

	/*
	void FontCreate(char* szText);
	void Text_Render();
	*/

	//D3DXVECTOR3 GetPosition();
	void ccButtonPushBack(cButton&);
	virtual int GetState();
	virtual void StateChange(int state);
};

