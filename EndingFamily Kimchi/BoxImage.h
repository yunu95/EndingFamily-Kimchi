#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>

// author : Á¾È­
class BoxImage :
    public YunutyEngine::Console::MatrixImage
{
public:
    void SetBoxImage(int width, int height, char outline);
};
