#include "KimchiNumText.h"
#include "GlobalFunctions.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
void KimchiNumText::Update()
{
    stringstream sstream;
    sstream << "��ġ ���� : " << doubleToKimchi(GameInfo::kimchis) << endl<<endl << "Kps : " << doubleToKps(GameInfo::Getkps());
    SetText(width, height, sstream.str());
}

