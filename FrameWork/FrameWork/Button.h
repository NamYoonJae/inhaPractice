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
	void Update();
	void Render();

	int GetState();
	void StateChange(int state);

};

