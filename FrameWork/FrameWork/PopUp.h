#pragma once
#include "basic.h"
#include "Observer.h"
#include <functional>
#include "cObject.h"
class cButton;

enum
{
	enum_Off = 1000,
	enum_On = 1001,
	enum_Hover = 1002,
};

class cPopUp  : public cObserver ,public cObject
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
	RECT m_Rect;

	vector<cButton*> m_vecBtnList;
	cButton* m_pButton;


public:
	cPopUp();
	~cPopUp();

	virtual void Setup(char* root, char* fileName, D3DXVECTOR3 positionXYZ);
	virtual void Update(EventType message);
	virtual void Render(D3DXMATRIXA16 * pmat = NULL);
	void Update() override{};
	void cButtonPushBack(cButton*);
	virtual int GetState();
	virtual void SetStateChange(int state);
	virtual D3DXVECTOR3 GetPosition();
	std::function<void(EventType&, cPopUp*)> EventProcess;
	
	virtual float GetImageInfoWidth();
	virtual float GetImageInfoHeight();

	virtual void LoadTexture(char* szFullPath);
	virtual void ChangeSprite(char* szFullPath);

};

