#pragma once
#include "Scene.h"

class cGrid;

class cGameScene : public cScene
{
private:
	cGrid* m_pGrid;
public:
	cGameScene(string name);
	~cGameScene();

	void Setup() override;
	void CheckInput() override;
	void Update() override;
	void Render() override;
};

