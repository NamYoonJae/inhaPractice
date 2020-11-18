#pragma once


enum SceneType { SCENE_TITLE = 0, SCENE_BOSS1 = 1, SCENE_BOSS_2 = 2 };

class cScene
{
protected:
	SceneType Type;
public:
	cScene(SceneType);
	virtual ~cScene();

	virtual void Setup() = 0;
	

	SceneType GetSceneName() { return Type; }
};

