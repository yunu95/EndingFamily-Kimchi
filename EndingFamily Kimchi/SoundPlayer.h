#pragma once
#include <vector>
#include "fmod.hpp"
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <queue>
#include <map>

using namespace std;
using namespace FMOD;

enum class SoundType
{
    NoSound = 0, Hit, Cry, ButtonSound, Kimjang, Receiving, Answer_Halme, Answer_HiveMind, konami_sound,
    ZergResearchComplete, robotArm, Stimpack, RuuberGlove, Boyak, thief_original, thief_speedup, thief_stealth, thief_airport, 
    kimchiclub_crowd, kimchiclub_speedup, kimchiclub_adrenalin, grandma_original, grandma_archon_portrait, thief_stealth_portrait, kimchiclub_mumbling,
    farm_original, farm_hatchery_portrait, farm_tools, farm_fertilizer, farm_tree, 
    factory_original, factory_scv, factory_auto, factory_reactor,
    temple_original, temple_sacrifice, temple_dosa,
    mitotic_original, mitotic_warp, mitotic_psionic, mitotic_warpgate_portrait,
    spaceship_original, spaceship_upgrade, spaceship_portrait,
};

class SoundPlayer
{
private:
    thread soundPlayerThread;
    queue< FMOD::Sound*> soundQueue;
    map<SoundType, Sound*> soundTypeMap;
    FMOD::System* f_system = nullptr;
    Channel* f_channel_1[10];
    Channel* f_channel_2[10];
    FMOD_RESULT result;

    SoundPlayer();
    static SoundPlayer* instance;
    static SoundPlayer* GetInstance();
    void ThreadFunction();
public:

    static void Play(SoundType soundType);
};

