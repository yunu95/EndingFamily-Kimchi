#pragma once
#include <thread>
#include "Object.h"
#include <functional>

using namespace std;

namespace YunutyEngine
{
    class Component;
    static class YunutyCycle : Object
    {
    private:
        thread updateThread;
        bool isGameRunning=false;
        static YunutyCycle* _instance;
        YunutyCycle() {}
        void ActiveComponentsDo(function<void(Component*)> todo);
        static void UpdateComponent(Component* component);
        static void StartComponent(Component* component);
    public:
        static YunutyCycle& GetInstance();
        void Initialize();
        void Play();
        void Stop();
        void Pause();
        void SetMaxFrameRate();
        void ThreadFunction();
        bool IsGameRunning();
    };
}
