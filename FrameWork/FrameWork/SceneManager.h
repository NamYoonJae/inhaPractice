#pragma once

#define g_pSceneManager cSceneManager::GetInstance()

class cScene;

class cSceneManager
{
	Singletone(cSceneManager);
private:
	map<string, cScene*> m_mapScenes;
	cScene* m_CurrentScene;
	
public:
	cScene* GetCurrentScene();
	void Setup();
	void AddScene(string name, cScene* scene);
	void DestroyScene(string name);
	void ChangeScene(string name);

	void Destroy();
};

