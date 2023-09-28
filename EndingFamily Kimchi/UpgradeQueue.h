#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>
#include "Selector.h"


using namespace YunutyEngine;

class TextImage;

class UpgradeQueue :
    public Component
{
private:
    UpgradeQueue* instance = nullptr;
protected:
    void OnEnable() override;
public:
    UpgradeQueue();
    UpgradeQueue* GetInstance();
    Selector* selector = nullptr;
    vector<GameObject*> buttons;
    vector<GameObject*> buttonNestedTexts;
    Console::MatrixCustomImage* upgradeImage = nullptr;
    TextImage* description = nullptr;
    TextImage* cost = nullptr;

    void UpdateButtons();
};

