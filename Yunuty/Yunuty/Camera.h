#pragma once
#include "Object.h"
#include "Component.h"

namespace YunutyEngine
{
    class YunutyCycle;
    class Camera :
        public Component
    {
    private:
        static Camera* mainCamera;
        virtual void Render() = 0;
    public:
        Camera();
        void SetCameraMain();
        static Camera* GetMainCamera();
        friend YunutyCycle;
    };
}
