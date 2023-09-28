#include "GlobalFunctions.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;
const string numSuffix[] = { "","��","��","��","��","��","��","��","��","��","��","��","��","���ϻ�","�ƽ±�","����Ÿ","�Ұ�����","�������" };
string File2String(const std::string& img)
{
    string img_output;

    string img_file = img_path + img;
    ifstream input_img(img_file);

    img_output = string((istreambuf_iterator<char>(input_img)), istreambuf_iterator<char>());

    return img_output;
}

string doubleToKimchi(double numDouble)
{
    int unit = 0;
    stringstream sstream;
    if (numDouble >= 100000000)
        unit++;
    
    while (numDouble >= 100000000)
    {
        unit++;
        numDouble /= 10000;
    }

    if (unit > 0)
    {
        sstream << int(numDouble / 10000) << numSuffix[unit] << ' ';
        if (int(numDouble) % 10000 != 0)
            sstream << int(numDouble) % 10000 << numSuffix[unit - 1];
    }
    else
        sstream << int(numDouble);

    sstream << " ����";
    return sstream.str();
}
string doubleToKps(double numDouble)
{
    int unit = 0;
    stringstream sstream;
    if (numDouble >= 100000000)
        unit++;

    while (numDouble >= 100000000)
    {
        unit++;
        numDouble /= 10000;
    }

    if (unit > 0)
    {
        sstream << int(numDouble / 10000) << numSuffix[unit] << ' ';
        if (int(numDouble) % 10000 != 0)
            sstream << (int)(numDouble) % 10000 << numSuffix[unit - 1] ;
    }
    else
        if (numDouble < 1)
            sstream << int(numDouble) << "." << int(numDouble * 10) ;
        else
            sstream << int(numDouble);
    sstream << " ����";

    return sstream.str();
}
vector<string> String2VectorMatrix(const string& imageString)
{
    stringstream imgStream(imageString);
    string segment;
    vector<string> segments;
    while (getline(imgStream, segment, '\n'))
    {
        segments.push_back(segment);
    }
    return segments;
}