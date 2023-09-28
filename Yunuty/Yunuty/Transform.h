#pragma once
#include "Component.h"
#include "Vector3.h"

namespace YunutyEngine
{
    class GameObject;
    class Transform :
        public Component
    {
    private:
	public:
		Vector3d position = Vector3d();
        Vector3d GetWorldPosition();
    };
}
