#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>

// author : Á¾È­
class TextImage :
	public YunutyEngine::Console::MatrixImage
{
public:
	void SetText(int width, int height, string text);
	void SetText( string text);
};