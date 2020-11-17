#pragma once


enum SceneName { SCENE_TITLE = 0, SCENE_BOSS1 = 1, SCENE_BOSS_2 = 2 };

class cScene
{
protected:
	string	 m_SceneName;
public:
	//cScene();
	cScene(string name);
	virtual ~cScene();

	virtual void Setup() = 0;
	virtual void CheckInput() = 0;

	string GetSceneName() { return m_SceneName; }
};

