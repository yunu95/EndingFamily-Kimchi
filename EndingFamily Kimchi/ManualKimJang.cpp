#include "ManualKimJang.h"
#include "GameInfo.h"

void ManualKimJang::Update()
{
    if (YunutyEngine::Input::isKeyPushed(YunutyEngine::KeyCode::Return))
        GameInfo::kimchis += 1;
}
