#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>

// author : ��ȭ
class BoxImage :
    public YunutyEngine::Console::MatrixImage
{
public:
    void SetBoxImage(int width, int height, char outline);
};
