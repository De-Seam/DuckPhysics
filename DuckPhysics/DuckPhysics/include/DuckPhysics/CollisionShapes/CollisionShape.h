#pragma once
#include "DuckPhysics/Core.h"
#include "DuckPhysics/Shapes/Shapes.h"
#include "fm/fmath.h"

DP_NAMESPACE_BEGIN

class CollisionShape
{
private: //Deleted operators
	CollisionShape(const CollisionShape&);
	CollisionShape& operator=(const CollisionShape&);

public:



protected:
	SphereShape boundingSphere;
};

DP_NAMESPACE_END