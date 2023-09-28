#pragma once
#include "Object.h"
#include "EKeycode.h"
#include "GlobalComponent.h"

// À¯¿ëÇÔ
// GetAsyncKeyState
namespace YunutyEngine
{
    class Input :
        public GlobalComponent
    {
    private:
        static unique_ptr<Input> instance;
    protected:
        virtual bool m_isKeyDown(KeyCode keyCode) = 0;
        virtual bool m_isKeyPushed(KeyCode keyCode) = 0;
    public:
        template<typename InputType>
        static void SetInput()
        {
            static_assert(is_base_of<Input, InputType>::value, "input must be a derived class of Input superClass");
            auto ptr = new InputType();
            instance = unique_ptr<Input>(ptr);
        }
        static bool isKeyDown(KeyCode keyCode);
        static bool isKeyPushed(KeyCode keyCode);
    };
}
