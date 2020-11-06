#pragma once
#include "Scene.h"

class cGrid;
class cPopUp;
class cButton;

class cGameScene : public cScene
{
private:
	cGrid* m_pGrid;
	cPopUp* m_pPopup;
	cButton* m_pButton;
	cButton* m_pButton2;

	
public:
	cGameScene(string name);
	~cGameScene();

	void Setup() override;
	void CheckInput() override;
	void Update() override;
	void Render() override;
};

