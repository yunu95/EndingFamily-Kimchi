#pragma once
#include "Object.h"
#include <vector>
#include <set>
#include <memory>
#include <map>

using namespace std;

namespace YunutyEngine
{
    // Global components are always called before other components.
    class GlobalComponent :
        public Object
    {
        friend class YunutyCycle;
    private:
        static std::map<GlobalComponent*,unique_ptr<GlobalComponent>> globalComponents;
    protected:
        GlobalComponent();
        virtual void Update() {};
        virtual void FixedUpdate() {};
    public:
        ~GlobalComponent();
    };
}

