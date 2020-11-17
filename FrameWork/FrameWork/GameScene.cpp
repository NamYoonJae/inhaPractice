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

//
#include "ObjectPool.h"

cGameScene::cGameScene(string name)
	:cScene(name)
{
}


cGameScene::~cGameScene()
{
}

void cGameScene::Setup() // boss1map  boss2map
{
	cGrid *pGrid = new cGrid;
	pGrid->Setup();

	ObjectManager->AddChild(pGrid);

	cPopUp *pPopup = new cPopUp;
	pPopup->Setup("UI", "panel-info.png", D3DXVECTOR3(100, 100, 0));

	cButton *pButton = new cButton;
	pButton->Setup("UI", "btn-med-up.png", D3DXVECTOR3(100, 100, 0), 0, 0, 0);
	pPopup->cButtonPushBack(pButton);
	pButton->EventProcess = BtnStartEvent;

	cButton *pButton2 = new cButton;
	pButton2->Setup("UI", "btn-med-up.png", D3DXVECTOR3(100, 100, 0), 100, 100, 0);
	pPopup->cButtonPushBack(pButton2);
	pButton2->EventProcess = BtnExitEvent;
	EventManager->Attach(pPopup);

	ObjectManager->AddUIChild(pPopup);


	cTerrain* pTerrain = new cTerrain;
	pTerrain->Setup("data/HeightMapData", "terrain.jpg", "HeightMap.raw");
	pTerrain->Tagging(Tag::Tag_Map);
	
	cCharater* player = (cCharater*)ObjectManager->SearchChild(Tag::Tag_Player);

	pTerrain->GetTarget(player->GetPos());
	ObjectManager->AddChild(pTerrain);

	cCamera* Camera = (cCamera*)ObjectManager->SearchChild(Tag::Tag_Camera);

	cSkinnedMesh* m_pSkinnedUnit = new cSkinnedMesh();
	m_pSkinnedUnit->Setup("data/XFile/Dragon", "Basic Attack.X");
	m_pSkinnedUnit->SetAnimationIndex(0);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixScaling(&matWorld, 0.1f, 0.1f, 0.1f);
	m_pSkinnedUnit->SetTransform(&matWorld);

	ObjectManager->AddChild(m_pSkinnedUnit);

	cArthur* pArthur = new cArthur;
	pArthur->Setup("data/XFile/Arthur", "arthur_TBorn.X");
	pArthur->SetScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	Camera->Setup(pArthur->GetPos());
	
	ObjectManager->AddChild(pArthur);
	//	
	//#pragma region jsonfileload
	//	// json에서 파일, 값을 불러와 렌더하는 테스트 코드니까 삭제해도 됩니다.
	//	m_p_jsonValue = json_parse_file("data/json/example box test.json");
	//	m_p_jsonRootObj = json_value_get_object(m_p_jsonValue);
	//
	//	m_p_jsonObjUnit = new cObjMesh;
	//	m_p_jsonObjUnit->Setup(
	//		json_Fuction::object_get_pChar(m_p_jsonRootObj, "Box/FileDirectory"),
	//		json_Fuction::object_get_pChar(m_p_jsonRootObj, "Box/FileName")
	//	);
	//	m_p_jsonObjUnit->SetPosition(
	//		json_Fuction::get_D3DXVECTOR3(m_p_jsonRootObj, "Box/Pos_x", "Box/Pos_y", "Box/Pos_z")
	//	);
	//
	//	m_p_jsonSubObj = json_Fuction::object_get_object(m_p_jsonRootObj, "Box/");
	//	json_object_set_number(m_p_jsonSubObj, "Pos_x", m_p_jsonObjUnit->GetPosition().x - 5.f);
	//	json_object_set_number(m_p_jsonSubObj, "Pos_y", m_p_jsonObjUnit->GetPosition().y + 5.f);
	//	json_object_set_number(m_p_jsonSubObj, "Pos_z", m_p_jsonObjUnit->GetPosition().z - 3.f);
	//	json_serialize_to_file_pretty(m_p_jsonValue, "data/example box test save.json");
	//	
	//	m_p_jsonObjUnit->SetScale(D3DXVECTOR3(0.3f, 0.3f, 0.3f));
	//
	//#pragma endregion jsonfileload
}

void cGameScene::CheckInput()
{

}
