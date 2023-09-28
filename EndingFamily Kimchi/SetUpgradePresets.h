#pragma once
#include "Upgrade.h"

void AddUpgradePreset(string name, string description, string description_effect, string imageFileName, function<void()> upgradeEffect, double upgradeCost, SoundType upgradeSound = SoundType::NoSound)
{
    auto upgrade = new Upgrade(name);
    upgrade->upgradeEffect = upgradeEffect;
    upgrade->upgradeCost = upgradeCost;
    upgrade->description = description;
    upgrade->description_effect = description_effect;
    upgrade->imageFileName = imageFileName;
    upgrade->upgradeSound = upgradeSound;
}
//void SetAllUpgradePresets()
//{
//}
