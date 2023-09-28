#pragma once
#include <iostream>
#include <vector>

using namespace std;
namespace YunutyEngine
{
    class GameObject;
    class Scene;

    class IGameObjectParent
    {
    private:
        virtual remove_reference<unique_ptr<GameObject>>::type&& MoveChild(GameObject* child)=0;
        virtual void ReceiveChild(remove_reference<unique_ptr<GameObject>>::type&& child)=0;
        virtual int GetChildIndex(GameObject* child)=0;
    public:
        virtual vector<GameObject*> GetChildren()=0;
        friend GameObject;
        friend Scene;
    };
}
