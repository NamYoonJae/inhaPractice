#pragma once
#include "Scene.h"

class cTitleScene :
	public cScene
{
private:

public:
	cTitleScene(SceneType);
	~cTitleScene();

	void Setup();
};

