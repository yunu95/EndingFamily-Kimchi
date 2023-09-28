#pragma once
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>
#include "SoundPlayer.h"

class AnimatedImage;
class FacilityText;
class SaveFile;
class TextImage;

class Facility : public YunutyEngine::Component
{
protected:
    static vector<Facility*> facilities;
    void Update() override;
    string name;
    double priceGrowthFactor = 1.35;
    double price;
public:
    Facility();
    bool isPerson = false;
    string GetName();
    string portraitFile;
    string description;
    void SetName(const string& name);
    void Buy();
    int facilityNum;
    double kps = 1;
    double kpsTotal();
    SoundType selectSound;
    SoundType buySound;
    SoundType buyFailSound;
    double GetPrice();
    void Apply(AnimatedImage* portrait, FacilityText* facilityText, TextImage* description);
    void Set(string name, string portraitFile, double price, double kps, bool isPerson = false);
    static double kpsGlobal();
    friend SaveFile;
};

