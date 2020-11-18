#pragma once
#include "PopUp.h"
class cButton :
	public cPopUp
{
private:
	bool curHoverCheck;
	bool preHoverCheck;


public:
	cButton();
	~cButton();

	void Setup(char* root, char* fileName, D3DXVECTOR3 position, float x, float y, float z);
	void Update(EventType message);
	void Render();
	void Render(D3DXVECTOR3 position);

	int GetState();
	void SetStateChange(int state);

	D3DXVECTOR3 GetPosition();
	float GetImageInfoWidth();
	float GetImageInfoHeight();

	void LoadTexture(char* szFullPath);
	void ChangeSprite(char* szFullPath);

	bool GetCurHoverCheck() { return curHoverCheck; };
	bool GetPreHoverCheck() { return preHoverCheck; };
	void ChangeHoverCheck() { curHoverCheck = !curHoverCheck; };
	void SetPreHoverCheck() { preHoverCheck = curHoverCheck; };
};

