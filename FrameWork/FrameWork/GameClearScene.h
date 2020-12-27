#pragma once
#include "Scene.h"

class Popup;

class cGameClearScene :
    public cScene
{

public:
    cGameClearScene(SceneType);
    ~cGameClearScene();

    void Setup() override;
    void Reset(int sceneType) override;

};

