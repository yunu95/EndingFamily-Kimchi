#include "Selector.h"

using namespace YunutyEngine::Console;
using namespace YunutyEngine;

void Selector::Start()
{
    if (defaultIndex < candidates.size())
        Highlight(candidates[defaultIndex]);
}
void Selector::Highlight(ISelectable* target)
{
    if (!target->GetEnabled())
        return;

    for (int i = 0; i < candidates.size(); i++)
    {
        candidates[i]->Dehightlight();
    }
    target->Highlight();
    highlighted = target;
}
void Selector::Select(ISelectable* target)
{
    if (!target->GetEnabled())
        return;

    target->Select();
}
ISelectable* Selector::GetHighlighted()
{
    return highlighted;
}
