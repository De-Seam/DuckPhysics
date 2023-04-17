#pragma once
#include "DuckPhysics/Core.h"
#include "fm/fmath.h"

DP_NAMESPACE_BEGIN

struct AABB
{
	fm::vec3 min, max;

	bool Collides(const AABB& other);
};

//Locations are not included, as shapes don't inheritely have locations. Only bounds. Locations are provided by the functions
struct SphereShape
{
	float radius;
};

struct AABBShape
{
	fm::vec3 halfExtents;
	
	//min = location - halfExtents
	//max = location + halfExtents
};

bool Collides(fm::vec3 locationA, SphereShape sphereA, fm::vec3 locationB, SphereShape sphereB);
bool Collides(fm::vec3 locationA, AABBShape boxA, fm::vec3 locationB, AABBShape boxB);

DP_NAMESPACE_END