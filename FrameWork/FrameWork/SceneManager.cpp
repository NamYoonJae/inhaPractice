#include "stdafx.h"
#include "Scene.h"
#include "SceneManager.h"

#include "GameScene.h"


cSceneManager::cSceneManager()
	:m_CurrentScene(nullptr)
{
}


cSceneManager::~cSceneManager()
{
}

cScene* cSceneManager::GetCurrentScene()
{
	return m_CurrentScene;
}

void cSceneManager::Setup()
{
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
