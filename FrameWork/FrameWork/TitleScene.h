#pragma once
#include "Scene.h"

class PopUp;
class Button;
enum TAG_UI;

class cTitleScene :
	public cScene
{
private:


public:
	cTitleScene(SceneType);
	~cTitleScene();

	void Setup() override;
	void Reset(int sceneType) override;
};

