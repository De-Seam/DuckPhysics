#pragma once
#include "DuckPhysics/Core.h"
#include "DuckPhysics/Shapes/Shapes.h"
#include "fm/fmath.h"

DP_NAMESPACE_BEGIN

enum class ShapeType
{
	Invalid,
	CollisionBoxShape,
	CollisionSphereShape
};

class CollisionShape
{
private: //Deleted operators
	CollisionShape(const CollisionShape&);
	CollisionShape& operator=(const CollisionShape&);

public:
	virtual ~CollisionShape() = default;
	CollisionShape() = default;

	virtual CollisionResult Collides(fm::vec3 location, fm::vec3 otherLocation, CollisionShape* other) = 0;

	virtual void CalculateBoundingSphere() = 0;

	ShapeType shapeType = ShapeType::Invalid;
protected:
	SphereShape boundingSphere;
};

DP_NAMESPACE_END