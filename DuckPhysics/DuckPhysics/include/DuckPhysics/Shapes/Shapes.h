#pragma once
#include "DuckPhysics/Core.h"
#include "DuckPhysics/Collision/CollisionResult.h"
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
		fm::vec3 axis[3];

		void UpdateAxes()
		{
			fm::mat3 rotMatrix = fm::to_mat3(rotation);
			axis[0] = fm::vec3{ 1, 0, 0 } *rotMatrix; // x-axis
			axis[1] = fm::vec3{ 0, 1, 0 } *rotMatrix; // y-axis
			axis[2] = fm::vec3{ 0, 0, 1 } *rotMatrix; // z-axis
		}
	};

	bool Collides(fm::vec3 locationA, SphereShape sphereA, fm::vec3 locationB, SphereShape sphereB);
	bool Collides(fm::vec3 locationA, AABBShape boxA, fm::vec3 locationB, AABBShape boxB);
	CollisionResult Collides(fm::vec3 locationA, BoxShape boxA, fm::vec3 locationB, BoxShape boxB);

}