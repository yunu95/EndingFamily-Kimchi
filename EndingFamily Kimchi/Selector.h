#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>
#include "ISelectable.h"
#include <vector>

// author : ±èÇöÀç
class Selector :
    public YunutyEngine::Component
{
protected:
    ISelectable* highlighted = nullptr;
public:
    virtual void Start() override;
    virtual void Highlight(ISelectable*);
    virtual void Select(ISelectable*);
    int defaultIndex = 0;
    Selector() {}
    vector<ISelectable*> candidates;
    ISelectable* GetHighlighted();
};
