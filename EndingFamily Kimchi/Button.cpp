#include "Button.h"

void Button::Highlight()
{
    onHighlight();
    for (auto each : highlightGameObjects)
        each->SetSelfActive(true);

    SoundPlayer::Play(highlightSound != SoundType::NoSound ? highlightSound : sound);
}
void Button::Dehightlight()
{
    onDehighlight();
    for (auto each : highlightGameObjects)
        each->SetSelfActive(false);
}
void Button::Select()
{
    onSelect();
    SoundPlayer::Play(selectSound != SoundType::NoSound ? selectSound : sound);
}
void Button::SetEnabled(bool enabled)
{
    this->enabled = enabled;
}
bool Button::GetEnabled()
{
    return this->enabled;
}