#pragma once
#include "PopUp.h"
class cButton :
	public cPopUp
{
private:

public:
	cButton();
	~cButton();

	void Setup(char* root, char* fileName, D3DXVECTOR3 position, float x, float y, float z);
	void Update(std::string);
	void Render();
	void Render(D3DXVECTOR3 position); //click과 hover 이미지 좌표값만 가져와서 랜더

	int GetState();
	void StateChange(int state);
	D3DXVECTOR3 GetPosition();
	float GetImageInfoWidth();
	float GetImageInfoHeight();

};

