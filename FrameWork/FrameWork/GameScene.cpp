#include "stdafx.h"
#include "Camera.h"
#include "Grid.h"
#include "TimerManager.h"
#include "FontManager.h"
#include "GameScene.h"


cGameScene::cGameScene(string name)
	:cScene(name)
	,m_pGrid(nullptr)
{
}


cGameScene::~cGameScene()
{
}

void cGameScene::Setup()
{
	m_cMainCamera = new cCamera;
	m_cMainCamera->Setup(NULL);

	m_pGrid = new cGrid;
	m_pGrid->Setup();
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

	g_pTimeManager->DrawFPS();
	m_pGrid->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
