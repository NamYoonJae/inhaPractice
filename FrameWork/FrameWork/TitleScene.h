#pragma once
#include "Scene.h"

class PopUp;
class Button;

class cTitleScene :
	public cScene
{
private:


public:
	cTitleScene(SceneType);
	~cTitleScene();

	void Setup();
};

