#include "AnimatedImage.h"
#include "GlobalFunctions.h"
using namespace YunutyEngine;
using namespace YunutyEngine::Console;

void AnimatedImage::Update()
{
    // 프레임간 시간간격을 받아올 수 있는 함수
    Time::GetDeltaTime();
    // 축적된 시간이 0.1초를 넘으면, 축적된 시간을 초기화하고, 다음 이미지를 불러온다.
    //if ()
    //{
        // do things
    //}
    if (!sprites.empty())
    {
        timePassed += Time::GetDeltaTimeUnscaled();
        if (timePassed > 0.1)
        {
            SetMatrix(sprites[spriteIndex++]);
            spriteIndex %= sprites.size();
            timePassed -= 0.1;
        }
    }
}
void AnimatedImage::SetSprites(const vector<string>& filePaths)
{
    sprites.clear();
    for (string filepath : filePaths)
    {
        sprites.push_back(File2String(filepath));
    }
    spriteIndex = 0;
}
void AnimatedImage::SetSprites(const string& fileFolderPath)
{
    vector<string> filePaths;

    string full_path = img_path + fileFolderPath + "/*.*";

    struct _finddata_t fd;
    intptr_t handle;

    handle = _findfirst(full_path.c_str(), &fd);

    if (handle == -1)
        return;
    do
    {
        if (*fd.name != '.' && *fd.name != '..')
        {
            filePaths.push_back(fileFolderPath + "/" + fd.name);
        }

    } while (_findnext(handle, &fd) == 0);

    sort(filePaths.begin(), filePaths.end());
    _findclose(handle);
    SetSprites(filePaths);
}
void AnimatedImage::SetSprites()
{

}