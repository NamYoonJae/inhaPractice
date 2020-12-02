#pragma once

#define g_pSceneManager cSceneManager::GetInstance()

class cScene;

class cSceneManager
{
	Singletone(cSceneManager);
private:
	vector<cScene*> m_vecScenes;
	cScene* m_CurrentScene;

	CRITICAL_SECTION	cs;
	std::thread*		m_pThread;
public:
	cScene* GetCurrentScene();
	void Setup();	
	void ChangeScene(int sceneNum);
	void Destroy();
	void LoadScene(int SceneType);
};

