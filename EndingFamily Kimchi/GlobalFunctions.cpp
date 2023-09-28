#include "GlobalFunctions.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;
const string numSuffix[] = { "","만","억","조","경","해","자","양","구","간","정","재","극","항하사","아승기","나유타","불가사의","무량대수" };
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

    sstream << " 포기";
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
    sstream << " 포기";

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