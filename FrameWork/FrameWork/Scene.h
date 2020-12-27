#pragma once


enum SceneType
{
	SCENE_TITLE = 0,
	SCENE_BOSS_1 = 1,
	SCENE_BOSS_2 = 2,
	SCENE_TROPHIES = 3,


	SCENE_GAMEOVER = 4,
	SCENE_CLEAR = 5
};

class cScene
{
protected:
	SceneType Type;
public:
	cScene(SceneType);
	virtual ~cScene();

	virtual void Setup() = 0;
	virtual void Reset(int sceneType) = 0; // 

	SceneType GetSceneName() { return Type; }
};

