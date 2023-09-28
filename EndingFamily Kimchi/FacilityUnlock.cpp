#include "FacilityUnlock.h"
#include "GameInfo.h"
#include "TextImage.h"


void FacilityUnlock::Start()
{
    for (auto each : buttons)
        each.second->SetEnabled(false);

    for (auto each : buttonTexts)
        each.second->SetText("???");
}
void FacilityUnlock::Update()
{
    for (auto each : Facilities)
    {
        if (GameInfo::kimchis * rangeFactor + rangeConstant > each->GetPrice())
        {
            if (!buttons[each]->GetEnabled())
            {
                buttons[each]->SetEnabled(true);
                buttonTexts[each]->SetText(each->GetName());
            }
        }
    }
}
