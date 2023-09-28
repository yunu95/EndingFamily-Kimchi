#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include <stack>

using namespace YunutyEngine;
using namespace std;
YunutyEngine::GameObject::GameObject()
{
    transform = AddComponent<Transform>();
}
void YunutyEngine::GameObject::DeleteComponent(Component* component)
{
    components.erase(component);
}
bool YunutyEngine::GameObject::GetActive()
{
    if (!selfActive)
        return false;
    if (parentGameObject)
        return parentGameObject->GetActive();
    else
        return true;
}
bool YunutyEngine::GameObject::GetSelfActive()
{
    return selfActive;
}
void YunutyEngine::GameObject::SetSelfActive(bool selfActive)
{
    bool activeBefore = GetActive();
    bool activeAfter;

    this->selfActive = selfActive;

    activeAfter = GetActive();
    if (activeBefore != activeAfter)
    {
        if (activeAfter)
        {
            stack<GameObject*> activeStack;
            activeStack.push(this);
            while (!activeStack.empty())
            {
                auto child = activeStack.top();
                activeStack.pop();
                for (auto each : child->childrenIndexed)
                    if (each->selfActive)
                        activeStack.push(each);

                for (auto eachComp = child->components.begin(); eachComp != child->components.end(); eachComp++)
                    if (activeAfter)
                        eachComp->first->OnEnable();
                    else
                        eachComp->first->OnDisable();
            }
        }
    }

}
GameObject* YunutyEngine::GameObject::GetParentGameObject()
{
    return parentGameObject;
}
void YunutyEngine::GameObject::SetParent(IGameObjectParent* parent)
{
    if (this->parent)
        parent->ReceiveChild(this->parent->MoveChild(this));
    else
        parent->ReceiveChild(move(unique_ptr<GameObject>(this)));
    this->parent = parent;
    this->parentGameObject = dynamic_cast<GameObject*>(parent);
}
remove_reference<unique_ptr<YunutyEngine::GameObject>>::type&& YunutyEngine::GameObject::MoveChild(GameObject* child)
{
    unique_ptr<YunutyEngine::GameObject> ret = move(children[child]);
    children.erase(child);
    return move(ret);
}

vector<YunutyEngine::GameObject*> YunutyEngine::GameObject::GetChildren()
{
    return childrenIndexed;
}
void YunutyEngine::GameObject::ReceiveChild(remove_reference<unique_ptr<GameObject>>::type&& child)
{
    auto ptr = child.get();
    children.insert(make_pair(ptr, unique_ptr<GameObject>()));
    children[ptr] = move(child);
    childIndexMap.insert(make_pair(ptr, childrenIndexed.size()));
    childrenIndexed.push_back(ptr);
}
int YunutyEngine::GameObject::GetChildIndex(GameObject* child)
{
    return childIndexMap[child];
}
YunutyEngine::GameObject::~GameObject()
{
}
Transform* YunutyEngine::GameObject::GetTransform()
{
    return transform;
}
int YunutyEngine::GameObject::GetChildIndex()
{
    return parent->GetChildIndex(this);
}
int YunutyEngine::GameObject::GetSceneIndex()
{
    return (parentGameObject ? parentGameObject->GetSceneIndex() : -1) + 1 + GetChildIndex();
}
