#pragma once
#include "DuckPhysics/Core.h"
#include "fm/fmath.h"

#include <vector>

namespace DP_NAMESPACE
{
	struct CollisionResult
	{
		bool collides = false;
		fm::vec3 normal = fm::vec3{ 0,0,0 };
		std::vector<fm::vec3> contactPoints = {};
		float penetrationDepth = 0.f;
		fm::vec3 penetrationAxis = fm::vec3{ 0,0,0 };
	};
}