#pragma once
#include "DuckPhysics/Core.h"
#include "CollisionShape.h"

DP_NAMESPACE_BEGIN

class CollisionSphereShape : public CollisionShape
{
public:

protected:
	SphereShape sphere;
};

DP_NAMESPACE_END