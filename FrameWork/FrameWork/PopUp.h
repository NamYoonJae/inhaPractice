#pragma once
#include "basic.h"
class Button;

class PopUp
{
protected:
	enum
	{
		Off = 0,
		On = 1,
		hover = 2,
	};
	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_ImageInfo;
	LPDIRECT3DTEXTURE9 m_pTextureUI;

	LPD3DXFONT m_pFont;
	string text;

	int m_State;
	D3DXVECTOR3 m_Position;

	bool m_IsLButtonDown;
	bool m_IsRButtonDown;
	POINT m_ptPrevMouse;
	POINT m_Click;

	vector<Button*> vecBtnList;


public:
	PopUp();
	~PopUp();

	virtual void Setup(char* root, char* fileName);
	virtual void Update();
	virtual void Render();

	void FontCreate(char* szText);
	void Text_Render();


};

