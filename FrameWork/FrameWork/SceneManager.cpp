#include "stdafx.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ObjectPool.h"
#include "GameScene.h"
#include "cCharater.h"
#include "Camera.h"
#include "SkyBox.h"
#include "TitleScene.h"

cSceneManager::cSceneManager()
	:m_CurrentScene(nullptr)
{
	m_vecScenes.resize(2);
	const std::vector<cScene*>::iterator it = m_vecScenes.begin();

	//*(it + SceneType::SCENE_TITLE)
	*(it + SceneType::SCENE_TITLE) = new cTitleScene(SceneType::SCENE_TITLE);
	*(it + SceneType::SCENE_BOSS1) = new cGameScene(SceneType::SCENE_BOSS1);
}


cSceneManager::~cSceneManager()
{
	//SafeDelete(m_CurrentScene);
	Destroy();
	
}

cScene* cSceneManager::GetCurrentScene()
{
	return m_CurrentScene;
}

void cSceneManager::Setup()
{
	InitializeCriticalSection(&cs);

	ObjectManager->Revert();

	m_CurrentScene = m_vecScenes[SceneType::SCENE_TITLE];
	
	m_CurrentScene->Setup();
}

void cSceneManager::ChangeScene()
{
	/// 씬을 바꾸는 법
	///
	int nRandom = 1;//rand()%2;
	LoadScene(nRandom);
}

void cSceneManager::Destroy()
{
	// 게임 종료
	vector<cScene*> Scenes;
	m_vecScenes.swap(Scenes);
	return;
}

void cSceneManager::LoadScene(int SceneType)
{
	m_CurrentScene = m_vecScenes[SceneType];

	EnterCriticalSection(&cs);
	ObjectManager->Revert();
	m_pThread = new std::thread(&cScene::Setup, m_CurrentScene);
	if(m_pThread)
	{
		m_pThread->join();
		while(m_pThread->joinable())
		{
			// 로딩창
		}
	}
	LeaveCriticalSection(&cs);
}
