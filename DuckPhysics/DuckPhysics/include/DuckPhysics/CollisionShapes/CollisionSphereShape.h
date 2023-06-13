#pragma once
#include "DuckPhysics/Core.h"
#include "CollisionShape.h"

DP_NAMESPACE_BEGIN

class CollisionSphereShape : public CollisionShape
{
public:
	CollisionSphereShape()
	{
		shapeType = ShapeType::CollisionSphereShape;
	}

protected:
	SphereShape sphere;
};

DP_NAMESPACE_END