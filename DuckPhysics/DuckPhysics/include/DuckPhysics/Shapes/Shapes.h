#pragma once
#include "DuckPhysics/Core.h"
#include "fm/fmath.h"

#include <vector>

namespace DP
{

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

struct BoxShape
{
	fm::vec3 halfExtents;
	fm::quat rotation;
};

struct CollisionResult
{
	bool collides = false;
	fm::vec3 normal = fm::vec3{0,0,0};
	std::vector<fm::vec3> contactPoints = {};
};

bool Collides(fm::vec3 locationA, SphereShape sphereA, fm::vec3 locationB, SphereShape sphereB);
bool Collides(fm::vec3 locationA, AABBShape boxA, fm::vec3 locationB, AABBShape boxB);
CollisionResult Collides(fm::vec3 locationA, BoxShape boxA, fm::vec3 locationB, BoxShape boxB);

}