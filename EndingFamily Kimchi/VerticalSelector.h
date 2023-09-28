
#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>
#include "ISelectable.h"
#include "Selector.h"
#include <vector>

// author : ±èÇöÀç
class VerticalSelector :
    public Selector
{
protected:
    bool skipOneUpdate = true;
    virtual void OnEnable()override;
    virtual void Start()override;
    virtual void Update() override;
public:
    int selectableIndex = 0;
    VerticalSelector() {}
};
