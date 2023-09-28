#include "Transform.h"
#include "GameObject.h"

using namespace YunutyEngine;

Vector3d YunutyEngine::Transform::GetWorldPosition()
{
	if (GetGameObject()->GetParentGameObject() == nullptr)
		return position;
	Vector3d ret;
	ret.x = position.x + GetGameObject()->GetParentGameObject()->GetTransform()->GetWorldPosition().x;
	ret.y = position.y + GetGameObject()->GetParentGameObject()->GetTransform()->GetWorldPosition().y;
	return ret;
}