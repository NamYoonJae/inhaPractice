#include "stdafx.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Scene.h"


cScene::cScene(string name)
	:m_SceneName(name)
	,m_cMainCamera(NULL)
{
	//g_pSceneManager->m_mapScenes.find("");
}


cScene::~cScene()
{
	SafeDelete(m_cMainCamera);
}
