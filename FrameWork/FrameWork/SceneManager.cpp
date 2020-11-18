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

	//m_CurrentScene = m_vecScenes[SceneType::SCENE_TITLE];
	m_CurrentScene = m_vecScenes[SceneType::SCENE_BOSS1];
	m_CurrentScene->Setup();
}

void cSceneManager::ChangeScene()
{
	/// 씬을 바꾸는 법
	///
	LoadScene();
}

void cSceneManager::Destroy()
{
	vector<cScene*> Scenes;
	m_vecScenes.swap(Scenes);
	return;
}

void cSceneManager::LoadScene()
{

	if (m_CurrentScene == NULL)
		return;

	EnterCriticalSection(&cs);
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
