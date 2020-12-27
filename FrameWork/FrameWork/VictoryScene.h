#pragma once
#include "Scene.h"

class Popup;

class cVictoryScene :
    public cScene
{

    cVictoryScene(SceneType);
    ~cVictoryScene();

    void Setup() override;
    void Reset(int sceneType) override;
};

