#pragma once
#include "Scene.h"

class Popup;
class Button;

class cGameOverScene :
	public cScene
{
public:
	cGameOverScene(SceneType);
	~cGameOverScene();

	void Setup() override;
	void Reset(int sceneType) override;
};

