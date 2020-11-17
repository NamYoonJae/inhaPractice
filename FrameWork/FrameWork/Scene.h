#pragma once

class cCamera;

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

