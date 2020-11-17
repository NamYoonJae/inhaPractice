#include "stdafx.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ObjectPool.h"
#include "GameScene.h"
#include "cCharater.h"
#include "Camera.h"
#include "SkyBox.h"
cSceneManager::cSceneManager()
	:m_CurrentScene(nullptr)
{
	
}


cSceneManager::~cSceneManager()
{
	//SafeDelete(m_CurrentScene);
	
	map<string, cScene*> Scenes;
	
	m_mapScenes.swap(Scenes);
}

cScene* cSceneManager::GetCurrentScene()
{
	return m_CurrentScene;
}

void cSceneManager::Setup()
{
	InitializeCriticalSection(&cs);

	{
		SkyBox* pSkyBox = new SkyBox;
		pSkyBox->Setup("data/HeightMapData", "skyhorizon.png");
		
		cCamera *pCamera = new cCamera;
		cCharater*	pCharater = new cCharater;

		pCharater->Setup();
		pCharater->Tagging(Tag::Tag_Player);
		
		pCamera->Setup(pCharater->GetPos());
		pCamera->Tagging(Tag::Tag_Camera);

		pSkyBox->SetPos(pCamera->GetEye());
		pSkyBox->Tagging(Tag::Tag_SkyBox);
		EventManager->Attach(pCharater);
		EventManager->Attach(pCamera);

		ObjectManager->AddStaticChild(pSkyBox);
		ObjectManager->AddStaticChild(pCamera);
		ObjectManager->AddStaticChild(pCharater);		
	}
	
	cGameScene* gameScene = new cGameScene("MainGame");
	gameScene->Setup();
	m_CurrentScene = gameScene;

	AddScene(gameScene->GetSceneName(), gameScene);
}

void cSceneManager::AddScene(string name, cScene* scene)
{
	if(m_mapScenes.find(name) == m_mapScenes.end())
	{
		m_mapScenes[name] = scene;
	}
}

void cSceneManager::DestroyScene(string name)
{
	if (m_mapScenes.find(name) != m_mapScenes.end())
	{
		SafeDelete(m_mapScenes[name]);
		m_mapScenes.erase(m_mapScenes.find(name));
	}
}

void cSceneManager::ChangeScene(string name)
{
	if (m_mapScenes.find(name) != m_mapScenes.end())
	{
		if(m_CurrentScene != m_mapScenes[name])
		{
			m_CurrentScene = m_mapScenes[name];
		}
	}
}

void cSceneManager::Destroy()
{
	for (auto scene : m_mapScenes)
	{
		SafeDelete(scene.second);
	}

	m_mapScenes.clear();
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
			// ·ÎµùÃ¢
		}
	}
	LeaveCriticalSection(&cs);
}
