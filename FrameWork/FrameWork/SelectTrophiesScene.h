#pragma once
#include "Scene.h"

class Popup;

class cSelectTrophiesScene :
	public cScene
{
public:
	cSelectTrophiesScene(SceneType);
	~cSelectTrophiesScene();

	void Setup() override;
	void Reset(int SceneType) override;
};

