#pragma once
#include "IScene.h"
class GamePlayScene :
    public IScene
{
public:
    void Load();
    void Init();
    void Update();
    void Draw();

private:

};

