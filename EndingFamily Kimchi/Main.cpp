
#ifndef 갸아악구와아악
#include <iostream>
#include <vector>
#include <Yunuty/YunutyEngine.h>
#include <Yunuty/YunutyEngineConsole.h>
#include "BoxImage.h"
#include "TextImage.h"
#include "AddCategory.h"
#include "Selector.h"
#include "VerticalSelector.h"
#include "Button.h"
#include "AnimatedImage.h"
#include "ManualKimJang.h"
#include "KimchiNumText.h"
#include "Facility.h"
#include "FacilityText.h"
#include "GlobalFunctions.h"
#include "Upgrade.h"
#include "UpgradeQueue.h"
#include "SetUpgradePresets.h"
#include "SaveFile.h"
#include "NewsText.h"
#include "KonamiCommand.h"
#include "FacilityUnlock.h"
#include <map>

using namespace YunutyEngine;
using namespace YunutyEngine::Console;

bool endGame = false;

int main()
{
    Input::SetInput<Console::ConsoleInput>();
    Scene scene;
    YunutyEngine::YunutyCycle::GetInstance().Initialize();
    // 메인 씬 설정
    Scene::LoadScene(&scene);


    // 카메라 설정
    GameObject* cam = scene.AddGameObject("camera");
    Console::ConsoleCamera* camComp = cam->AddComponent<Console::ConsoleCamera>();
    //카메라 해상도설정
    camComp->SetSpaceHeight(60);
    camComp->SetSpaceWidth(250);


    typedef Button SelectableWindow;
    // 화면 선언
    GameObject* WS_ROOT = scene.AddGameObject();
    GameObject* WM_ROOT = scene.AddGameObject();
    GameObject* WF_ROOT = scene.AddGameObject();
    GameObject* WU_ROOT = scene.AddGameObject();

    WS_ROOT->AddComponent<KonamiCommand>();
    GameObject* displaySelector = scene.AddGameObject();
    // Start Window UI
    GameObject* WS_ROOTtext = scene.AddGameObject(WS_ROOT);
    WS_ROOT->AddComponent<BoxImage>()->SetBoxImage(100, 20, '*');
    WS_ROOTtext->AddComponent<AnimatedImage>()->SetSprites("TITLE");
    WS_ROOT->GetTransform()->position.y += 10;



    GameObject* S_UI_Selector = scene.AddGameObject(WS_ROOT);
    S_UI_Selector->AddComponent<VerticalSelector>();

    GameObject* S_seletion1 = AddFlexibleCategory(WS_ROOT, "CONTINUE", &scene, 20, 3, 0, -20, S_UI_Selector->GetComponent<Selector>());
    GameObject* S_seletion2 = AddFlexibleCategory(WS_ROOT, "NEW GAME START", &scene, 20, 3, 0, -25, S_UI_Selector->GetComponent<Selector>());
    GameObject* S_seletion3 = AddFlexibleCategory(WS_ROOT, "QUIT", &scene, 20, 3, 0, -30, S_UI_Selector->GetComponent<Selector>());
    S_seletion1->GetComponent<Button>()->onSelect = [displaySelector, WM_ROOT]() {SaveFile::Load(); displaySelector->GetComponent<Selector>()->Highlight(WM_ROOT->GetComponent<SelectableWindow>()); };
    S_seletion2->GetComponent<Button>()->onSelect = [displaySelector, WM_ROOT]() {displaySelector->GetComponent<Selector>()->Highlight(WM_ROOT->GetComponent<SelectableWindow>()); };
    S_seletion3->GetComponent<Button>()->onSelect = []() {endGame = true; };

    // Main Window UI
    GameObject* WM_ROOTtext = scene.AddGameObject(WM_ROOT);
    //WM_ROOTtext->AddComponent<BoxImage>()->SetBoxImage(105, 35, '*');
    WM_ROOTtext->AddComponent<TextImage>()->SetText(20, 3, " ");
    WM_ROOTtext->AddComponent<AnimatedImage>()->SetSprites("KIMCHI Default F");
    WM_ROOTtext->GetTransform()->position.x -= 55;


    GameObject* M_UI_Selector = scene.AddGameObject(WM_ROOT);
    M_UI_Selector->AddComponent<VerticalSelector>();

    GameObject* textBox;
    GameObject* M_MenuPanel = scene.AddGameObject(WM_ROOT);
    GameObject* M_category0 = AddFlexibleCategory(WM_ROOT, "김 장 하 기", &scene, 30, 5, 75, 16, M_UI_Selector->GetComponent<Selector>());
    GameObject* M_category1 = AddFlexibleCategory(WM_ROOT, "시 설", &scene, 30, 5, 75, 8, M_UI_Selector->GetComponent<Selector>());
    GameObject* M_category2 = AddFlexibleCategory(WM_ROOT, "업 그 레 이 드", &scene, 30, 5, 75, 0, M_UI_Selector->GetComponent<Selector>());
    GameObject* M_category3 = AddFlexibleCategory(WM_ROOT, "게 임 저 장", &scene, 30, 5, 75, -8, M_UI_Selector->GetComponent<Selector>());
    GameObject* M_category4 = AddFlexibleCategory(WM_ROOT, "게 임 종 료", &scene, 30, 5, 75, -16, M_UI_Selector->GetComponent<Selector>());

    GameObject* M_KimchiStatus = scene.AddGameObject(WM_ROOT);
    M_KimchiStatus->AddComponent<KimchiNumText>()->SetText(30, 4, "");
    M_KimchiStatus->GetTransform()->position.x -= 55;
    M_KimchiStatus->GetTransform()->position.y -= 20;

    GameObject* M_NewsBox = scene.AddGameObject(WM_ROOT);
    GameObject* M_NewsText = scene.AddGameObject(M_NewsBox);
    M_NewsBox->AddComponent<BoxImage>()->SetBoxImage(102, 10, '#');
    M_NewsText->AddComponent<NewsText>()->SetText(100, 8, "");
    M_NewsBox->GetTransform()->position.x -= 55;
    M_NewsBox->GetTransform()->position.y += 23;

    M_category0->GetComponent<Button>()->onSelect = [displaySelector, WF_ROOT]() {GameInfo::kimchis += 1; };
    M_category1->GetComponent<Button>()->onSelect = [displaySelector, WF_ROOT]() {displaySelector->GetComponent<Selector>()->Highlight(WF_ROOT->GetComponent<SelectableWindow>()); };
    M_category2->GetComponent<Button>()->onSelect = [displaySelector, WU_ROOT]() {displaySelector->GetComponent<Selector>()->Highlight(WU_ROOT->GetComponent<SelectableWindow>()); };
    M_category3->GetComponent<Button>()->onSelect = []() {SaveFile::Save(); };
    M_category4->GetComponent<Button>()->onSelect = []() {endGame = true; };

    M_category0->GetComponent<Button>()->selectSound = SoundType::Kimjang;

    M_MenuPanel->AddComponent<BoxImage>()->SetBoxImage(80, 50, '*');
    M_MenuPanel->GetTransform()->position.x = 75;

    // Facility Window UI
    GameObject* WF_ROOTtext = scene.AddGameObject(WF_ROOT);
    GameObject* WF_FacilityPortrait = scene.AddGameObject(WF_ROOT);
    WF_FacilityPortrait->AddComponent<AnimatedImage>()->SetSprites("ghost");
    WF_ROOTtext->AddComponent<TextImage>()->SetText(148, 35, "");
    WF_FacilityPortrait->GetTransform()->position.x -= 40;
    //WF_FacilityPortrait->GetTransform()->position.y+=5;

    GameObject* F_UI_Selector = scene.AddGameObject(WF_ROOT);
    F_UI_Selector->AddComponent<VerticalSelector>();
    GameObject* F_MenuPanel = scene.AddGameObject(WF_ROOT);
    F_MenuPanel->AddComponent<BoxImage>()->SetBoxImage(40, 55, '*');
    F_MenuPanel->GetTransform()->position.x = 100;

    GameObject* F_Facility1Text;
    GameObject* F_Facility2Text;
    GameObject* F_Facility3Text;
    GameObject* F_Facility4Text;
    GameObject* F_Facility5Text;
    GameObject* F_Facility6Text;
    GameObject* F_Facility7Text;
    GameObject* F_Facility8Text;

    GameObject* F_Return = AddFlexibleCategory(WF_ROOT, "돌 아 가 기", &scene, 20, 5, 100, 17, F_UI_Selector->GetComponent<Selector>());
    GameObject* F_Facility1 = AddFlexibleCategory(WF_ROOT, "할 머 니", &scene, 20, 3, 100, 10, F_UI_Selector->GetComponent<Selector>(), &F_Facility1Text);
    GameObject* F_Facility2 = AddFlexibleCategory(WF_ROOT, "김 치 도 둑", &scene, 20, 3, 100, 5, F_UI_Selector->GetComponent<Selector>(), &F_Facility2Text);
    GameObject* F_Facility3 = AddFlexibleCategory(WF_ROOT, "부 녀 회", &scene, 20, 3, 100, 0, F_UI_Selector->GetComponent<Selector>(), &F_Facility3Text);
    GameObject* F_Facility4 = AddFlexibleCategory(WF_ROOT, "농 장", &scene, 20, 3, 100, -5, F_UI_Selector->GetComponent<Selector>(), &F_Facility4Text);
    GameObject* F_Facility5 = AddFlexibleCategory(WF_ROOT, "공 장", &scene, 20, 3, 100, -10, F_UI_Selector->GetComponent<Selector>(), &F_Facility5Text);
    GameObject* F_Facility6 = AddFlexibleCategory(WF_ROOT, "사 당", &scene, 20, 3, 100, -15, F_UI_Selector->GetComponent<Selector>(), &F_Facility6Text);
    GameObject* F_Facility7 = AddFlexibleCategory(WF_ROOT, "가 상 분 열 기", &scene, 20, 3, 100, -20, F_UI_Selector->GetComponent<Selector>(), &F_Facility7Text);
    GameObject* F_Facility8 = AddFlexibleCategory(WF_ROOT, "김 치 우 주 선", &scene, 20, 3, 100, -25, F_UI_Selector->GetComponent<Selector>(), &F_Facility8Text);


    GameObject* Facil_NULL = scene.AddGameObject();
    GameObject* Facil_Granny = scene.AddGameObject();
    GameObject* Facil_Thief = scene.AddGameObject();
    GameObject* Facil_Society = scene.AddGameObject();
    GameObject* Facil_Farm = scene.AddGameObject();
    GameObject* Facil_Factory = scene.AddGameObject();
    GameObject* Facil_Temple = scene.AddGameObject();
    GameObject* Facil_Reactor = scene.AddGameObject();
    GameObject* Facil_Spaceship = scene.AddGameObject();

    Facil_NULL->AddComponent<Facility>()->Set("", "Goback", 0, 0, true);
    Facil_Granny->AddComponent<Facility>()->Set("할머니", "Normal Granny", 10, 0.1, true);
    Facil_Thief->AddComponent<Facility>()->Set("김치도둑", "Kimchi Thief(SCV Portrait)", 50, 1, true);
    Facil_Society->AddComponent<Facility>()->Set("부녀회", "Kimchi Society(Elf Woman)", 1000, 40, true);
    Facil_Farm->AddComponent<Facility>()->Set("농장", "Kimchi Farm(House)", 10000, 400, false);
    Facil_Factory->AddComponent<Facility>()->Set("공장", "Kimchi Factory(Terran Command Center)", 300000, 12000, false);
    Facil_Temple->AddComponent<Facility>()->Set("사당", "Kimchi Temple(Troll Templer)", 1000000, 40000, false);
    Facil_Reactor->AddComponent<Facility>()->Set("김치 차원문", "Terran Warp", 500000000, 20000000, false);
    Facil_Spaceship->AddComponent<Facility>()->Set("추진우주선", "SpaceShip", 25000000000, 1000000000, false);

    // 시설물 초기화
    {
        Facil_Granny->GetComponent<Facility>()->description = "김장을 하는 친절한 할머니입니다.";
        Facil_Thief->GetComponent<Facility>()->description = "이유는 모르겠지만 김치만을 훔쳐가는 도둑입니다.";
        Facil_Society->GetComponent<Facility>()->description = "동네 아주머니들이 심심해서 가볍게 시작한 김장모임입니다.";
        Facil_Farm->GetComponent<Facility>()->description = "유전자 조작 기술의 발달으로 김장이 되어져 있는 배추가 자라는 밭입니다.";
        Facil_Factory->GetComponent<Facility>()->description = "가장 최신 김장 기술들을 테스트하기 위한 공장을 건설합니다.";
        Facil_Temple->GetComponent<Facility>()->description = "올해 액운을 떨쳐내고 김장이 잘되기 위해 무당의 굿은 필수입니다.";
        Facil_Reactor->GetComponent<Facility>()->description = "가만히 있어도 김치가 복사가 된다고!?";
        Facil_Spaceship->GetComponent<Facility>()->description = "이젠 김치로 생화학 무기를 만드는 시대가 왔습니다! 외부의 위협을 빠르게 제거 가능합니다.";

        Facil_Granny->GetComponent<Facility>()->selectSound = SoundType::grandma_original;
        Facil_Thief->GetComponent<Facility>()->selectSound = SoundType::thief_original;
        Facil_Society->GetComponent<Facility>()->selectSound = SoundType::kimchiclub_mumbling;
        Facil_Farm->GetComponent<Facility>()->selectSound = SoundType::farm_original;
        Facil_Factory->GetComponent<Facility>()->selectSound = SoundType::factory_original;
        Facil_Temple->GetComponent<Facility>()->selectSound = SoundType::temple_original;
        Facil_Reactor->GetComponent<Facility>()->selectSound = SoundType::mitotic_original;
        Facil_Spaceship->GetComponent<Facility>()->selectSound = SoundType::spaceship_original;
    }

    //F_Facility1->GetComponent<Button>()->highlightSound = SoundType::HalmeQuote;

    F_Return->GetComponent<Button>()->onSelect = [displaySelector, WM_ROOT]() {displaySelector->GetComponent<Selector>()->Highlight(WM_ROOT->GetComponent<SelectableWindow>()); };

    GameObject* F_DescriptionBox = scene.AddGameObject(WF_ROOT);
    GameObject* F_Description = scene.AddGameObject(F_DescriptionBox);
    F_DescriptionBox->AddComponent<BoxImage>()->SetBoxImage(70, 10, '#');
    F_Description->AddComponent<TextImage>()->SetText(68, 8, "");
    F_DescriptionBox->GetTransform()->position.x = 40;
    F_DescriptionBox->GetTransform()->position.y = -23;

    GameObject* F_ItemIntroductionBox = scene.AddGameObject(WF_ROOT);
    GameObject* F_ItemIntroduction = scene.AddGameObject(F_ItemIntroductionBox);
    F_ItemIntroductionBox->AddComponent<BoxImage>();
    F_ItemIntroductionBox->GetComponent<BoxImage>()->SetBoxImage(35, 20, '*');
    F_ItemIntroduction->AddComponent<FacilityText>();
    F_ItemIntroduction->GetComponent<FacilityText>()->SetText(23, 18, "");
    F_ItemIntroductionBox->GetTransform()->position.x = 57;
    F_ItemIntroductionBox->GetTransform()->position.y = -7;

    GameObject* F_NewsBox = scene.AddGameObject(WF_ROOT);
    GameObject* F_NewsText = scene.AddGameObject(F_NewsBox);
    F_NewsBox->AddComponent<BoxImage>()->SetBoxImage(50, 10, '#');
    F_NewsText->AddComponent<NewsText>()->SetText(48, 8, "");
    F_NewsBox->GetTransform()->position.x = 50;
    F_NewsBox->GetTransform()->position.y = 23;

    GameObject* F_KimchiBox = scene.AddGameObject(WF_ROOT);
    GameObject* F_KimchiText = scene.AddGameObject(F_KimchiBox);
    F_KimchiBox->AddComponent<BoxImage>()->SetBoxImage(40, 10, '*');
    F_KimchiText->AddComponent<KimchiNumText>()->SetText(38, 8, "");
    F_KimchiBox->GetTransform()->position.x = 55;
    F_KimchiBox->GetTransform()->position.y = 12;

    F_Return->GetComponent<Button>()->onHighlight = [Facil_NULL, F_ItemIntroduction, WF_FacilityPortrait, F_Description]() {Facil_NULL->GetComponent<Facility>()->Apply(WF_FacilityPortrait->GetComponent<AnimatedImage>(), F_ItemIntroduction->GetComponent<FacilityText>(), F_Description->GetComponent<TextImage>()); F_ItemIntroduction->GetComponent<FacilityText>()->SetFacility(nullptr); };
    F_Facility1->GetComponent<Button>()->onHighlight = [Facil_Granny, F_ItemIntroduction, WF_FacilityPortrait, F_Description]() {Facil_Granny->GetComponent<Facility>()->Apply(WF_FacilityPortrait->GetComponent<AnimatedImage>(), F_ItemIntroduction->GetComponent<FacilityText>(), F_Description->GetComponent<TextImage>()); };
    F_Facility2->GetComponent<Button>()->onHighlight = [Facil_Thief, F_ItemIntroduction, WF_FacilityPortrait, F_Description]() {Facil_Thief->GetComponent<Facility>()->Apply(WF_FacilityPortrait->GetComponent<AnimatedImage>(), F_ItemIntroduction->GetComponent<FacilityText>(), F_Description->GetComponent<TextImage>()); };
    F_Facility3->GetComponent<Button>()->onHighlight = [Facil_Society, F_ItemIntroduction, WF_FacilityPortrait, F_Description]() {Facil_Society->GetComponent<Facility>()->Apply(WF_FacilityPortrait->GetComponent<AnimatedImage>(), F_ItemIntroduction->GetComponent<FacilityText>(), F_Description->GetComponent<TextImage>()); };
    F_Facility4->GetComponent<Button>()->onHighlight = [Facil_Farm, F_ItemIntroduction, WF_FacilityPortrait, F_Description]() {Facil_Farm->GetComponent<Facility>()->Apply(WF_FacilityPortrait->GetComponent<AnimatedImage>(), F_ItemIntroduction->GetComponent<FacilityText>(), F_Description->GetComponent<TextImage>()); };
    F_Facility5->GetComponent<Button>()->onHighlight = [Facil_Factory, F_ItemIntroduction, WF_FacilityPortrait, F_Description]() {Facil_Factory->GetComponent<Facility>()->Apply(WF_FacilityPortrait->GetComponent<AnimatedImage>(), F_ItemIntroduction->GetComponent<FacilityText>(), F_Description->GetComponent<TextImage>()); };
    F_Facility6->GetComponent<Button>()->onHighlight = [Facil_Temple, F_ItemIntroduction, WF_FacilityPortrait, F_Description]() {Facil_Temple->GetComponent<Facility>()->Apply(WF_FacilityPortrait->GetComponent<AnimatedImage>(), F_ItemIntroduction->GetComponent<FacilityText>(), F_Description->GetComponent<TextImage>()); };
    F_Facility7->GetComponent<Button>()->onHighlight = [Facil_Reactor, F_ItemIntroduction, WF_FacilityPortrait, F_Description]() {Facil_Reactor->GetComponent<Facility>()->Apply(WF_FacilityPortrait->GetComponent<AnimatedImage>(), F_ItemIntroduction->GetComponent<FacilityText>(), F_Description->GetComponent<TextImage>()); };
    F_Facility8->GetComponent<Button>()->onHighlight = [Facil_Spaceship, F_ItemIntroduction, WF_FacilityPortrait, F_Description]() {Facil_Spaceship->GetComponent<Facility>()->Apply(WF_FacilityPortrait->GetComponent<AnimatedImage>(), F_ItemIntroduction->GetComponent<FacilityText>(), F_Description->GetComponent<TextImage>()); };

    F_Facility1->GetComponent<Button>()->onSelect = [Facil_Granny]() {Facil_Granny->GetComponent<Facility>()->Buy(); };
    F_Facility2->GetComponent<Button>()->onSelect = [Facil_Thief]() {Facil_Thief->GetComponent<Facility>()->Buy(); };
    F_Facility3->GetComponent<Button>()->onSelect = [Facil_Society]() {Facil_Society->GetComponent<Facility>()->Buy(); };
    F_Facility4->GetComponent<Button>()->onSelect = [Facil_Farm]() {Facil_Farm->GetComponent<Facility>()->Buy(); };
    F_Facility5->GetComponent<Button>()->onSelect = [Facil_Factory]() {Facil_Factory->GetComponent<Facility>()->Buy(); };
    F_Facility6->GetComponent<Button>()->onSelect = [Facil_Temple]() {Facil_Temple->GetComponent<Facility>()->Buy(); };
    F_Facility7->GetComponent<Button>()->onSelect = [Facil_Reactor]() {Facil_Reactor->GetComponent<Facility>()->Buy(); };
    F_Facility8->GetComponent<Button>()->onSelect = [Facil_Spaceship]() {Facil_Spaceship->GetComponent<Facility>()->Buy(); };

    WF_ROOT->AddComponent<FacilityUnlock>();
    //WF_ROOT->GetComponent<FacilityUnlock>()->Facilities.push_back(Facil_Granny->GetComponent<Facility>());
    //WF_ROOT->GetComponent<FacilityUnlock>()->buttons.insert(make_pair(Facil_Granny->GetComponent<Facility>(), F_Facility1->GetComponent<Button>()));
    //WF_ROOT->GetComponent<FacilityUnlock>()->buttonTexts.insert(make_pair(Facil_Granny->GetComponent<Facility>(), F_Facility1Text));

    WF_ROOT->GetComponent<FacilityUnlock>()->Facilities.push_back(Facil_Granny->GetComponent<Facility>());
    WF_ROOT->GetComponent<FacilityUnlock>()->Facilities.push_back(Facil_Thief->GetComponent<Facility>());
    WF_ROOT->GetComponent<FacilityUnlock>()->Facilities.push_back(Facil_Society->GetComponent<Facility>());
    WF_ROOT->GetComponent<FacilityUnlock>()->Facilities.push_back(Facil_Farm->GetComponent<Facility>());
    WF_ROOT->GetComponent<FacilityUnlock>()->Facilities.push_back(Facil_Factory->GetComponent<Facility>());
    WF_ROOT->GetComponent<FacilityUnlock>()->Facilities.push_back(Facil_Temple->GetComponent<Facility>());
    WF_ROOT->GetComponent<FacilityUnlock>()->Facilities.push_back(Facil_Reactor->GetComponent<Facility>());
    WF_ROOT->GetComponent<FacilityUnlock>()->Facilities.push_back(Facil_Spaceship->GetComponent<Facility>());

    WF_ROOT->GetComponent<FacilityUnlock>()->buttons.insert(make_pair(Facil_Granny->GetComponent<Facility>(), F_Facility1->GetComponent<Button>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttons.insert(make_pair(Facil_Thief->GetComponent<Facility>(), F_Facility2->GetComponent<Button>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttons.insert(make_pair(Facil_Society->GetComponent<Facility>(), F_Facility3->GetComponent<Button>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttons.insert(make_pair(Facil_Farm->GetComponent<Facility>(), F_Facility4->GetComponent<Button>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttons.insert(make_pair(Facil_Factory->GetComponent<Facility>(), F_Facility5->GetComponent<Button>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttons.insert(make_pair(Facil_Temple->GetComponent<Facility>(), F_Facility6->GetComponent<Button>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttons.insert(make_pair(Facil_Reactor->GetComponent<Facility>(), F_Facility7->GetComponent<Button>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttons.insert(make_pair(Facil_Spaceship->GetComponent<Facility>(), F_Facility8->GetComponent<Button>()));

    WF_ROOT->GetComponent<FacilityUnlock>()->buttonTexts.insert(make_pair(Facil_Granny->GetComponent<Facility>(), F_Facility1Text->GetComponent<TextImage>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttonTexts.insert(make_pair(Facil_Thief->GetComponent<Facility>(), F_Facility2Text->GetComponent<TextImage>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttonTexts.insert(make_pair(Facil_Society->GetComponent<Facility>(), F_Facility3Text->GetComponent<TextImage>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttonTexts.insert(make_pair(Facil_Farm->GetComponent<Facility>(), F_Facility4Text->GetComponent<TextImage>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttonTexts.insert(make_pair(Facil_Factory->GetComponent<Facility>(), F_Facility5Text->GetComponent<TextImage>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttonTexts.insert(make_pair(Facil_Temple->GetComponent<Facility>(), F_Facility6Text->GetComponent<TextImage>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttonTexts.insert(make_pair(Facil_Reactor->GetComponent<Facility>(), F_Facility7Text->GetComponent<TextImage>()));
    WF_ROOT->GetComponent<FacilityUnlock>()->buttonTexts.insert(make_pair(Facil_Spaceship->GetComponent<Facility>(), F_Facility8Text->GetComponent<TextImage>()));

    // Upgrade Window UI 
    GameObject* U_UpgradeImage = scene.AddGameObject(WU_ROOT);
    GameObject* U_UpgradeNullImage = scene.AddGameObject(U_UpgradeImage);
    GameObject* U_UpgradeQueue = scene.AddGameObject(WU_ROOT);
    GameObject* U_DescriptionText;
    GameObject* U_Description = AddFlexibleCategory(WU_ROOT, "VIDE", &scene, 150, 12, -20, -20, 0, &U_DescriptionText);

    U_UpgradeImage->AddComponent<MatrixCustomImage>()->SetMatrixString(File2String("stimpack.txt"));
    U_UpgradeImage->GetTransform()->position.x -= 20;
    U_UpgradeImage->GetTransform()->position.y += 7;
    U_UpgradeNullImage->AddComponent<AnimatedImage>()->SetSprites("Goback");

    GameObject* U_MenuPanel = scene.AddGameObject(WU_ROOT);
    U_MenuPanel->AddComponent<BoxImage>()->SetBoxImage(40, 55, '*');
    U_MenuPanel->GetTransform()->position.x = 100;

    GameObject* U_NewsBox = scene.AddGameObject(WU_ROOT);
    GameObject* U_NewsText = scene.AddGameObject(U_NewsBox);
    U_NewsBox->AddComponent<BoxImage>()->SetBoxImage(50, 10, '#');
    U_NewsText->AddComponent<NewsText>()->SetText(48, 8, "");
    U_NewsBox->GetTransform()->position.x = 50;
    U_NewsBox->GetTransform()->position.y = 23;

    GameObject* U_KimchiBox = scene.AddGameObject(WU_ROOT);
    GameObject* U_KimchiText = scene.AddGameObject(U_KimchiBox);
    U_KimchiBox->AddComponent<BoxImage>()->SetBoxImage(40, 10, '*');
    U_KimchiText->AddComponent<KimchiNumText>()->SetText(38, 8, "");
    U_KimchiBox->GetTransform()->position.x = 55;
    U_KimchiBox->GetTransform()->position.y = 12;

    GameObject* U_PriceBox = scene.AddGameObject(WU_ROOT);
    GameObject* U_PriceText = scene.AddGameObject(U_PriceBox);
    U_PriceBox->AddComponent<BoxImage>()->SetBoxImage(30, 5, '*');
    U_PriceText->AddComponent<TextImage>()->SetText(28, 3, "");
    U_PriceBox->GetTransform()->position.x = 40;
    U_PriceBox->GetTransform()->position.y = -16;

    GameObject* U_UI_Selector = scene.AddGameObject(WU_ROOT);
    U_UI_Selector->AddComponent<VerticalSelector>();


    GameObject* U_Selection = AddFlexibleCategory(WU_ROOT, "돌 아 가 기", &scene, 20, 5, 100, 12, U_UI_Selector->GetComponent<Selector>());

    vector<GameObject*> U_RSelectionTexts(7, nullptr);
    GameObject* U_RSelection1 = AddFlexibleCategory(WU_ROOT, "VIDE", &scene, 20, 3, 100, 5, U_UI_Selector->GetComponent<Selector>(), &U_RSelectionTexts[0]);
    GameObject* U_RSelection2 = AddFlexibleCategory(WU_ROOT, "VIDE", &scene, 20, 3, 100, 0, U_UI_Selector->GetComponent<Selector>(), &U_RSelectionTexts[1]);
    GameObject* U_RSelection3 = AddFlexibleCategory(WU_ROOT, "VIDE", &scene, 20, 3, 100, -5, U_UI_Selector->GetComponent<Selector>(), &U_RSelectionTexts[2]);
    GameObject* U_RSelection4 = AddFlexibleCategory(WU_ROOT, "VIDE", &scene, 20, 3, 100, -10, U_UI_Selector->GetComponent<Selector>(), &U_RSelectionTexts[3]);
    GameObject* U_RSelection5 = AddFlexibleCategory(WU_ROOT, "VIDE", &scene, 20, 3, 100, -15, U_UI_Selector->GetComponent<Selector>(), &U_RSelectionTexts[4]);
    GameObject* U_RSelection6 = AddFlexibleCategory(WU_ROOT, "VIDE", &scene, 20, 3, 100, -20, U_UI_Selector->GetComponent<Selector>(), &U_RSelectionTexts[5]);
    GameObject* U_RSelection7 = AddFlexibleCategory(WU_ROOT, "VIDE", &scene, 20, 3, 100, -25, U_UI_Selector->GetComponent<Selector>(), &U_RSelectionTexts[6]);

    U_UpgradeQueue->AddComponent<UpgradeQueue>();
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->selector = U_UI_Selector->GetComponent<VerticalSelector>();
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->upgradeImage = U_UpgradeImage->GetComponent<MatrixCustomImage>();
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->description = U_DescriptionText->GetComponent<TextImage>();
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->cost = U_PriceText->GetComponent<TextImage>();
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->buttonNestedTexts = U_RSelectionTexts;
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->buttons.push_back(U_RSelection1);
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->buttons.push_back(U_RSelection2);
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->buttons.push_back(U_RSelection3);
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->buttons.push_back(U_RSelection4);
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->buttons.push_back(U_RSelection5);
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->buttons.push_back(U_RSelection6);
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->buttons.push_back(U_RSelection7);
    U_UpgradeQueue->GetComponent<UpgradeQueue>()->UpdateButtons();

    U_Selection->GetComponent<Button>()->onHighlight =
        [U_UpgradeNullImage, U_UpgradeImage, U_Description, U_PriceBox, U_DescriptionText]()
    {
        U_UpgradeImage->GetComponent<MatrixCustomImage>()->SetMatrixString("");
        U_UpgradeNullImage->SetSelfActive(true);
        //U_Description->SetSelfActive(false);
        U_DescriptionText->SetSelfActive(false);
        U_PriceBox->SetSelfActive(false);
    };
    U_Selection->GetComponent<Button>()->onDehighlight =
        [U_UpgradeNullImage, U_UpgradeImage, U_Description, U_PriceBox, U_DescriptionText]()
    {
        U_UpgradeNullImage->SetSelfActive(false);
        //U_Description->SetSelfActive(true);
        U_DescriptionText->SetSelfActive(true);
        U_PriceBox->SetSelfActive(true);
    };
    U_Selection->GetComponent<Button>()->onSelect = [displaySelector, WM_ROOT]() {displaySelector->GetComponent<Selector>()->Highlight(WM_ROOT->GetComponent<SelectableWindow>()); };

    // 업그레이드 설정
    {
        AddUpgradePreset(
            // 업그레이드 이름 
            "고무 장갑",
            // 업그레이드 설정
            "할머니들의 손 보호를 위한 평범한 고무장갑입니다.",
            // 업그레이드 효과
            "할머니의 kps가 2배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Rubber gloves.txt",
            // 업그레이드 시 동작
            [Facil_Granny]()
            {
                Facil_Granny->GetComponent<Facility>()->kps *= 2;
                Facil_Granny->GetComponent<Facility>()->portraitFile = "Normal Granny";
                Facil_Granny->GetComponent<Facility>()->selectSound = SoundType::grandma_original;
                Facil_Granny->GetComponent<Facility>()->description = "고무장갑을 껴 김장에 익숙해진 할머니입니다.";
            },
            // 업그레이드 비용
                100,
                // 업그레이드 완료 효과음
                SoundType::RuuberGlove);

        AddUpgradePreset(
            // 업그레이드 이름 
            "보약",
            // 업그레이드 설정
            "건강을 챙겨드리기 위한 보약을 할머니들께 드립니다.",
            // 업그레이드 효과
            "할머니의 kps가 4배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Boyak.txt",
            // 업그레이드 시 동작
            [Facil_Granny]()
            {
                Facil_Granny->GetComponent<Facility>()->kps *= 4;
                Facil_Granny->GetComponent<Facility>()->portraitFile = "Happy Granny";
                Facil_Granny->GetComponent<Facility>()->selectSound = SoundType::grandma_original;
                Facil_Granny->GetComponent<Facility>()->description = "보약을 먹어 체력이 강해진 할머니입니다.";
            },
            // 업그레이드 비용
                400,
                // 업그레이드 완료 효과음
                SoundType::Boyak);

        AddUpgradePreset(
            // 업그레이드 이름 
            "김장 자극제",
            // 업그레이드 설정
            "할머니들에게 상시복용 가능한 영양제를 지급하여 업무 효율을 늘립니다.",
            // 업그레이드 효과
            "할머니의 kps가 32배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "stimpack.txt",
            // 업그레이드 시 동작
            [Facil_Granny]()
            {
                Facil_Granny->GetComponent<Facility>()->kps *= 32;
                Facil_Granny->GetComponent<Facility>()->portraitFile = "Very Happy Granny";
                Facil_Granny->GetComponent<Facility>()->selectSound = SoundType::Stimpack;
                Facil_Granny->GetComponent<Facility>()->description = "웃는 얼굴로 김장을 하시는 할머니들의 표정에서 광기가 느껴집니다.";
            },
            // 업그레이드 비용
                12800,
                // 업그레이드 완료 효과음
                SoundType::Stimpack);

        AddUpgradePreset(
            // 업그레이드 이름 
            "인공 눈 이식",
            // 업그레이드 설정
            "할머니들에게 기계 눈을 이식하여 검수과정을 자동화합니다.",
            // 업그레이드 효과
            "할머니의 kps가 256배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "ocular implant.txt",
            // 업그레이드 시 동작
            [Facil_Granny]()
            {
                Facil_Granny->GetComponent<Facility>()->kps *= 256;
                Facil_Granny->GetComponent<Facility>()->portraitFile = "ghost";
                Facil_Granny->GetComponent<Facility>()->selectSound = SoundType::Receiving;
                Facil_Granny->GetComponent<Facility>()->description = "인공 눈을 이식 받은 할머니가 김치를 빠르게 검수하고 있습니다.";
            },
            // 업그레이드 비용
                3200000,
                // 업그레이드 완료 효과음
                SoundType::robotArm);


        AddUpgradePreset(
            // 업그레이드 이름 
            "인격말살",
            // 업그레이드 설정
            "할머니들의 잡생각을 없애 김장에 초집중 상태를 유지할 수 있게 됩니다.",
            // 업그레이드 효과
            "할머니의 kps가 100배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Brain in Bottle.txt",
            // 업그레이드 시 동작
            [Facil_Granny]()
            {
                Facil_Granny->GetComponent<Facility>()->kps *= 100;
                Facil_Granny->GetComponent<Facility>()->portraitFile = "ghost";
                Facil_Granny->GetComponent<Facility>()->selectSound = SoundType::Receiving;
                Facil_Granny->GetComponent<Facility>()->description = "그 곳에는 더이상 할머니라 부를 수 없는 형체가 김장 중입니다.";
            },
            // 업그레이드 비용
                320000000,
                // 업그레이드 완료 효과음
                SoundType::ZergResearchComplete);

        AddUpgradePreset(
            // 업그레이드 이름 
            "군체의식",
            // 업그레이드 설정
            "이제 할머니들은 칼라로 연결되어 생각을 공유합니다",
            // 업그레이드 효과
            "할머니의 kps가 1000배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Overmind1.txt",
            // 업그레이드 시 동작
            [Facil_Granny]()
            {
                Facil_Granny->GetComponent<Facility>()->kps *= 1000;
                Facil_Granny->GetComponent<Facility>()->portraitFile = "Archon";
                Facil_Granny->GetComponent<Facility>()->selectSound = SoundType::grandma_archon_portrait;
                Facil_Granny->GetComponent<Facility>()->description = "우린... 연결되어 있다.....";
            },
            // 업그레이드 비용
                320000000000,
                // 업그레이드 완료 효과음
                SoundType::Answer_HiveMind);

        AddUpgradePreset(
            // 업그레이드 이름 
            "발업",
            // 업그레이드 설정
            "보다 빠르게! 김치를! 훔쳐옵니다!",
            // 업그레이드 효과
            "김치도둑의 kps가 2배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Speed Up.txt",
            // 업그레이드 시 동작
            [Facil_Thief]()
            {
                Facil_Thief->GetComponent<Facility>()->kps *= 2;
                Facil_Thief->GetComponent<Facility>()->portraitFile = "Kimchi Thief(SCV Portrait)";
                Facil_Thief->GetComponent<Facility>()->selectSound = SoundType::thief_original;
                Facil_Thief->GetComponent<Facility>()->description = "발이 더 빨라진 도둑입니다.";
            },
            // 업그레이드 비용
                500,
                // 업그레이드 완료 효과음
                SoundType::thief_speedup);

        AddUpgradePreset(
            // 업그레이드 이름 
            "철판",
            // 업그레이드 설정
            "얼굴에 철판을 깔아 도둑질을 들켰을때 뻔뻔하게 대처할 수 있습니다.",
            // 업그레이드 효과
            "김치도둑의 kps가 4배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Iron Face.txt",
            // 업그레이드 시 동작
            [Facil_Thief]()
            {
                Facil_Thief->GetComponent<Facility>()->kps *= 4;
                Facil_Thief->GetComponent<Facility>()->portraitFile = "Thief(Airport Thief)";
                Facil_Thief->GetComponent<Facility>()->selectSound = SoundType::thief_airport;
                Facil_Thief->GetComponent<Facility>()->description = "왜 나한테만 그러는데 **! 내가 뭘 잘못했는데 **!";
            },
            // 업그레이드 비용
                2000,
                // 업그레이드 완료 효과음
                SoundType::thief_airport);



        AddUpgradePreset(
            // 업그레이드 이름 
            "클로킹",
            // 업그레이드 설정
            "은신을 통해 더 이상 도둑의 도둑질을 들키질 않습니다.",
            // 업그레이드 효과
            "김치도둑의 kps가 256배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Clocking.txt",
            // 업그레이드 시 동작
            [Facil_Thief]()
            {
                Facil_Thief->GetComponent<Facility>()->kps *= 256;
                Facil_Thief->GetComponent<Facility>()->portraitFile = "Kimchi Thief(Dark Templer Portrait)";
                Facil_Thief->GetComponent<Facility>()->selectSound = SoundType::thief_stealth_portrait;
                Facil_Thief->GetComponent<Facility>()->description = "은신 기술을 터득한 도둑입니다. 그의 도둑질 기술은 한 걸음 더 나아갔습니다.";
            },
            // 업그레이드 비용
                512000,
                // 업그레이드 완료 효과음
                SoundType::thief_stealth);



        AddUpgradePreset(
            // 업그레이드 이름 
            "주민 포섭",
            // 업그레이드 설정
            "모든 동네 사람들이 모여 이제 김장을 합니다.",
            // 업그레이드 효과
            "부녀희의 kps가 4배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Population up.txt",
            // 업그레이드 시 동작
            [Facil_Society]()
            {
                Facil_Society->GetComponent<Facility>()->kps *= 4;
                Facil_Society->GetComponent<Facility>()->portraitFile = "Kimchi Society(Elf Woman)";
                Facil_Society->GetComponent<Facility>()->selectSound = SoundType::kimchiclub_mumbling;
                Facil_Society->GetComponent<Facility>()->description = "주민들이 부녀회에 포섭되어 부녀회가 북적거립니다.";
            },
            // 업그레이드 비용
                20000,
                // 업그레이드 완료 효과음
                SoundType::kimchiclub_crowd);

        AddUpgradePreset(
            // 업그레이드 이름 
            "속도 UP!",
            // 업그레이드 설정
            "때론 사랑의 채직찔도 필요한 법입니다.",
            // 업그레이드 효과
            "부녀희의 kps가 4배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Society_Speed up.txt",
            // 업그레이드 시 동작
            [Facil_Society]()
            {
                Facil_Society->GetComponent<Facility>()->kps *= 4;
                Facil_Society->GetComponent<Facility>()->portraitFile = "Kimchi Society(Elf Woman)";
                Facil_Society->GetComponent<Facility>()->selectSound = SoundType::kimchiclub_mumbling;
                Facil_Society->GetComponent<Facility>()->description = "사랑의 채찍질로 인해 부녀회의 김치 만드는 속도가 빨라졌습니다.";

            },
            // 업그레이드 비용
                80000,
                // 업그레이드 완료 효과음
                SoundType::kimchiclub_speedup);

        AddUpgradePreset(
            // 업그레이드 이름 
            "아드레날린",
            // 업그레이드 설정
            "주민들은 이제 넘치는 아드레날린으로 김장에 필요한 모든 속도가 증가했습니다.",
            // 업그레이드 효과
            "부녀희의 kps가 100배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Society_Adrenaline.txt",
            // 업그레이드 시 동작
            [Facil_Society]()
            {
                Facil_Society->GetComponent<Facility>()->kps *= 100;
                Facil_Society->GetComponent<Facility>()->portraitFile = "Kimchi Society(Elf Worrier)";
                Facil_Society->GetComponent<Facility>()->selectSound = SoundType::kimchiclub_mumbling;
                Facil_Society->GetComponent<Facility>()->description = "더 이상 그들을 일반적인 부녀회라 부를수 없습니다. 그들은 이제 전사들입니다.";

            },
            // 업그레이드 비용
                8000000,
                // 업그레이드 완료 효과음
                SoundType::kimchiclub_adrenalin);

        AddUpgradePreset(
            // 업그레이드 이름 
            "최신 농기구",
            // 업그레이드 설정
            "더 이상 농기구들이 손상되지 않습니다.",
            // 업그레이드 효과
            "김치 농장의 kps가 2배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "agricultural implement.txt",
            // 업그레이드 시 동작
            [Facil_Farm]()
            {
                Facil_Farm->GetComponent<Facility>()->kps *= 2;
                Facil_Farm->GetComponent<Facility>()->portraitFile = "Kimchi Farm(House)";
                Facil_Farm->GetComponent<Facility>()->selectSound = SoundType::farm_original;
                Facil_Farm->GetComponent<Facility>()->description = "농장은 최신 농기구를 갖춰 더욱 발전했습니다.";


            },
            // 업그레이드 비용
                100000,
                // 업그레이드 완료 효과음
                SoundType::farm_tools);

        AddUpgradePreset(
            // 업그레이드 이름 
            "초화학 비료",
            // 업그레이드 설정
            "해충들을 더이상 당신의 김치의 상대가 되지 못합니다.",
            // 업그레이드 효과
            "김치 농장의 kps가 100배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "fertilizer.txt",
            // 업그레이드 시 동작
            [Facil_Farm]()
            {
                Facil_Farm->GetComponent<Facility>()->kps *= 100;
                Facil_Farm->GetComponent<Facility>()->portraitFile = "Kimchi Farm(Zerg Spawnimg Pool)";
                Facil_Farm->GetComponent<Facility>()->selectSound = SoundType::farm_hatchery_portrait;
                Facil_Farm->GetComponent<Facility>()->description = "초화학 비료의 힘은 대단했습니다! 더 이상 아무도 접근 불가능한 모습의 농장입니다.";

            },
            // 업그레이드 비용
                100000000,
                // 업그레이드 완료 효과음
                SoundType::farm_fertilizer);

        AddUpgradePreset(
            // 업그레이드 이름 
            "김치 나무",
            // 업그레이드 설정
            "유전자 과학의 발달은 나무에서 김치가 열리는 경지까지 도달하였습니다.",
            // 업그레이드 효과
            "김치 농장의 kps가 10배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Kimchi Tree.txt",
            // 업그레이드 시 동작
            [Facil_Farm]()
            {
                Facil_Farm->GetComponent<Facility>()->kps *= 10;
                Facil_Farm->GetComponent<Facility>()->portraitFile = "Kimchi Farm(Zerg Brain Hatchery)";
                Facil_Farm->GetComponent<Facility>()->selectSound = SoundType::farm_hatchery_portrait;
                Facil_Farm->GetComponent<Facility>()->description = "농장이 왜 두근두근 움직이는지는 원인 불명이지만 김치만 잘 만들면 됩니다.";

            },
            // 업그레이드 비용
                1000000000,
                // 업그레이드 완료 효과음
                SoundType::farm_tree);

        AddUpgradePreset(
            // 업그레이드 이름 
            "SCV",
            // 업그레이드 설정
            "Reay to go sir!",
            // 업그레이드 효과
            "김치 공장의 kps가 8배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "SCV.txt",
            // 업그레이드 시 동작
            [Facil_Factory]()
            {
                Facil_Factory->GetComponent<Facility>()->kps *= 8;
                Facil_Factory->GetComponent<Facility>()->portraitFile = "Kimchi Factory(Terran Command Center)";
                Facil_Factory->GetComponent<Facility>()->selectSound = SoundType::factory_original;
                Facil_Factory->GetComponent<Facility>()->description = "공장에서 SCV들이 열심히 김치를 만들고 있습니다.";

            },
            // 업그레이드 비용
                12000000,
                // 업그레이드 완료 효과음
                SoundType::factory_scv);

        AddUpgradePreset(
            // 업그레이드 이름 
            "자동 생산 시설",
            // 업그레이드 설정
            "이제 인력은 필요 없습니다. 로봇을 가동하기 위한 전력만이 필요할뿐...",
            // 업그레이드 효과
            "김치 공장의 kps가 100배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Automatic Factory.txt",
            // 업그레이드 시 동작
            [Facil_Factory]()
            {
                Facil_Factory->GetComponent<Facility>()->kps *= 100;
                Facil_Factory->GetComponent<Facility>()->portraitFile = "Infested Command Center";
                Facil_Factory->GetComponent<Facility>()->selectSound = SoundType::factory_original;
                Facil_Factory->GetComponent<Facility>()->description = "이제 공장은 마치 하나의 생명체처럼 유기적으로 김치를 생산합니다.";

            },
            // 업그레이드 비용
                1200000000,
                // 업그레이드 완료 효과음
                SoundType::factory_auto);

        AddUpgradePreset(
            // 업그레이드 이름 
            "반응로 건설",
            // 업그레이드 설정
            "무한에 가까운 에너지로 공장은 이제 영구적인 기관이 되었습니다.",
            // 업그레이드 효과
            "김치 공장의 kps가 2배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Reactor.txt",
            // 업그레이드 시 동작
            [Facil_Factory]()
            {
                Facil_Factory->GetComponent<Facility>()->kps *= 2;
                Facil_Factory->GetComponent<Facility>()->portraitFile = "Kimchi Factory (Terran Woman)";
                Facil_Factory->GetComponent<Facility>()->selectSound = SoundType::factory_original;
                Facil_Factory->GetComponent<Facility>()->description = "무한동력에 가까운 공장을 운영하기 위한 최첨단 AI를 설치했습니다.";

            },
            // 업그레이드 비용
                2400000000,
                // 업그레이드 완료 효과음
                SoundType::factory_reactor);

        AddUpgradePreset(
            // 업그레이드 이름 
            "정기적인 제물",
            // 업그레이드 설정
            "사당의 굿의 효혐이 증가합니다.",
            // 업그레이드 효과
            "김치 사당의 kps가 20배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Sacrifice.txt",
            // 업그레이드 시 동작
            [Facil_Temple]()
            {
                Facil_Temple->GetComponent<Facility>()->kps *= 20;
                Facil_Temple->GetComponent<Facility>()->portraitFile = "Kimchi Temple(Troll Templer)";
                Facil_Temple->GetComponent<Facility>()->selectSound = SoundType::temple_original;
                Facil_Temple->GetComponent<Facility>()->description = "정기적인 제물 공양으로 사당이 더욱 활기차졌습니다.";

            },
            // 업그레이드 비용
                200000000,
                // 업그레이드 완료 효과음
                SoundType::temple_sacrifice);

        AddUpgradePreset(
            // 업그레이드 이름 
            "배추도사 무도사",
            // 업그레이드 설정
            "도사님들은 겉은 귀여워 보이지만 실은 엄청나신 분들입니다.",
            // 업그레이드 효과
            "김치 사당의 kps가 10배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Cabbage and Radish sprits.txt",
            // 업그레이드 시 동작
            [Facil_Temple]()
            {
                Facil_Temple->GetComponent<Facility>()->kps *= 10;
                Facil_Temple->GetComponent<Facility>()->portraitFile = "Kimchi Temple(High Templer)";
                Facil_Temple->GetComponent<Facility>()->selectSound = SoundType::temple_original;
                Facil_Temple->GetComponent<Facility>()->description = "이곳의 신성력은 범접할 수 없는 수준입니다.";

            },
            // 업그레이드 비용
                2000000000,
                // 업그레이드 완료 효과음
                SoundType::temple_dosa);

        AddUpgradePreset(
            // 업그레이드 이름 
            "워프 시스템",
            // 업그레이드 설정
            "이제 김치는 어느 곳에서나 존재할 수 있습니다.",
            // 업그레이드 효과
            "김치 가상분열기의 kps가 2배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Warp.txt",
            // 업그레이드 시 동작
            [Facil_Reactor]()
            {
                Facil_Reactor->GetComponent<Facility>()->kps *= 2;
                Facil_Reactor->GetComponent<Facility>()->portraitFile = "Terran Warp";
                Facil_Reactor->GetComponent<Facility>()->selectSound = SoundType::mitotic_original;
                Facil_Reactor->GetComponent<Facility>()->description = "워프 시스템을 갖춘 가상분열기의 모습입니다.";

            },
            // 업그레이드 비용
                5000000000,
                // 업그레이드 완료 효과음
                SoundType::mitotic_warp);

        AddUpgradePreset(
            // 업그레이드 이름 
            "사이오닉",
            // 업그레이드 설정
            "의문의 물질에서 발견한 에너지를 이용해 김치를 복제합니다.",
            // 업그레이드 효과
            "김치 가상분열기의 kps가 2배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Psionics.txt",
            // 업그레이드 시 동작
            [Facil_Reactor]()
            {
                Facil_Reactor->GetComponent<Facility>()->kps *= 2;
                Facil_Reactor->GetComponent<Facility>()->portraitFile = "Kimchi Disruptor(protoss gate)";
                Facil_Reactor->GetComponent<Facility>()->selectSound = SoundType::mitotic_warpgate_portrait;
                Facil_Reactor->GetComponent<Facility>()->description = "더 이상 이것은 인류의 기술이라 설명할 수 없습니다.";

            },
            // 업그레이드 비용
                10000000000,
                // 업그레이드 완료 효과음
                SoundType::mitotic_psionic);

        AddUpgradePreset(
            // 업그레이드 이름 
            "거대 반응로",
            // 업그레이드 설정
            "이제 김치로 못하는 것은 없습니다. 연비가 대폭 상승!",
            // 업그레이드 효과
            "김치 추진 우주선의 kps가 2배로 증가합니다.",
            // 업그레이드 아이콘 파일 이름
            "Mega reactor.txt",
            // 업그레이드 시 동작
            [Facil_Spaceship]()
            {
                Facil_Spaceship->GetComponent<Facility>()->kps *= 2;
                Facil_Spaceship->GetComponent<Facility>()->portraitFile = "spaceship portrait";
                Facil_Spaceship->GetComponent<Facility>()->selectSound = SoundType::spaceship_portrait;
                Facil_Spaceship->GetComponent<Facility>()->description = "베테랑 함장의 지휘 아래 이 거대 우주선은 무사히 다른 행성에 도달할 수 있을 것입니다.";

            },
            // 업그레이드 비용
                25000000000.0l,
                // 업그레이드 완료 효과음
                SoundType::spaceship_upgrade);



        sort(Upgrade::upgradesLeft.begin(), Upgrade::upgradesLeft.end(), Upgrade::Compare);

    }
    // 뉴스 설정
    {
        NewsText::AddNews(0, "당신의 집은 패가망신했습니다. 아내와 며느리는 도망갔고, 당신은 풀뿌리와 나무껍질로 구차한 생을 연명하고 있습니다.");
        NewsText::AddNews(0, "당신은 김치를 만드려고 합니다. 근데 먹고 싶어하는 사람은 없군요.");
        NewsText::AddNews(5, "당신의 첫 김치는 땅바닥으로 던져졌습니다. 동네 누렁이도 거들떠보지 않네요.");
        NewsText::AddNews(50, "가족들이 마침내 당신이 만든 김치를 먹어보려고 합니다.");
        NewsText::AddNews(100, "당신의 김치가 이웃들 사이에서 유명합니다.");
        NewsText::AddNews(500, "사람들이 당신의 김치에 관해 이야기하기 시작했습니다.");
        NewsText::AddNews(1000, "동네에서 당신의 김치에 대한 소문이 퍼지고 있습니다.");
        NewsText::AddNews(5000, "당신의 김치가 지역 전체에서 유명세를 떨치고 있습니다!");
        NewsText::AddNews(10000, "당신의 김치에 대한 수요가 폭발적으로 증가했습니다.");
        NewsText::AddNews(50000, "당신의 김치에 대한 온라인 몰을 개설했습니다!");
        NewsText::AddNews(70000, "의사들이 삼시세끼 신선한 김치를 섭취하는 것을 권장합니다.");
        NewsText::AddNews(100000, "당신의 김치가 물량이 부족해 웃돈을 얹어 비싸게 팔리고 있습니다.");
        NewsText::AddNews(300000, "한 남자가 은행을 털어서 그 돈으로 김치를 샀습니다.");
        NewsText::AddNews(400000, "전문가들에 따르면 친환경 농장 김치가 청소년들에게 인기몰이를 하고 있다고 합니다.");
        NewsText::AddNews(500000, "당신의 김치가 해외에서도 큰 인기를 끌고 있습니다.");
        NewsText::AddNews(600000, "김치 공장들이 지구 온난화의 주범으로 지목되었습니다!");
        NewsText::AddNews(750000, "김치 공장에서 파업이 일어나 로봇들이 노동력을 대신하고 있습니다.");
        NewsText::AddNews(900000, "알 수 없는 불법 김치들이 발견되었습니다. \"맛은 끔찍합니다.\" 경찰이 말합니다.");
        NewsText::AddNews(1000000, "당신의 김치를 직접 맛보러 사람들이 아주 먼 곳에서도 오고 있습니다.");
        NewsText::AddNews(10000000, "전 세계의 유명인사들이 당신의 김치를 즐겨먹습니다.");
        NewsText::AddNews(1500000, "해외 정치가가 김치 밀수 스캔들에 휘말렸습니다.");
        NewsText::AddNews(20000000, "모 연예인, \"김치를 끊을 수가 없다, 도움이 절실히 필요해.\" 충격 고백!");
        NewsText::AddNews(30000000, "모 연예인, \"김치 덕분에 날씬하고 건강한 상태를 유지할 수 있었다.\" 충격 고백!");
        NewsText::AddNews(50000000, "당신의 김치를 기리기 위한 박물관이 생겼습니다.");
        NewsText::AddNews(100000000, "당신의 김치를 기념하기 위한 국경일이 생겨났습니다.");
        NewsText::AddNews(500000000, "당신의 김치가 세계 불가사의 중 하나에 이름을 올렸습니다.");
        NewsText::AddNews(1000000000, "이제 역사책에는 당신의 김치에 대한 단원이 따로 있습니다.");
        NewsText::AddNews(2000000000, "영화가 배우의 부족으로 취소되었습니다. \"모두가 집에서 김치를 먹고 있어요.\" 감독이 한탄합니다.");
        NewsText::AddNews(3000000000, "새로운 김치 종교가 국가를 휩씁니다.");
        NewsText::AddNews(5000000000, "당신의 김치가 정부의 감시를 받고 있습니다.");
        NewsText::AddNews(7000000000, "아무도 신경쓰지 않는 어떤 퇴보하는 국가에서 김치가 불법으로 지정되어, 정치적 긴장을 발생시키고 있습니다.");
        NewsText::AddNews(10000000000, "온 지구 사람들이 당신의 김치를 즐겨먹습니다!");
        NewsText::AddNews(30000000000, "자원들을 전부 김치로 바꾸는 바람에 국가 금 비축량이 줄어들고 있습니다.");
        NewsText::AddNews(40000000000, "김치가 기존 화폐의 입지를 서서히 잠식하고 있습니다!");
        NewsText::AddNews(50000000000, "이웃 행성에서 온 외계 생명체들이 당신의 김치를 먹어보고 싶어합니다.");
        NewsText::AddNews(70000000000, "국가는 김치를 먹고 싶어 나타나는 불안정한 생명체에 대해서 걱정하고 있습니다.");
        NewsText::AddNews(85000000000, "김치 경제가 빠르게 성장하면서 김치를 담을 안전금고가 매년 수영장 크기의 두 배만큼 늘어나고 있습니다.");
        NewsText::AddNews(100000000000, "우주의 고대 신들이 당신의 김치를 맛보려고 깨어났습니다.");
        NewsText::AddNews(5000000000000, "다른 차원의 존재들이 당신의 김치를 맛보기 위해 나타났습니다.");
        NewsText::AddNews(10000000000000, "당신의 김치가 지각을 갖게 되었습니다.");
        NewsText::AddNews(500000000000000, "온 우주가 원자 단위까지 배추 포기로 바뀌어 버렸습니다.");
        NewsText::AddNews(1000000000000000, "당신의 김치는 우주의 기본 법칙들을 고쳐 쓰고 있습니다.");
        NewsText::AddNews(2000000000000000, "It's time to stop playing.");
    }

    // Window Controler
    WM_ROOT->SetSelfActive(0);
    WS_ROOT->SetSelfActive(0);
    WF_ROOT->SetSelfActive(0);
    WU_ROOT->SetSelfActive(0);

    //화면 선택자 초기화

    WM_ROOT->AddComponent<SelectableWindow>();
    WS_ROOT->AddComponent<SelectableWindow>();
    WF_ROOT->AddComponent<SelectableWindow>();
    WU_ROOT->AddComponent<SelectableWindow>();

    WM_ROOT->GetComponent<SelectableWindow>()->highlightGameObjects.push_back(WM_ROOT);
    WS_ROOT->GetComponent<SelectableWindow>()->highlightGameObjects.push_back(WS_ROOT);
    WF_ROOT->GetComponent<SelectableWindow>()->highlightGameObjects.push_back(WF_ROOT);
    WU_ROOT->GetComponent<SelectableWindow>()->highlightGameObjects.push_back(WU_ROOT);

    displaySelector->AddComponent<Selector>();

    displaySelector->GetComponent<Selector>()->candidates.push_back(WS_ROOT->GetComponent<SelectableWindow>());
    displaySelector->GetComponent<Selector>()->candidates.push_back(WM_ROOT->GetComponent<SelectableWindow>());
    displaySelector->GetComponent<Selector>()->candidates.push_back(WF_ROOT->GetComponent<SelectableWindow>());
    displaySelector->GetComponent<Selector>()->candidates.push_back(WU_ROOT->GetComponent<SelectableWindow>());


    YunutyEngine::YunutyCycle::GetInstance().Play();

    while (!endGame)
    {
        Sleep(100);
    }
}
#endif

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
