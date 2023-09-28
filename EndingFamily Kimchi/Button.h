#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>
#include "ISelectable.h"
#include "SoundPlayer.h"
#include <functional>
using namespace YunutyEngine;
// author : ±èÇöÀç
class Button :
    public YunutyEngine::Component, public ISelectable
{
private:
    bool enabled=true;
public:
    vector<GameObject*> highlightGameObjects;
    std::function<void()> onSelect = []() {};
    std::function<void()> onHighlight = []() {};
    std::function<void()> onDehighlight = []() {};
    SoundType sound = SoundType::NoSound;
    SoundType highlightSound = SoundType::NoSound;
    SoundType selectSound = SoundType::NoSound;

    virtual void Highlight() override;
    virtual void Dehightlight() override;
    virtual void Select() override;
    virtual void SetEnabled(bool enabled)override;
    virtual bool GetEnabled()override;
};
