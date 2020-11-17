#pragma once
#include "Scene.h"

class cGameScene : public cScene
{
private:

public:
	cGameScene(string name);
	~cGameScene();

	void Setup() override;
	void CheckInput() override;

};

