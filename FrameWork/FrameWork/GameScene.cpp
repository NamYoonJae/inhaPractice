#include "stdafx.h"
#include "Camera.h"
#include "Grid.h"
#include "TimerManager.h"
#include "FontManager.h"
#include "ObjObject.h"
#include "GameScene.h"
#include "cTerrain.h"

cGameScene::cGameScene(string name)
	:cScene(name)
	,m_pGrid(nullptr)
	,m_pObjUnit(nullptr)
	,m_pTerrain(nullptr)
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

	m_pObjUnit = new cObjMesh;
	m_pObjUnit->Setup("data/ObjFile", "box.obj");
	m_pObjUnit->SetScale(D3DXVECTOR3(0.3f, 0.3f, 0.3f));

	if(m_pTerrain == NULL)
	{
		m_pTerrain = new cTerrain;
		m_pTerrain->Setup("data/HeightMapData", "terrain.jpg", "HeightMap.raw");
	}
}

void cGameScene::CheckInput()
{
}

void cGameScene::Update()
{
	if (m_cMainCamera)
		m_cMainCamera->Update();

	if (m_pTerrain)
	{
		static D3DXVECTOR3 vec{ 0,0,0 };
		static int cnt = 0;
		if (cnt > 0 && cnt < 2)
			vec.x += 1.0f;
		m_pTerrain->callThread(vec);
		cnt++;
		
	}
}

void cGameScene::Render()
{
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	g_pTimeManager->DrawFPS();
	m_pGrid->Render();

// >> temp Light Off
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pObjUnit->Render();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
// <<
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	if (m_pTerrain)
		m_pTerrain->Render();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
