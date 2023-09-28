#include "Facility.h"
#include "FacilityText.h"
#include "AnimatedImage.h"
#include "GameInfo.h"
#include <Yunuty/YunutyEngine.h>

vector<Facility*> Facility::facilities;
Facility::Facility()
{
    facilities.push_back(this);
}

void Facility::Update()
{
    GameInfo::kimchis += kpsTotal() * YunutyEngine::Time::GetDeltaTime();
}

string Facility::GetName()
{
    return name;
}

void Facility::SetName(const string& name)
{
    this->name = name;
}

void Facility::Buy()
{
    if (GameInfo::kimchis >= price)
    {
        GameInfo::kimchis -= price;
        price *= priceGrowthFactor;
        facilityNum++;
        SoundPlayer::Play(buySound);
    }
    else
        SoundPlayer::Play(buyFailSound);
}

double Facility::kpsTotal()
{
    return kps * facilityNum;
}
double Facility::kpsGlobal()
{
    double ret = 0;
    for (auto each : facilities)
        ret += each->kpsTotal();
    return ret;
}

void Facility::Apply(AnimatedImage* portrait, FacilityText* facilityText, TextImage* description)
{
    SoundPlayer::Play(selectSound);
    if (facilityText)
        facilityText->SetFacility(this);

    if (portrait)
        portrait->SetSprites(portraitFile);

    if (description)
        description->SetText(this->description);
}
double Facility::GetPrice()
{
    return price;
}
void Facility::Set(string name, string portraitFile, double price, double kps, bool isPerson)
{
    this->name = name;
    this->portraitFile = portraitFile;
    this->price = price;
    this->kps = kps;
    this->isPerson = isPerson;
}

