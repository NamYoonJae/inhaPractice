#pragma once
#include "Scene.h"

class cGrid;
class cPopUp;
class cButton;
class cObjMesh;
class cTerrain;

class cCharater;
class SkyBox;

class cArthur;

class cGameScene : public cScene
{
private:
	cGrid* m_pGrid;
	cPopUp* m_pPopup;
	cButton* m_pButton;
	cButton* m_pButton2;

	JSON_Object* m_p_jsonRootObj;
	JSON_Object* m_p_jsonSubObj;
	JSON_Value* m_p_jsonValue;
	
	cObjMesh* m_p_jsonObjUnit;
	
	cObjMesh* m_pObjUnit;
	cTerrain* m_pTerrain;

	//
	cCharater*	m_pCharater;
	SkyBox*		m_pSkyBox;

// temp >>
	cArthur*	  m_pArthur;
// <<
public:
	cGameScene(string name);
	~cGameScene();

	void Setup() override;
	void CheckInput() override;
	void Update() override;
	void Render() override;
};

