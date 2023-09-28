#include "GlobalComponent.h"

using namespace YunutyEngine;

std::map<GlobalComponent*, unique_ptr<GlobalComponent>> YunutyEngine::GlobalComponent::globalComponents;
GlobalComponent::GlobalComponent()
{
    globalComponents.insert(make_pair(this, unique_ptr<GlobalComponent>(this)));
    //AddGlobalComponent(this);
}
GlobalComponent::~GlobalComponent()
{
    globalComponents.erase(this);
}
