#pragma once
#include <fstream>
#include <vector>
using namespace std;

static string img_path = "./4_Resources/imgs/";

string File2String(const std::string& img);
string doubleToKimchi(double);
string doubleToKps(double);
vector<string> String2VectorMatrix(const string& imageString);