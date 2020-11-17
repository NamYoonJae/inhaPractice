#include "stdafx.h"
#include "Camera.h"
#include "Grid.h"
#include "TimerManager.h"
#include "FontManager.h"
#include "ObjObject.h"
#include "Observer.h"
#include "cTerrain.h"
#include "Button.h"
#include "cCharater.h"
#include "SkyBox.h"
#include "ButtonEvent.h"

// >>
#include "SkinnedMesh.h"
#include "SkinnedMeshManager.h"
#include "Arthur.h"
// <<

#include "GameScene.h"

cGameScene::cGameScene(string name)
	:cScene(name)
	,m_pGrid(nullptr)
	,m_pObjUnit(nullptr)
	,m_pTerrain(nullptr)
	,m_pCharater(nullptr)
	,m_p_jsonRootObj(nullptr)
	,m_p_jsonValue(nullptr)
	,m_p_jsonObjUnit(nullptr)
	,m_pSkyBox(nullptr)
	, m_pArthur(nullptr)
{
}


cGameScene::~cGameScene()
{
	json_value_free(m_p_jsonValue);
	
	SafeDelete(m_pMainCamera);
	SafeDelete(m_pGrid);
	
	SafeDelete(m_pArthur);
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
	m_pButton->EventProcess = BtnStartEvent;

	m_pButton2 = new cButton;
	m_pButton2->Setup("UI", "btn-med-up.png", D3DXVECTOR3(100, 100, 0), 100, 100, 0);
	m_pPopup->cButtonPushBack(m_pButton2);
	m_pButton2->EventProcess = BtnExitEvent;

	EventManager->Attach(m_pPopup);

#pragma region jsonfileload
	// json에서 파일, 값을 불러와 렌더하는 테스트 코드니까 삭제해도 됩니다.
	m_p_jsonValue = json_parse_file("data/json/example box test.json");
	m_p_jsonRootObj = json_value_get_object(m_p_jsonValue);

	m_p_jsonObjUnit = new cObjMesh;
	m_p_jsonObjUnit->Setup(
		json_Fuction::object_get_pChar(m_p_jsonRootObj, "Box/FileDirectory"),
		json_Fuction::object_get_pChar(m_p_jsonRootObj, "Box/FileName")
	);
	m_p_jsonObjUnit->SetPosition(
		json_Fuction::get_D3DXVECTOR3(m_p_jsonRootObj, "Box/Pos_x", "Box/Pos_y", "Box/Pos_z")
	);

	m_p_jsonSubObj = json_Fuction::object_get_object(m_p_jsonRootObj, "Box/");
	json_object_set_number(m_p_jsonSubObj, "Pos_x", m_p_jsonObjUnit->GetPosition().x - 5.f);
	json_object_set_number(m_p_jsonSubObj, "Pos_y", m_p_jsonObjUnit->GetPosition().y + 5.f);
	json_object_set_number(m_p_jsonSubObj, "Pos_z", m_p_jsonObjUnit->GetPosition().z - 3.f);
	json_serialize_to_file_pretty(m_p_jsonValue, "data/example box test save.json");
	
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

	
	if(m_pCharater == NULL)
	{
		m_pCharater = new cCharater;
		m_pCharater->Setup();
		//EventManager->Attach(m_pCharater);
	}

	if(m_pSkyBox == NULL)
	{
		m_pSkyBox = new SkyBox;
		m_pSkyBox->Setup("data/HeightMapData","skyhorizon.png");
		m_pSkyBox->SetPos(m_pMainCamera->GetEye());
	}

// >>
	m_pArthur = new cArthur;
	m_pArthur->Setup("data/XFile/Arthur", "arthur_passive01.X");
	//m_pArthur->Setup("data/XFile/Arthur", "arthur_run01.X");
	//m_pArthur->Setup("data/XFile/Arthur", "arthur_Attack01.X");
	m_pArthur->SetScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	m_pMainCamera->Setup(m_pArthur->GetPos());
// <<
}

void cGameScene::CheckInput()
{

}

void cGameScene::Update()
{
	SafeUpdate(m_pMainCamera);

	if(m_pArthur)
	{
		float y = m_pTerrain->getHeight(m_pArthur->GetPosition());
		D3DXVECTOR3 vec = m_pArthur->GetPosition();
		vec.y = y + 1.0f;
		m_pArthur->SetPostiion(vec);
	}

	if (m_pTerrain && m_pArthur)
	{
		m_pTerrain->callThread(m_pArthur->GetPosition());
	}

	SafeUpdate(m_pArthur);
}

void cGameScene::Render()
{
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	
#pragma region Light Off
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	SafeRender(m_pSkyBox);
	g_pTimeManager->DrawFPS();
	
	SafeRender(m_pGrid);
	//SafeRender(m_pPopup);
	//SafeRender(m_p_jsonObjUnit);
	//SafeRender(m_pObjUnit);
	SafeRender(m_pTerrain);
	//SafeRender(m_pCharater);
	
	SafeRender(m_pArthur);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
#pragma endregion Light Off
	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
