#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>
#include "ISelectable.h"
#include "SoundPlayer.h"
#include "Facility.h"
#include <functional>
#include "Button.h"

using namespace YunutyEngine;
using namespace std;

class FacilityUnlock : public Component
{
protected:
    void Start() override;
    void Update() override;
public:
    const int rangeFactor = 5;
    const int rangeConstant = 50;
    vector<Facility*> Facilities;
    map<Facility*, Button*> buttons;
    map<Facility*, TextImage*> buttonTexts;
};

