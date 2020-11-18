#pragma once


enum SceneType { SCENE_TITLE = 0, SCENE_BOSS1 = 1, SCENE_BOSS_2 = 2 };

class cScene
{
protected:
	SceneType Type;
public:
	cScene(SceneType);
	cScene();
	virtual ~cScene();

	virtual void Setup() = 0;
	virtual void CheckInput() = 0;

	SceneType GetSceneName() { return Type; }
};

