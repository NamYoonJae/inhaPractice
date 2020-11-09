#pragma once

class cCamera;

class cScene
{
protected:
	string	 m_SceneName;
	cCamera* m_pMainCamera;
	
public:
	//cScene();
	cScene(string name);
	virtual ~cScene();

	virtual void Setup() = 0;
	virtual void CheckInput() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	string GetSceneName() { return m_SceneName; }
};

