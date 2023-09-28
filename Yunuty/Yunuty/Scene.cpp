#include "Scene.h"
#include "GameObject.h"

using namespace YunutyEngine;
YunutyEngine::Scene* YunutyEngine::Scene::currentScene = nullptr;
YunutyEngine::Scene* YunutyEngine::Scene::getCurrentScene()
{
    return currentScene;
}
void YunutyEngine::Scene::LoadScene(Scene* scene)
{
    currentScene = scene;
}
string YunutyEngine::Scene::getName()const
{
    return name;
}
void YunutyEngine::Scene::setName(const string& name)
{
    this->name = name;
}
YunutyEngine::GameObject* YunutyEngine::Scene::AddGameObject(IGameObjectParent* parent)
{
    auto gameObject = new GameObject();
    gameObject->scene = this;
    gameObject->SetParent(parent!=nullptr?parent:this);
    /*if (!parent)
        gameObjects.insert(make_pair<gameObject, unique_ptr<GameObject>(gameObject));*/

    return gameObject;
}
YunutyEngine::GameObject* YunutyEngine::Scene::AddGameObject(string name,IGameObjectParent* parent)
{
    auto gameObject = AddGameObject(parent);
    gameObject->name = name;
    return gameObject;
}
remove_reference<unique_ptr<YunutyEngine::GameObject>>::type&& YunutyEngine::Scene::MoveChild(GameObject* child)
{
    unique_ptr<YunutyEngine::GameObject> ret = move(children[child]);
    children.erase(child);
    return move(ret);
}

vector<YunutyEngine::GameObject*> YunutyEngine::Scene::GetChildren()
{
    return childrenIndexed;
}
void YunutyEngine::Scene::ReceiveChild(remove_reference<unique_ptr<GameObject>>::type&& child)
{
    auto ptr = child.get();
    children.insert(make_pair(ptr, unique_ptr<GameObject>()));
    children[ptr] = move(child);
    childIndexMap.insert(make_pair(ptr, childrenIndexed.size()));
    childrenIndexed.push_back(ptr);
}
int YunutyEngine::Scene::GetChildIndex(GameObject* child)
{
    return childIndexMap[child];
}
