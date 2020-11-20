#pragma once
#include "PopUp.h"
class cButton :
	public cPopUp
{
private:
	float m_X;
	float m_Y;
	float m_Z;

	//bool curHoverCheck;
	//bool preHoverCheck;
	
	int m_PreState;


public:
	cButton();
	~cButton();

	void Setup(char* root, char* fileName, D3DXVECTOR3 position, float x, float y, float z, float percent, bool powerOnOff);
	void Update(EventType message);
	void Render();
	//void Render(D3DXVECTOR3 position);

	int GetState();
	void SetStateChange(int state);

	int GetPreState();
	void SetPreState(int state);


	D3DXVECTOR3 GetPosition();
	float GetImageInfoWidth();
	float GetImageInfoHeight();

	void LoadTexture(char* szFullPath);
	void ChangeSprite(char* szFullPath);

	//bool GetCurHoverCheck() { return curHoverCheck; };
	//bool GetPreHoverCheck() { return preHoverCheck; };
	//void ChangeHoverCheck() { curHoverCheck = !curHoverCheck; };
	//void SetPreHoverCheck() { preHoverCheck = curHoverCheck; };


	float GetPercent();
	void PowerOnOff();
};

