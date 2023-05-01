#include "DuckPhysics/Shapes/Shapes.h"

#include <functional>

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

bool Collides(fm::vec3 locationA, BoxShape boxA, fm::vec3 locationB, BoxShape boxB)
{
	// Compute the rotation matrix expressing box B in box A's coordinate frame.
	fm::quat qA_inv = fm::quat(-boxA.rotation.x, -boxA.rotation.y, -boxA.rotation.z, boxA.rotation.w);
	fm::quat qB = boxB.rotation;
	fm::quat q = qA_inv * qB;
	fm::vec4 columns[3] = 
	{
		fm::vec4(q.w + q.x, q.z - q.y, -q.w + q.x, -q.z - q.y),
		fm::vec4(-q.z + q.y, q.w + q.x, q.z + q.y, -q.w + q.x),
		fm::vec4(q.y - q.x, -q.y - q.x, q.w + q.z, -q.w + q.z)
	};

	// Transform the position of box B into box A's coordinate frame.
	fm::vec3 t = locationB - locationA;
	t = qA_inv.rotate(t);

	// Half extents of both boxes.
	__m128 half_extents_A = boxA.halfExtents.as_sse();
	__m128 half_extents_B = boxB.halfExtents.as_sse();

	// Absolute value of rotation matrix.
	__m128 abs_columns[3] = 
	{
		_mm_add_ps(_mm_and_ps(columns[0].as_sse(), _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF))),
				   _mm_set1_ps(1e-6f)),
		_mm_add_ps(_mm_and_ps(columns[1].as_sse(), _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF))),
				   _mm_set1_ps(1e-6f)),
		_mm_add_ps(_mm_and_ps(columns[2].as_sse(), _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF))),
				   _mm_set1_ps(1e-6f))
	};

	// Check for axis separation.
	for (int i = 0; i < 3; ++i) 
	{
		__m128 axis_half_extents_A;
		switch (i) {
			case 0:
				axis_half_extents_A = _mm_shuffle_ps(half_extents_A, half_extents_A, _MM_SHUFFLE(0, 0, 0, 0));
				break;
			case 1:
				axis_half_extents_A = _mm_shuffle_ps(half_extents_A, half_extents_A, _MM_SHUFFLE(1, 1, 1, 1));
				break;
			case 2:
				axis_half_extents_A = _mm_shuffle_ps(half_extents_A, half_extents_A, _MM_SHUFFLE(2, 2, 2, 2));
				break;
			default:
				// Handle an error or throw an exception if i is outside the expected range of 0 to 2.
				break;
		}
		__m128 axis_half_extents_B = _mm_dp_ps(half_extents_B, abs_columns[i], 0x71);
		__m128 combined_half_extents = _mm_add_ps(axis_half_extents_A, axis_half_extents_B);
		float separation = std::abs(t[i]);
		if (separation > _mm_cvtss_f32(combined_half_extents)) 
			return false;
	}

	// Check for cross product axes.
	for (int i = 0; i < 3; ++i) 
	{
		for (int j = 0; j < 3; ++j) 
		{
			__m128 axis_half_extents_A = _mm_dp_ps(half_extents_A, abs_columns[j], 0x71);
			__m128 axis_half_extents_B = _mm_dp_ps(half_extents_B, abs_columns[(i + 2) % 3], 0x71);
			axis_half_extents_B = _mm_add_ps(axis_half_extents_B, _mm_dp_ps(half_extents_B, abs_columns[(i + 1) % 3], 0x71));
			__m128 combined_half_extents = _mm_add_ps(axis_half_extents_A, axis_half_extents_B);

			float separation = std::abs(t[(i + 1) % 3] * columns[j][(i + 2) % 3] - t[(i + 2) % 3] * columns[j][(i + 1) % 3]);
			if (separation > _mm_cvtss_f32(combined_half_extents)) 
				return false;
		}
	}

	return true;
}

}

