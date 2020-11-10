#pragma once
#include "Scene.h"

class cGrid;
class cPopUp;
class cButton;
class cObjMesh;
class cTerrain;

class cCharater;

class cGameScene : public cScene
{
private:
	cGrid* m_pGrid;
	cPopUp* m_pPopup;
	cButton* m_pButton;
	cButton* m_pButton2;

	
	cObjMesh* m_pObjUnit;
	cTerrain* m_pTerrain;

	//
	cCharater*	m_pCharater;
public:
	cGameScene(string name);
	~cGameScene();

	void Setup() override;
	void CheckInput() override;
	void Update() override;
	void Render() override;
};

