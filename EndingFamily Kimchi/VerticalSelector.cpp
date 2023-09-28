#include "VerticalSelector.h"

using namespace YunutyEngine::Console;
using namespace YunutyEngine;
void VerticalSelector::OnEnable()
{
    skipOneUpdate = true;
}
void VerticalSelector::Update()
{
    int nextIndex = selectableIndex;
    if (Input::isKeyPushed(KeyCode::DownArrow))
        nextIndex++;
    if (Input::isKeyPushed(KeyCode::UpArrow))
        nextIndex--;

    if (!skipOneUpdate)
    {
        if (Input::isKeyPushed(KeyCode::Space))
            Select(candidates[selectableIndex]);
    }
    else
        skipOneUpdate = false;

    if (nextIndex != selectableIndex)
        if (0 <= nextIndex && nextIndex < candidates.size()&&candidates[nextIndex]->GetEnabled())
            Highlight(candidates[nextIndex]);
        else
            nextIndex = selectableIndex;

    selectableIndex = nextIndex;
}
void VerticalSelector::Start()
{
    Selector::Start();
}