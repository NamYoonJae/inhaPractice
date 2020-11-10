#include "stdafx.h"
#include "Camera.h"
#include "Grid.h"
#include "TimerManager.h"
#include "FontManager.h"
#include "ObjObject.h"
#include "GameScene.h"
#include "Observer.h"
#include "cTerrain.h"
#include "Button.h"

cGameScene::cGameScene(string name)
	:cScene(name)
	,m_pGrid(nullptr)
	,m_pObjUnit(nullptr)
	,m_pTerrain(nullptr)
	,m_p_jsonObj(nullptr)
	,m_p_jsonValue(nullptr)
	,m_p_jsonObjUnit(nullptr)
{
}


cGameScene::~cGameScene()
{
	SafeDelete(m_pMainCamera);
	SafeDelete(m_pGrid);
}

void cGameScene::Setup()
{	
	m_pMainCamera = new cCamera;
	m_pMainCamera->Setup(NULL);
	EventManager->Attach(m_pMainCamera);

	m_pGrid = new cGrid;
	m_pGrid->Setup();



	m_pPopup = new cPopUp;
	m_pPopup->Setup("UI", "panel-info.png", D3DXVECTOR3(100,100,0));

	m_pButton = new cButton;
	m_pButton->Setup("UI", "btn-med-up.png", D3DXVECTOR3(100,100,0), 0, 0, 0);
	m_pPopup->cButtonPushBack(m_pButton);

	m_pButton2 = new cButton;
	m_pButton2->Setup("UI", "btn-med-up.png", D3DXVECTOR3(100, 100, 0), 100, 100, 0);
	m_pPopup->cButtonPushBack(m_pButton2);

	EventManager->Attach(m_pPopup);

#pragma region jsonfileload
	// json에서 파일, 값을 불러와 렌더하는 테스트 코드니까 삭제해도 됩니다.
	m_p_jsonValue = json_parse_file("data/json/example box test.json");
	m_p_jsonObj = json_value_get_object(m_p_jsonValue);

	m_p_jsonObjUnit = new cObjMesh;
	m_p_jsonObjUnit->Setup(
		json_multi_object_get_pChar(m_p_jsonObj, "Box/FileDirectory"),
		json_multi_object_get_pChar(m_p_jsonObj, "Box/FileName")
	);
	m_p_jsonObjUnit->SetPosition(
		json_get_D3DXVECTOR3(m_p_jsonObj, "Box/Pos_x", "Box/Pos_y", "Box/Pos_z")
	);
	m_p_jsonObjUnit->SetScale(D3DXVECTOR3(0.3f, 0.3f, 0.3f));
#pragma endregion jsonfileload
	
	m_pObjUnit = new cObjMesh;
	m_pObjUnit->Setup("data/ObjFile", "SampleRoom.obj");
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
	if (m_pMainCamera)
		m_pMainCamera->Update();

	if (m_pTerrain)
	{
		static D3DXVECTOR3 vec{ 0,0,0 };
		static DWORD Elapsed = GetTickCount();
		if (GetTickCount() - Elapsed > 1000.0f)
		{
			Elapsed = GetTickCount();
			vec.x = rand() % 150;
			vec.z = rand() % 150;
		}
		m_pTerrain->callThread(vec);
	}

}

void cGameScene::Render()
{
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	g_pTimeManager->DrawFPS();
	m_pGrid->Render();

	if(m_pPopup)
		m_pPopup->Render();


#pragma region Light Off
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_p_jsonObjUnit->Render();
	m_pObjUnit->Render();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
#pragma endregion Light Off
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	if (m_pTerrain)
		m_pTerrain->Render();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
