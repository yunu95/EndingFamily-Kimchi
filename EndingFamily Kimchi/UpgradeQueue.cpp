#include "UpgradeQueue.h"
#include "Upgrade.h"
#include "Button.h"
#include "GlobalFunctions.h"
#include "TextImage.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace YunutyEngine;
using namespace YunutyEngine::Console;

void UpgradeQueue::OnEnable()
{
    UpdateButtons();
}
void UpgradeQueue::UpdateButtons()
{
    auto buttonItr = buttons.begin();
    auto buttonTextItr = buttonNestedTexts.begin();
    auto upgradeItr = Upgrade::upgradesLeft.begin();
    auto upgradeEndItr = Upgrade::upgradesLeft.end();
    for (auto i = 0; i < buttons.size(); i++)
    {
        if (upgradeItr == Upgrade::upgradesLeft.end())
        {
            (*buttonItr)->GetComponent<Button>()->SetEnabled(false);
            (*buttonTextItr)->GetComponent<TextImage>()->SetText("");
            buttonItr++;
            continue;
        }

        (*buttonTextItr)->GetComponent<TextImage>()->SetText((*upgradeItr)->name);
        (*buttonItr)->GetComponent<Button>()->SetEnabled(true);
        (*buttonItr)->GetComponent<Button>()->onHighlight =
            [upgradeItr, upgradeEndItr, this]()
        {
            stringstream desc;

            desc << (*upgradeItr)->description << endl << endl << (*upgradeItr)->description_effect;
            upgradeImage->SetMatrixString(File2String((*upgradeItr)->imageFileName));
            description->SetText(desc.str());
            desc.str("");
            desc <<"ºñ¿ë : " << doubleToKimchi((*upgradeItr)->upgradeCost);
            cost->SetText(desc.str());
        };
        (*buttonItr)->GetComponent<Button>()->onSelect =
            [upgradeItr, upgradeEndItr, this]()
        {
            (*upgradeItr)->Buy();
            this->UpdateButtons();
        };

        buttonItr++;
        buttonTextItr++;
        if (upgradeItr != Upgrade::upgradesLeft.end())
            upgradeItr++;
    }
    if (selector->GetHighlighted())
        selector->Highlight(selector->GetHighlighted());
}
UpgradeQueue::UpgradeQueue()
{
    if (!instance)
        instance = this;
}
UpgradeQueue* UpgradeQueue::GetInstance()
{
    return instance;
}
