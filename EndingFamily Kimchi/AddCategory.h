#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>


using namespace YunutyEngine;

class Selector;
GameObject* AddCategory(GameObject* Mainbox, string str, Scene* scene, int x, int y, GameObject** nestedBox = nullptr, Selector* selector = nullptr);
GameObject* AddFlexibleCategory(GameObject* Mainbox, string str, Scene* scene, int a, int b, int x, int y, Selector* selector = nullptr, GameObject** p_nestedText = nullptr);