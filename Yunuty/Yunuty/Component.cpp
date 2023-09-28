#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

using namespace YunutyEngine;
YunutyEngine::GameObject* YunutyEngine::Component::GetGameObject()
{
    return gameObject;
}
Transform* YunutyEngine::Component::GetTransform()
{
    return gameObject->GetTransform();
}
