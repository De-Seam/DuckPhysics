#pragma once
#include "DuckPhysics/Core.h"
#include "CollisionShape.h"

DP_NAMESPACE_BEGIN

class CollisionBoxShape : public CollisionShape
{
public:
	CollisionBoxShape()
	{
		shapeType = ShapeType::CollisionBoxShape;
	}

	virtual CollisionResult Collides(fm::vec3 location, fm::vec3 otherLocation, CollisionShape* other);

	virtual void CalculateBoundingSphere();

	BoxShape boxShape;

};

DP_NAMESPACE_END