#include "TextImage.h"
#include <sstream>
#include <iostream>

void gotoxy(int x, int y)
{
    COORD pos{ x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void TextImage::SetText(string text)
{
    SetText(width, height, text);
}
void TextImage::SetText(int width, int height, string text)
{
    //gotoxy(x, y);
    imageMatrix = vector<vector<char>>(height, vector<char>(width, ' '));
    this->width = width;
    this->height = height;
    //const char* str = text.c_str();
    int w = width;
    int h = height;
    int length = text.size();
    // do things
    // �ؽ�Ʈ �Է�
    vector<string> mat(height, string(width, ' '));
    std::stringstream str(text);
    std::string segment;
    std::vector<std::string> seglist;
    std::vector<std::string> segLineList;


    while (std::getline(str, segment, ' '))     // test��� string�� ������ ���������� segment�� �߶���
    {
        seglist.push_back(segment);              // seglist��� �迭�� segment���� �־���
    }
    auto setlistTemp = seglist;
    seglist.clear();
    for (auto each : setlistTemp)
    {
        str = stringstream(each);
        bool newLine = false;
        while (std::getline(str, segment, '\n'))
        {
            seglist.push_back((newLine ? "\n" : "") + segment);
            newLine = true;
        }
    }
    segLineList.push_back("");                   // seglinelist��� ���ο� ���� ����
    int currentLine = 0;                           // ���� �� ���� 0
    for (int i = 0; i < seglist.size(); i++)     // seglist.size = ������ �߶��� ����
    {
        if (seglist[i].size() > width)              // �߶��� ������ �ܾ���� �簢�� �ʺ񺸴� Ŭ ���
            break;                               // ��������

        // ���Ӱ� ������� seglinelist[n]���� ������� seglist[i]���� �������� ���� �簢�� �ʺ񺸴� Ŭ ���
        if ((segLineList[currentLine].size() + seglist[i].size() + 1) > width || seglist[i][0] == '\n')
        {
            segLineList.push_back("");           // seglinelist ���ο� �� �ϳ� �� ����
            currentLine++;                       // ���� �ټ� ++
        }
        if (seglist[i][0] == '\n')
            seglist[i] = seglist[i].substr(1);
        segLineList[currentLine] += seglist[i];  // ���� �ٿ� �߶��� ���ڿ� ����
        segLineList[currentLine] += " ";         // ���� �ٿ� �����̽��� ����

    }

    // �ؽ�Ʈ �߾ӿ� �ߵ��� �س��� ��... ���⼭ �ٵ� �����ϸ� �Ⱥ��δ�.. 
    //gotoxy(x, y);
    for (int i = 0; i < (currentLine + 1); i++)
    {
        for (int j = 0; j < segLineList[i].size(); j++)
            mat[((height - (currentLine)) / 2) + i][((width + 1 - segLineList[i].length()) / 2) + j] = segLineList[i][j];
    }
    SetMatrix(mat);
}