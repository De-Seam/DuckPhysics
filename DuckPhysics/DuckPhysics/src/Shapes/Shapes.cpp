#include "DuckPhysics/Shapes/Shapes.h"

namespace DP
{
	bool AABB::Collides(const AABB& other)
	{
		return 
		(min.x <= other.max.x) && (max.x >= other.min.x) &&
		(min.y <= other.max.y) && (max.y >= other.min.y) &&
		(min.z <= other.max.z) && (max.z >= other.min.z);
	}

	bool Collides(fm::vec3 locationA, SphereShape sphereA, fm::vec3 locationB, SphereShape sphereB)
	{
		fm::vec3 difference = locationB - locationA;
		float distance2 = difference.dot(difference);

		float distanceToCheck = (sphereA.radius + sphereB.radius) * (sphereA.radius + sphereB.radius);
		return distance2 < distanceToCheck;
	}

	bool Collides(fm::vec3 locationA, AABBShape boxA, fm::vec3 locationB, AABBShape boxB)
	{
		AABB aabbA = {locationA - boxA.halfExtents, locationA + boxA.halfExtents};
		AABB aabbB = {locationB - boxB.halfExtents, locationB + boxB.halfExtents};
		return aabbA.Collides(aabbB);
	}

}