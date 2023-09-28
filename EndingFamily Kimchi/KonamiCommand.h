#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>
#include "TextImage.h"
#include "GameInfo.h"
#include "SoundPlayer.h"
#include <conio.h>

using namespace YunutyEngine;
class KonamiCommand :
    public Component
{
private:
	KeyCode hidden[8] = { KeyCode::UpArrow, KeyCode::UpArrow, KeyCode::DownArrow, KeyCode::DownArrow, KeyCode::LeftArrow, KeyCode::RightArrow, KeyCode::LeftArrow, KeyCode::RightArrow };
	int hidden_index = 0;
	bool hidden_command = false;
	bool command_activated = false;
	int play_once = 1;
	SoundType active_sound = SoundType::konami_sound;

protected:
    void Update() override;
};

