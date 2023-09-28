#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>
#include <functional>
#include <queue>
#include "SoundPlayer.h"
#include "ISelectable.h"

using namespace YunutyEngine::Console;

class UpgradeQueue;
class TextImage;
class SaveFile;

class Upgrade
    //: YunutyEngine::Component,public ISelectable
{
private:
protected:
public:
    static map<string, Upgrade*> upgrades;
    static vector<Upgrade*> upgradesDone;
    static vector<Upgrade*> upgradesLeft;
    //static bool Compare(const Upgrade& lhs,const Upgrade& rhs);
    static bool Compare(Upgrade* lhs, Upgrade* rhs);
    Upgrade(string name);

    string name;
    string description;
    string description_effect;
    string imageFileName;
    function<void()> upgradeEffect = []() {};
    double upgradeCost = 0;

    SoundType upgradeSound = SoundType::NoSound;

    void Buy(bool load = false);

    friend UpgradeQueue;
    friend SaveFile;
};
