#include "Input.h"

using namespace YunutyEngine;

unique_ptr<Input> YunutyEngine::Input::instance = nullptr;

bool YunutyEngine::Input::isKeyDown(KeyCode keyCode)
{
    return instance->m_isKeyDown(keyCode);
}
bool YunutyEngine::Input::isKeyPushed(KeyCode keyCode)
{
    return instance->m_isKeyPushed(keyCode);
}
