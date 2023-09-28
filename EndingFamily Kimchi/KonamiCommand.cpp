#include "KonamiCommand.h"
#include "SoundPlayer.h"




void KonamiCommand::Update()
{
	KeyCode select = KeyCode::NoKey;

	if (Input::isKeyPushed(KeyCode::DownArrow))
		select = KeyCode::DownArrow;

	if (Input::isKeyPushed(KeyCode::UpArrow))
		select = KeyCode::UpArrow;

	if (Input::isKeyPushed(KeyCode::LeftArrow))
		select = KeyCode::LeftArrow;

	if (Input::isKeyPushed(KeyCode::RightArrow))
		select = KeyCode::RightArrow;

	if (Input::isKeyPushed(KeyCode::a))
		select = KeyCode::a;

	if (select == KeyCode::NoKey)
		return;

	if (hidden[hidden_index] == select)
	{
		hidden_index++;
		if (hidden_index == 8)
		{
			command_activated = true;
		}
	}
	else
	{
		hidden_index = 0;
	}

	if (command_activated)
	{
		Time::SetTimeScale(15);
		//해금 사운드 재생도 포함
		if (play_once == 1)
		{
			SoundPlayer::Play(active_sound);
			play_once++;
		}
	}
}