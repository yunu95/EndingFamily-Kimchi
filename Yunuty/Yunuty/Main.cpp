// Yunuty.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "YunutyCycle.h"
#include "Transform.h"
#include "RectTransform.h"
#include "GameObject.h"
#include "Scene.h"

using namespace std;
using namespace YunutyEngine;
int main()
{
    Scene scene0;
    scene0.setName("default");
    GameObject* c=scene0.AddGameObject();
    auto trs= c->AddComponent<RectTransform>();
    trs->SetAnchoredPosition(Vector2d(1,2));

    Scene::LoadScene(&scene0);

    YunutyCycle::GetInstance().Initialize();
    YunutyCycle::GetInstance().Play();
    while (true);
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
