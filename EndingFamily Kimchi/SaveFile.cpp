#include "SaveFile.h"
#include <fstream>
#include <fileapi.h>
#include <iostream>
#include "GameInfo.h"
#include "Upgrade.h"
#include "Facility.h"

using namespace std;

void SaveFile::Save()
{
    auto file = new SaveFile();
    
    ofstream fstream("yourGreedyLife.life");

    file->kimchis = GameInfo::kimchis;
    auto facItr = Facility::facilities.begin();
    for (int i = 0; i < 100; i++)
    {
        if (facItr == Facility::facilities.end())
            break;
        file->facilityNums[i] = (*facItr)->facilityNum;
        facItr++;
    }


    auto upgItr = Upgrade::upgradesDone.begin();
    for (int i = 0; i < 100; i++)
    {
        if (upgItr == Upgrade::upgradesDone.end())
            break;
        memcpy(file->completedUpgrades[i], (*upgItr)->name.c_str(), 40);
        upgItr++;
    }
    fstream.write((char*)file, sizeof(SaveFile));
    fstream.close();
    delete file;
}

void SaveFile::Load()
{
    auto file = new SaveFile();
    ifstream fstream;
    fstream.open("yourGreedyLife.life", ios::in);
    fstream.read((char*)file, sizeof(SaveFile));

    GameInfo::kimchis = file->kimchis;

    auto facItr = Facility::facilities.begin();
    for (int i = 0; i < 100; i++)
    {
        if (facItr == Facility::facilities.end())
            break;
        (*facItr)->facilityNum = file->facilityNums[i];
        (*facItr)->price *=pow((*facItr)->priceGrowthFactor,(*facItr)->facilityNum);
        facItr++;
    }


    auto upgItr = Upgrade::upgrades.begin();
    for (int i = 0; i < 100; i++)
    {
        if (file->completedUpgrades[i][0] == '\0')
            break;
        Upgrade::upgrades[string(file->completedUpgrades[i])]->Buy(true);
        upgItr++;
    }
    fstream.close();
    delete file;
}
