#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>
#include "Selector.h"


using namespace YunutyEngine;

class TextImage;

class SaveFile
{
private:
    SaveFile() {}
    double kimchis = 0;
    int facilityNums[100] = { 0 };
    char completedUpgrades[100][40] = { 0 };
public:
    static void Save();
    static void Load();
};
