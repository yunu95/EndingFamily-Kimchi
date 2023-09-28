#include "TextImage.h"
#include "BoxImage.h"
#include "AddCategory.h"
#include "Selector.h"
#include "Button.h"

using namespace YunutyEngine;


GameObject* AddCategory(GameObject* Motherbox, string str, Scene* scene, int x, int y, GameObject** nestedBox, Selector* selector)
{
    GameObject* button = scene->AddGameObject(Motherbox);
    GameObject* highlightBox = scene->AddGameObject(Motherbox);
    GameObject* textBox = nullptr;
    (nestedBox ? *nestedBox : textBox) = scene->AddGameObject(button);
    highlightBox->AddComponent<BoxImage>()->SetBoxImage(66, 9, '*');
    (nestedBox ? *nestedBox : textBox)->AddComponent<TextImage>()->SetText(60, 7, str);
    button->GetTransform()->position.x += x;
    button->GetTransform()->position.y += y;
    if (selector)
    {
        button->AddComponent<Button>();
        button->GetComponent<Button>()->highlightGameObjects.push_back(highlightBox);
        selector->candidates.push_back(button->GetComponent<Button>());
    }
    return button;
}


GameObject* AddFlexibleCategory(GameObject* Motherbox, string str, Scene* scene, int width, int height, int x, int y, Selector* selector, GameObject** p_nestedText )
{
    GameObject* button = scene->AddGameObject(Motherbox);
    GameObject* highlightBox = scene->AddGameObject(button);
    GameObject* nestedText = scene->AddGameObject(button);
    highlightBox->AddComponent<BoxImage>()->SetBoxImage(width, height, '*');
    nestedText->AddComponent<TextImage>()->SetText(width - 2, height - 2, str);
    if (p_nestedText)
        *p_nestedText = nestedText;

    button->GetTransform()->position.x += x;
    button->GetTransform()->position.y += y;

    if (selector)
    {
        button->AddComponent<Button>();
        button->GetComponent<Button>()->highlightGameObjects.push_back(highlightBox);
        button->GetComponent<Button>()->sound = SoundType::ButtonSound;
        selector->candidates.push_back(button->GetComponent<Button>());
    }

    return button;
}