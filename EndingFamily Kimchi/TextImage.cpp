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
    // 텍스트 입력
    vector<string> mat(height, string(width, ' '));
    std::stringstream str(text);
    std::string segment;
    std::vector<std::string> seglist;
    std::vector<std::string> segLineList;


    while (std::getline(str, segment, ' '))     // test라는 string을 공백이 있을때마다 segment로 잘라줌
    {
        seglist.push_back(segment);              // seglist라는 배열에 segment들을 넣어줌
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
    segLineList.push_back("");                   // seglinelist라는 새로운 줄을 생성
    int currentLine = 0;                           // 현재 줄 수는 0
    for (int i = 0; i < seglist.size(); i++)     // seglist.size = 문장이 잘라진 갯수
    {
        if (seglist[i].size() > width)              // 잘라진 문장의 단어수가 사각형 너비보다 클 경우
            break;                               // 실행중지

        // 새롭게 만들어진 seglinelist[n]번의 사이즈와 seglist[i]와의 사이즈의 합이 사각형 너비보다 클 경우
        if ((segLineList[currentLine].size() + seglist[i].size() + 1) > width || seglist[i][0] == '\n')
        {
            segLineList.push_back("");           // seglinelist 새로운 줄 하나 더 생성
            currentLine++;                       // 현재 줄수 ++
        }
        if (seglist[i][0] == '\n')
            seglist[i] = seglist[i].substr(1);
        segLineList[currentLine] += seglist[i];  // 현재 줄에 잘라진 문자열 삽입
        segLineList[currentLine] += " ";         // 현재 줄에 스페이스바 삽입

    }

    // 텍스트 중앙에 뜨도록 해놓긴 함... 여기서 근데 실행하면 안보인다.. 
    //gotoxy(x, y);
    for (int i = 0; i < (currentLine + 1); i++)
    {
        for (int j = 0; j < segLineList[i].size(); j++)
            mat[((height - (currentLine)) / 2) + i][((width + 1 - segLineList[i].length()) / 2) + j] = segLineList[i][j];
    }
    SetMatrix(mat);
}