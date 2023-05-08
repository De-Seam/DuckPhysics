#pragma once
#include "DuckPhysics/Core.h"
#include "CollisionShape.h"

DP_NAMESPACE_BEGIN

class CollisionBoxShape : public CollisionShape
{
public:
	BoxShape box;
};

DP_NAMESPACE_END