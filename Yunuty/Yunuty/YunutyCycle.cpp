#include <iostream>
#include <chrono>
#include <stack>
#include "YunutyCycle.h"
#include "Time.h"
#include "GameObject.h"
#include "Component.h"
#include "GlobalComponent.h"
#include "Scene.h"
#include "Camera.h"

using namespace YunutyEngine;

YunutyEngine::YunutyCycle* YunutyEngine::YunutyCycle::_instance = nullptr;
YunutyEngine::YunutyCycle& YunutyEngine::YunutyCycle::GetInstance()
{
    if (!_instance)
        _instance = new YunutyCycle();
    return *_instance;
}
void YunutyEngine::YunutyCycle::Initialize()
{
}

void YunutyEngine::YunutyCycle::Play()
{
    updateThread = thread(&YunutyCycle::ThreadFunction, this);
    ActiveComponentsDo(StartComponent);
}

void YunutyEngine::YunutyCycle::Stop()
{
}

void YunutyEngine::YunutyCycle::Pause()
{
}

void YunutyEngine::YunutyCycle::SetMaxFrameRate()
{
}

bool YunutyEngine::YunutyCycle::IsGameRunning()
{
    return isGameRunning;
}

void YunutyEngine::YunutyCycle::ThreadFunction()
{
    while (true)
    {
        Time::Update();

        for (auto i = GlobalComponent::globalComponents.begin(); i != GlobalComponent::globalComponents.end(); i++)
            i->second->Update();

        ActiveComponentsDo(UpdateComponent);
        if (Camera::mainCamera)
            Camera::mainCamera->Render();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void YunutyEngine::YunutyCycle::UpdateComponent(Component* component)
{
    if (!component->StartCalled)
    {
        component->StartCalled = true;
        component->Start();
    }
    component->Update();
}
void YunutyEngine::YunutyCycle::StartComponent(Component* component)
{
    component->StartCalled = true;
    component->Start();
}
void YunutyEngine::YunutyCycle::ActiveComponentsDo(function<void(Component*)> todo)
{
    YunutyEngine::IGameObjectParent* gameObjectParent = Scene::getCurrentScene();
    if (Scene::getCurrentScene())
    {
        stack<GameObject*> objectsStack;
        auto firstChildren = Scene::getCurrentScene()->GetChildren();
        for (auto each = firstChildren.rbegin(); each != firstChildren.rend(); each++)
            objectsStack.push(*each);

        while (!objectsStack.empty())
        {
            auto gameObject = objectsStack.top();
            objectsStack.pop();
            if (!gameObject->GetSelfActive())
                continue;

            for (auto each = gameObject->components.begin(); each != gameObject->components.end(); each++)
                todo(each->first);

            for (auto each = gameObject->children.begin(); each != gameObject->children.end(); each++)
                objectsStack.push(each->first);
        }
    }
}
