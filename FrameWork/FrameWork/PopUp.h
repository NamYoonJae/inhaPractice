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
		enum_Hover = 2,
	};
	LPD3DXSPRITE m_pSprite;
	D3DXIMAGE_INFO m_ImageInfo;
	LPDIRECT3DTEXTURE9 m_pTextureUI;

	int m_State;
	D3DXVECTOR3 m_Position;

	vector<cButton*> m_vecBtnList;
	cButton* m_pButton;

	cButton* m_pButtonHover;
	cButton* m_pButtonClick;

public:
	cPopUp();
	~cPopUp();

	virtual void Setup(char* root, char* fileName, D3DXVECTOR3 positionXYZ);
	virtual void Update(std::string);
	virtual void Render();

	void cButtonPushBack(cButton*);
	virtual int GetState();
	virtual void SetStateChange(int state);
};

