#include <iostream>
#include "../Yunuty/Yunuty/YunutyEngine.h"
#include "../Yunuty/Yunuty/YunutyEngineConsole.h"
//using namespace std;
using namespace YunutyEngine;

#ifndef 갸아악구와아악
class Factory : public Component
{
protected:
    double kimchi = 0;
    double kps = 10;
    virtual void Update()override;
};
void Factory::Update()
{
    kimchi += kps * Time::GetDeltaTime();
    //cout << "김치의 갯수 : " << kimchi << endl;
}
#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

vector<string> print_box(int row, int col, int x_pos, int y_pos)
{
    vector<string> mat(row, string(col, ' '));
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            if ((i == 0 || i == col - 1) || (j == 0 || j == row - 1))
            {
                //printf("■");
                mat[i][j] = '*';
            }
            else
            {
                //printf("  ");
                mat[i][j] = ' ';
            }
        }
        y_pos++;
        //gotoxy(x_pos, y_pos);
    }
    return mat;
}


Transform* trs;

int main()
{
    Scene scene;
    YunutyEngine::YunutyCycle::GetInstance().Initialize();
    YunutyEngine::YunutyCycle::GetInstance().Initialize();
    YunutyEngine::YunutyCycle::GetInstance().Play();

    Scene::LoadScene(&scene);
    GameObject* a = scene.AddGameObject("text");
    GameObject* cam = scene.AddGameObject("camera");
    trs = a->GetTransform();

    auto camComp = cam->AddComponent<Console::ConsoleCamera>();
    //a->AddComponent<Factory>();
    camComp->SetSpaceHeight(80);
    camComp->SetSpaceWidth(280);
    auto mat = a->AddComponent<Console::MatrixCustomImage>();
    //vector<vector<char>> matStr("asqwde","Asd");
    auto str = print_box(10, 10, 0, 0);
    mat->SetMatrixStrings(str);


    mat->GetGameObject()->GetTransform()->position.x -= 50;
    mat->GetGameObject()->GetTransform()->position.y -= 10;

    //mat->SetMatrixString("asdqq\nweqsa");

    while (true);
    std::cout << "Hello World2!\n";
}
#endif

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
