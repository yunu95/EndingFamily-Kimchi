#include "SoundPlayer.h"
#include <iostream>
#include <windows.h>
#include <filesystem>

SoundPlayer* SoundPlayer::instance = nullptr;
SoundPlayer::SoundPlayer()
{
    System_Create(&f_system);
    f_system->init(10, FMOD_INIT_NORMAL, NULL);
    string soundFolderPath = "./4_Resources/sound/";

    map<SoundType, string> soundFileMap;

    soundFileMap.insert(make_pair(SoundType::Cry, "sound1.wav"));
    soundFileMap.insert(make_pair(SoundType::Hit, "sound2.wav"));
    soundFileMap.insert(make_pair(SoundType::ButtonSound, "button.wav"));
    soundFileMap.insert(make_pair(SoundType::Kimjang, "kimjang1.wav"));
    soundFileMap.insert(make_pair(SoundType::Receiving, "receiving.wav"));
    soundFileMap.insert(make_pair(SoundType::konami_sound, "konami_sound.wav"));

    soundFileMap.insert(make_pair(SoundType::Answer_Halme, "grandma_boyak.wav"));
    soundFileMap.insert(make_pair(SoundType::Answer_HiveMind, "grandma_hivemind.wav"));
    soundFileMap.insert(make_pair(SoundType::ZergResearchComplete, "grandma_removeMind.wav"));
    soundFileMap.insert(make_pair(SoundType::robotArm, "grandma_roboArm.wav"));
    soundFileMap.insert(make_pair(SoundType::Stimpack, "grandma_stimpack.wav"));
    soundFileMap.insert(make_pair(SoundType::RuuberGlove, "grandma_rubberglove.wav"));
    soundFileMap.insert(make_pair(SoundType::Boyak, "grandma_boyak.wav"));
    soundFileMap.insert(make_pair(SoundType::grandma_original, "grandma_original.wav")); 
    soundFileMap.insert(make_pair(SoundType::grandma_archon_portrait, "grandma_archon_portrait.wav"));  //군체의식 업그레이드 이후 일러스트

    soundFileMap.insert(make_pair(SoundType::thief_original, "thief_original.wav"));  
    soundFileMap.insert(make_pair(SoundType::thief_stealth_portrait, "thief_stealth_portrait.wav"));    //은신 업그레이드 이후 일러스트
    soundFileMap.insert(make_pair(SoundType::thief_speedup, "thief_speedup.wav"));
	soundFileMap.insert(make_pair(SoundType::thief_stealth, "thief_stealth.wav"));
	soundFileMap.insert(make_pair(SoundType::thief_airport, "thief_airport.wav"));

    soundFileMap.insert(make_pair(SoundType::kimchiclub_mumbling, "kimchiclub_mumbling.wav"));          //김치부녀회 디폴트 일러스트
    soundFileMap.insert(make_pair(SoundType::kimchiclub_crowd, "kimchiclub_crowd.wav"));
	soundFileMap.insert(make_pair(SoundType::kimchiclub_speedup, "kimchiclub_speedup.wav"));
	soundFileMap.insert(make_pair(SoundType::kimchiclub_adrenalin, "kimchiclub_adrenalin.wav"));

	soundFileMap.insert(make_pair(SoundType::farm_original, "farm_original.wav"));     
    soundFileMap.insert(make_pair(SoundType::farm_hatchery_portrait, "farm_hatchery_portrait.wav"));    //비료 업그레이드 이후 일러스트
	soundFileMap.insert(make_pair(SoundType::farm_tools, "farm_tools.wav"));
	soundFileMap.insert(make_pair(SoundType::farm_fertilizer, "farm_fertilizer.wav"));
	soundFileMap.insert(make_pair(SoundType::farm_tree, "farm_tree.wav"));

	soundFileMap.insert(make_pair(SoundType::factory_original, "factory_original.wav"));   
	soundFileMap.insert(make_pair(SoundType::factory_scv, "factory_scv.wav"));
	soundFileMap.insert(make_pair(SoundType::factory_auto, "factory_auto.wav"));
	soundFileMap.insert(make_pair(SoundType::factory_reactor, "factory_reactor.wav"));

	soundFileMap.insert(make_pair(SoundType::temple_original, "temple_original.wav"));  
	soundFileMap.insert(make_pair(SoundType::temple_sacrifice, "temple_sacrifice.wav"));
	soundFileMap.insert(make_pair(SoundType::temple_dosa, "temple_dosa.wav"));

	soundFileMap.insert(make_pair(SoundType::mitotic_original, "mitotic_original.wav"));        //김치 가상분열기 기본 일러스트
	soundFileMap.insert(make_pair(SoundType::mitotic_warp, "mitotic_warp.wav"));
	soundFileMap.insert(make_pair(SoundType::mitotic_psionic, "mitotic_psionic.wav"));          
    soundFileMap.insert(make_pair(SoundType::mitotic_warpgate_portrait, "mitotic_warpgate_portrait.wav"));  //사이오닉 업그레이드 이후 일러스트

	soundFileMap.insert(make_pair(SoundType::spaceship_original, "spaceship_original.wav"));    //우주선 기본 일러스트
	soundFileMap.insert(make_pair(SoundType::spaceship_upgrade, "spaceship_upgrade.wav"));
	soundFileMap.insert(make_pair(SoundType::spaceship_portrait, "spaceship_portrait.wav"));    //반응로 업그레이드 이후

    /// <summary>
    ///  사운드 추가가 모두 끝난후 create 부분...
    /// </summary>

    srand(time(NULL));
    for (auto each : soundFileMap)
        soundTypeMap.insert(make_pair(each.first, nullptr));

    for (auto each : soundFileMap)
        f_system->createSound((soundFolderPath + each.second).c_str(), FMOD_LOOP_OFF, NULL, &soundTypeMap[each.first]);
    soundPlayerThread = thread(&SoundPlayer::ThreadFunction, this);

}

SoundPlayer* SoundPlayer::GetInstance()
{
    if (!instance)
        instance = new SoundPlayer();
    return instance;
}

void SoundPlayer::ThreadFunction()
{
    while (true)
    {
        result = f_system->update();

        while (!soundQueue.empty())
        {
			f_system->playSound(soundQueue.front(), NULL, 0, f_channel_1);
			while (1)
			{
				if (f_channel_1)
				{
					bool playing = false;
					result = f_channel_1[0]->isPlaying(&playing);
                    result = f_channel_1[1]->isPlaying(&playing);
                    result = f_channel_1[2]->isPlaying(&playing);
                    result = f_channel_1[3]->isPlaying(&playing);
                    result = f_channel_1[4]->isPlaying(&playing);
                    result = f_channel_1[5]->isPlaying(&playing);
                    result = f_channel_1[6]->isPlaying(&playing);
                    result = f_channel_1[7]->isPlaying(&playing);
                    result = f_channel_1[8]->isPlaying(&playing);
                    result = f_channel_1[9]->isPlaying(&playing);
					if (!playing) break;
				}
			}
            
			soundQueue.pop();
        }
        Sleep(40);
        
    }
}

void SoundPlayer::Play(SoundType soundType)
{
    GetInstance()->soundQueue.push(GetInstance()->soundTypeMap[soundType]);
}