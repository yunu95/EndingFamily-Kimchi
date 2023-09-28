#pragma once
#include "IGameObjectParent.h"
#include <iostream>
#include "Object.h"
#include <unordered_map>
#include <unordered_set>

using namespace std;
namespace YunutyEngine
{
    class GameObject;
    class YunutyCycle;
    class Scene :
        public Object, public IGameObjectParent
    {
    private:
        string name;
        unordered_set<GameObject*> gameObjects;
        unordered_map<GameObject*, unique_ptr<GameObject>> children;
        vector<GameObject*> childrenIndexed;
        unordered_map<GameObject*, int> childIndexMap;
        static Scene* currentScene;
    protected:
        remove_reference<unique_ptr<GameObject>>::type&& MoveChild(GameObject* child) override;
        vector<GameObject*> GetChildren() override;
        void ReceiveChild(remove_reference<unique_ptr<GameObject>>::type&& child)override;
        int GetChildIndex(GameObject* child)override;
    public:
        static Scene* getCurrentScene();
        static void LoadScene(Scene* scene);
        string getName()const;
        void setName(const string& name);
        GameObject* AddGameObject(IGameObjectParent* parent = nullptr);
        GameObject* AddGameObject(string name, IGameObjectParent* parent = nullptr);
        friend YunutyCycle;
    };
}

