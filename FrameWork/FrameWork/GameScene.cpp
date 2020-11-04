#include "stdafx.h"
#include "Camera.h"
#include "GameScene.h"


cGameScene::cGameScene(string name)
	:cScene(name)
{
}


cGameScene::~cGameScene()
{
}

void cGameScene::Setup()
{
	m_cMainCamera = new cCamera;
	m_cMainCamera->Setup(&D3DXVECTOR3(0, 0, 0));
}

void cGameScene::CheckInput()
{
}

void cGameScene::Update()
{
	if (m_cMainCamera)
		m_cMainCamera->Update();
}

void cGameScene::Render()
{
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
