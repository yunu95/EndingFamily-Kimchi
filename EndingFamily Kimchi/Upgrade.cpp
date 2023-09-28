#include "Upgrade.h"
#include "TextImage.h"
#include "GlobalFunctions.h"
#include "GameInfo.h"

map<string, Upgrade*> Upgrade::upgrades;
vector<Upgrade*> Upgrade::upgradesDone;
vector<Upgrade*> Upgrade::upgradesLeft;

//bool Upgrade::Compare(const Upgrade& lhs, const Upgrade& rhs)
//{
//    return lhs.upgradeCost < rhs.upgradeCost;
//}
bool Upgrade::Compare(Upgrade* lhs, Upgrade* rhs)
{
    //return Compare(*lhs,*rhs);
    return lhs->upgradeCost < rhs->upgradeCost;
}
Upgrade::Upgrade(string name)
{
    this->name = name;
    upgradesLeft.push_back(this);
    upgrades[name] = this;
    //sort(upgradesLeft.begin(), upgradesLeft.end(), [](const Upgrade*& item1, const Upgrade*& item2) {return item1->upgradeCost > item2->upgradeCost; });
}
//void Upgrade::Apply(TextImage* description, MatrixCustomImage* image)
//{
//    description->SetText(this->description + "\n" + this->description_effect);
//    image->SetMatrixString(File2String(imageFileName));
//}
void Upgrade::Buy(bool load)
{
    if (GameInfo::kimchis > upgradeCost || load)
    {
        if (!load)
        {
            GameInfo::kimchis -= upgradeCost;
            SoundPlayer::Play(upgradeSound);
        }
        upgradeEffect();

        upgradesLeft.erase(find(upgradesLeft.begin(), upgradesLeft.end(), this));
        upgradesDone.push_back(this);
    }
}
