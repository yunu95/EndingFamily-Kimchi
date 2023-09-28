#pragma once
#include "Object.h"
#include <chrono>

using namespace std;
namespace YunutyEngine
{
    static class Time :
        public Object
    {
        friend class YunutyCycle;
    private:
        static chrono::system_clock::time_point lastFrameTime;
        static double timeScale;
        static double deltaTimeUnscaled;
        static void Update();
    public:
        static void SetTimeScale(const float& timeScale);
        static double GetTimeScale();
        static double GetDeltaTime();
        static double GetDeltaTimeUnscaled();
    };
}
