#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>
#include <io.h>
#include <algorithm>

// author : 
class AnimatedImage :
    public YunutyEngine::Console::MatrixImage
{
private:
    //typedef vector<string> Image;
    vector<string> sprites;
    int spriteIndex=0;
    float timePassed=0;
protected:
    void Update() override;
public:
    void SetSprites(const vector<string>& filePaths);
	void SetSprites(const string& fileFolderPath);
    void SetSprites();
    
};
