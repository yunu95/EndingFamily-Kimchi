#pragma once
#include "Object.h"
//#include "GameObject.h"

namespace YunutyEngine
{
    class GameObject;
    class YunutyCycle;
    class Transform;
    class Component :
        public Object
    {
    private:
        GameObject* gameObject = nullptr;
        bool StartCalled = false;
    protected:
        Component() {}
        virtual void OnEnable() {};
        virtual void OnDisable() {};
        virtual void Start() {};
        virtual void Update() {};
        virtual void FixedUpdate() {};
    public:
        virtual ~Component() {}
        Transform* GetTransform();
        GameObject* GetGameObject();
        //template<typename ComponentType>
        //friend ComponentType* GameObject::AddComponent<ComponentType>();
        friend GameObject;
        friend YunutyCycle;
    };
}
