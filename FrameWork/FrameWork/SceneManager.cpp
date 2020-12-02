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

cSceneManager::cSceneManager()
	:m_CurrentScene(nullptr)
{
	m_vecScenes.resize(4);
	const std::vector<cScene*>::iterator it = m_vecScenes.begin();


	*(it + SceneType::SCENE_TITLE) = new cTitleScene(SceneType::SCENE_TITLE);
	*(it + SceneType::SCENE_BOSS_1) = new cGameScene(SceneType::SCENE_BOSS_1);


	*(it + SceneType::SCENE_GAMEOVER) = new cGameOverScene(SceneType::SCENE_GAMEOVER);
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

	//m_CurrentScene = m_vecScenes[SceneType::SCENE_TITLE];
	//m_CurrentScene = m_vecScenes[SceneType::SCENE_GAMEOVER];
	
	//m_CurrentScene->Setup();
	ChangeScene(0);
}

void cSceneManager::ChangeScene(int sceneNum)
{
	// ���� �ٲٴ� ��
	//boss1�� �Ѿ�´� �̰� SceneNumber
	int nRandom = sceneNum;//rand()%2;
	LoadScene(nRandom);
}

void cSceneManager::Destroy()
{
	// ���� ����
	vector<cScene*> Scenes;
	m_vecScenes.swap(Scenes);
	return;
}

void cSceneManager::LoadScene(int SceneType)
{
	//SceneTpye �� �� �����̴� ->��, �ٲ� ��Number���� Type
	
	//
	// setup
	//m_CurrentScene->Reset();

	//
	m_CurrentScene = m_vecScenes[SceneType];

	EnterCriticalSection(&cs);
	ObjectManager->Revert();
	m_pThread = new std::thread(&cScene::Setup, m_CurrentScene);
	if(m_pThread)
	{
		m_pThread->join();
		while(m_pThread->joinable())
		{
			// �ε�â
		}
	}
	LeaveCriticalSection(&cs);
}