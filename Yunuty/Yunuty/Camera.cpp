#include "Camera.h"
using namespace YunutyEngine;
Camera* YunutyEngine::Camera::mainCamera = nullptr;
YunutyEngine::Camera::Camera()
{
    if (mainCamera == nullptr)
        mainCamera = this;
}
void YunutyEngine::Camera::SetCameraMain()
{
    mainCamera = this;
}
Camera* YunutyEngine::Camera::GetMainCamera()
{
    return mainCamera;
}
