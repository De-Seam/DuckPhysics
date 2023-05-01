#pragma once
#include "DuckPhysics/Core.h"
#include "CollisionShape.h"

DP_NAMESPACE_BEGIN

class CollisionBoxShape : public CollisionShape
{
	BoxShape box;
};

DP_NAMESPACE_END