#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>

// author : ��ȭ
class TextImage :
	public YunutyEngine::Console::MatrixImage
{
public:
	void SetText(int width, int height, string text);
	void SetText( string text);
};