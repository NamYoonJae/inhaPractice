#include "stdafx.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ObjectPool.h"
#include "GameScene.h"
#include "cCharater.h"
#include "Camera.h"
#include "SkyBox.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "SelectTrophiesScene.h"
#include "GameClearScene.h"

cSceneManager::cSceneManager()
	:m_CurrentScene(nullptr)
{
	m_vecScenes.resize(6);
	const std::vector<cScene*>::iterator it = m_vecScenes.begin();

	*(it + SceneType::SCENE_TITLE) = new cTitleScene(SceneType::SCENE_TITLE);
	*(it + SceneType::SCENE_BOSS_1) = new cGameScene(SceneType::SCENE_BOSS_1);
	//*(it + SceneType::SCENE_BOSS_2) = new cGameScene(SceneType::SCENE_BOSS_2);

	*(it + SceneType::SCENE_TROPHIES) = new cSelectTrophiesScene(SceneType::SCENE_TROPHIES);
	*(it + SceneType::SCENE_GAMEOVER) = new cGameOverScene(SceneType::SCENE_GAMEOVER);
	*(it + SceneType::SCENE_CLEAR) = new cGameClearScene(SceneType::SCENE_CLEAR);
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

	//ObjectManager->Revert();

	m_CurrentScene = m_vecScenes[SceneType::SCENE_TITLE];
	//m_CurrentScene = m_vecScenes[SceneType::SCENE_GAMEOVER];

	m_CurrentScene->Setup();
	//ChangeScene(TagUI_Title);
}

void cSceneManager::ChangeScene(int sceneNum)
{
	// 씬을 바꾸는 법
	// rand()%2;
	LoadScene(sceneNum);
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

	m_CurrentSceneType = SceneType; // 선행해서 실행되어야 함
	//
	// setup
	
	//
	m_CurrentScene->Reset(SceneType);
	m_CurrentScene = m_vecScenes[SceneType];

	
	EnterCriticalSection(&cs);
	//ObjectManager->Revert();
	
	m_pThread = new std::thread(&cScene::Setup, m_CurrentScene);
	if (m_pThread)
	{
		m_pThread->join();
		while (m_pThread->joinable())
		{
			// 로딩창
		}
		SafeDelete(m_pThread);
	}
	LeaveCriticalSection(&cs);
}

int cSceneManager::GetCurrentSceneType()
{
	return m_CurrentSceneType;
}
