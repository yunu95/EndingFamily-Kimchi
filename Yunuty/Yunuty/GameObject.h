#pragma once
#include <iostream>
#include "Object.h"
#include "IGameObjectParent.h"
#include <unordered_map>
//#include "Scene.h"
#include "Transform.h"

using namespace std;
namespace YunutyEngine
{
    class Scene;
    class Component;
    class Transform;
    class YunutyCycle;
    class GameObject :
        public Object, public IGameObjectParent
    {
    private:
        Scene* scene = nullptr;
        string name;
        bool selfActive = true;
        IGameObjectParent* parent = nullptr;
        GameObject* parentGameObject = nullptr;
        Transform* transform;
        unordered_map<GameObject*, unique_ptr<GameObject>> children;
        vector<GameObject*> childrenIndexed;
        unordered_map<GameObject*, int> childIndexMap;
        unordered_map<Component*, unique_ptr<Component>> components;
        GameObject();
    protected:
        remove_reference<unique_ptr<GameObject>>::type&& MoveChild(GameObject* child) override;
        vector<GameObject*> GetChildren() override;
        void ReceiveChild(remove_reference<unique_ptr<GameObject>>::type&& child) override;
        int GetChildIndex(GameObject* child) override;
    public:
        ~GameObject();
        Transform* GetTransform();
        template<typename ComponentType>
        ComponentType* AddComponent()
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "only derived classes from component are allowed");
            auto newComponent = new ComponentType();
            newComponent->gameObject = this;
            components.insert(make_pair(newComponent, unique_ptr<Component>(newComponent)));
            return newComponent;
        }
        template<typename ComponentType>
        ComponentType* GetComponent()
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "only derived classes from component are allowed");
            for (auto i = components.begin(); i != components.end(); i++)
            {
                auto castedPointer = dynamic_cast<ComponentType*>(i->first);
                if (castedPointer)
                    return castedPointer;;
            }
            return nullptr;
        }
        void DeleteComponent(Component* component);
        bool GetActive();
        bool GetSelfActive();
        void SetSelfActive(bool selfActive);
        GameObject* GetParentGameObject();
        void SetParent(IGameObjectParent* parent = nullptr);
        int GetChildIndex();
        int GetSceneIndex();

        friend Scene;
        friend YunutyCycle;
    };
}
