#include "AnimatedImage.h"
#include "GlobalFunctions.h"
using namespace YunutyEngine;
using namespace YunutyEngine::Console;

void AnimatedImage::Update()
{
    // �����Ӱ� �ð������� �޾ƿ� �� �ִ� �Լ�
    Time::GetDeltaTime();
    // ������ �ð��� 0.1�ʸ� ������, ������ �ð��� �ʱ�ȭ�ϰ�, ���� �̹����� �ҷ��´�.
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