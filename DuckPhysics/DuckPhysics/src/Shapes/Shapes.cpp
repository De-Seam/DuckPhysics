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
		AABB aabbA = { locationA - boxA.halfExtents, locationA + boxA.halfExtents };
		AABB aabbB = { locationB - boxB.halfExtents, locationB + boxB.halfExtents };
		return aabbA.Collides(aabbB);
	}

	fm::vec3 FindReferenceFaceNormal(BoxShape* referenceBox, const fm::vec3& minPenetrationAxis)
	{
		// Transform the minimum penetration axis into the local coordinate frame of the reference box
		fm::quat invRefRotation = fm::quat(-referenceBox->rotation.x, -referenceBox->rotation.y, -referenceBox->rotation.z, referenceBox->rotation.w);
		fm::vec3 localMinPenetrationAxis = invRefRotation.rotate(minPenetrationAxis);

		// Find the index of the face with the normal most closely aligned with the local minimum penetration axis
		int maxIndex = 0;
		float maxDotProduct = -1.0f;
		for (int i = 0; i < 3; ++i) {
			float dotProduct = std::abs(localMinPenetrationAxis[i]);
			if (dotProduct > maxDotProduct) {
				maxDotProduct = dotProduct;
				maxIndex = i;
			}
		}

		// Create the local normal of the reference face
		fm::vec3 localFaceNormal(0, 0, 0);
		localFaceNormal[maxIndex] = (localMinPenetrationAxis[maxIndex] > 0) ? 1.0f : -1.0f;

		// Transform the local face normal back into the world coordinate frame
		fm::vec3 worldFaceNormal = referenceBox->rotation.rotate(localFaceNormal);
		return worldFaceNormal;
	}

	std::vector<fm::vec3> GetIncidentBoxVertices(fm::vec3 location, BoxShape* incidentBox)
	{
		std::vector<fm::vec3> incidentVertices(8);

		// The local vertices of the box, assuming the box's center is at the origin.
		fm::vec3 localVertices[] = {
			fm::vec3(-incidentBox->halfExtents.x, -incidentBox->halfExtents.y, -incidentBox->halfExtents.z),
			fm::vec3(-incidentBox->halfExtents.x, -incidentBox->halfExtents.y,  incidentBox->halfExtents.z),
			fm::vec3(-incidentBox->halfExtents.x,  incidentBox->halfExtents.y, -incidentBox->halfExtents.z),
			fm::vec3(-incidentBox->halfExtents.x,  incidentBox->halfExtents.y,  incidentBox->halfExtents.z),
			fm::vec3(incidentBox->halfExtents.x, -incidentBox->halfExtents.y, -incidentBox->halfExtents.z),
			fm::vec3(incidentBox->halfExtents.x, -incidentBox->halfExtents.y,  incidentBox->halfExtents.z),
			fm::vec3(incidentBox->halfExtents.x,  incidentBox->halfExtents.y, -incidentBox->halfExtents.z),
			fm::vec3(incidentBox->halfExtents.x,  incidentBox->halfExtents.y,  incidentBox->halfExtents.z)
		};

		// Transform the local vertices into world coordinates.
		for (int i = 0; i < 8; ++i) {
			incidentVertices[i] = location + incidentBox->rotation.rotate(localVertices[i]);
		}

		return incidentVertices;
	}

	std::vector<fm::vec3> TransformVertices(const std::vector<fm::vec3>& incidentVertices, const fm::quat& referenceRotation)
	{
		std::vector<fm::vec3> transformedVertices(incidentVertices.size());

		// Calculate the inverse of the reference box's rotation quaternion.
		fm::quat invRefRotation = fm::quat(-referenceRotation.x, -referenceRotation.y, -referenceRotation.z, referenceRotation.w);

		// Transform the incident vertices into the reference box's coordinate frame.
		for (size_t i = 0; i < incidentVertices.size(); ++i) {
			transformedVertices[i] = invRefRotation.rotate(incidentVertices[i]);
		}

		return transformedVertices;
	}

	std::vector<fm::vec3> ClipVerticesAgainstReferenceFace(const std::vector<fm::vec3>& transformedIncidentVertices, const fm::vec3& referenceFaceNormal, BoxShape* referenceBox)
	{
		std::vector<fm::vec3> clippedVertices;

		// Calculate the reference face's plane constant.
		float planeConstant = referenceFaceNormal.dot(referenceBox->halfExtents);

		// Iterate over the incident vertices and clip them against the reference face.
		for (const fm::vec3& vertex : transformedIncidentVertices) {
			float signedDistance = referenceFaceNormal.dot(vertex) - planeConstant;

			// Add the vertex to the clipped vertices if it lies on or inside the reference face.
			if (signedDistance <= 0) {
				clippedVertices.push_back(vertex);
			}
		}

		return clippedVertices;
	}

	std::pair<float, float> projectOntoAxis(const BoxShape& box, const fm::vec3& axis, const fm::vec3& position)
	{
		// compute the corners of the box
		fm::vec3 corners[8] = {
			box.halfExtents * fm::vec3{-1, -1, -1},
			box.halfExtents * fm::vec3{-1, -1,  1},
			box.halfExtents * fm::vec3{-1,  1, -1},
			box.halfExtents * fm::vec3{-1,  1,  1},
			box.halfExtents * fm::vec3{ 1, -1, -1},
			box.halfExtents * fm::vec3{ 1, -1,  1},
			box.halfExtents * fm::vec3{ 1,  1, -1},
			box.halfExtents * fm::vec3{ 1,  1,  1}
		};

		// rotate the corners according to the box's orientation and add the position
		for (auto& corner : corners)
			corner = position + corner * fm::to_mat3(box.rotation);

		// project the corners onto the axis and find min and max projection
		float minProj = std::numeric_limits<float>::infinity();
		float maxProj = -std::numeric_limits<float>::infinity();
		for (const auto& corner : corners)
		{
			float proj = corner.dot(axis);
			minProj = std::min(minProj, proj);
			maxProj = std::max(maxProj, proj);
		}

		// return the min and max projection as a pair
		return std::make_pair(minProj, maxProj);
	}

	bool overlaps(float minProjA, float maxProjA, float minProjB, float maxProjB)
	{
		// Two intervals overlap if the start of one is less than the end of the other and vice versa.
		return minProjA <= maxProjB && minProjB <= maxProjA;
	}


	CollisionResult Collides(fm::vec3 locationA, BoxShape boxA, fm::vec3 locationB, BoxShape boxB)
	{
		boxA.UpdateAxes();
		boxB.UpdateAxes();

		CollisionResult result;

		fm::vec3 T = locationB - locationA;

		// Compute rotation matrix expressing box B in box A's coordinate frame
		fm::mat3 R = fm::to_mat3(boxA.rotation) * fm::to_mat3(boxB.rotation).transpose();

		// Compute translation vector T, in box A's coordinates
		T = T * fm::to_mat3(boxA.rotation.conjugate());

		fm::mat3 AbsR;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				AbsR[i][j] = std::abs(R[i][j]) + std::numeric_limits<float>::epsilon();

		float minOverlap = std::numeric_limits<float>::infinity();
		fm::vec3 minPenetrationAxis;

		// Test axes of box A
		for (int i = 0; i < 3; ++i)
		{
			float ra = boxA.halfExtents[i];
			float rb = boxB.halfExtents[0] * AbsR[i][0] + boxB.halfExtents[1] * AbsR[i][1] + boxB.halfExtents[2] * AbsR[i][2];
			if (std::abs(T[i]) > ra + rb)
			{
				return result;
			}

			float overlap = ra + rb - std::abs(T[i]);
			if (overlap < minOverlap)
			{
				minOverlap = overlap;
				minPenetrationAxis = boxA.axis[i];
			}
		}

		// Test axes of box B
		for (int i = 0; i < 3; ++i)
		{
			float ra = boxA.halfExtents[0] * AbsR[0][i] + boxA.halfExtents[1] * AbsR[1][i] + boxA.halfExtents[2] * AbsR[2][i];
			float rb = boxB.halfExtents[i];
			if (std::abs(T[0] * R[0][i] + T[1] * R[1][i] + T[2] * R[2][i]) > ra + rb)
			{
				return result;
			}

			float overlap = ra + rb - std::abs(T[0] * R[0][i] + T[1] * R[1][i] + T[2] * R[2][i]);
			if (overlap < minOverlap)
			{
				minOverlap = overlap;
				minPenetrationAxis = boxB.axis[i];
			}
		}

		// Test cross-product axes
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				// Compute the axis to test
				fm::vec3 axis = boxA.axis[i].cross(boxB.axis[j]);

				// Project both boxes onto this axis
				auto [minProjA, maxProjA] = projectOntoAxis(boxA, axis, locationA);
				auto [minProjB, maxProjB] = projectOntoAxis(boxB, axis, locationB);

				// Test if the projections overlap
				if (!overlaps(minProjA, maxProjA, minProjB, maxProjB))
				{
					return result; // no overlap means there is a separating axis and thus no collision
				}

				// Calculate the overlap
				float overlap = std::min(maxProjA, maxProjB) - std::max(minProjA, minProjB);
				if (overlap > 0.f && overlap < minOverlap)
				{
					minOverlap = overlap;
					minPenetrationAxis = axis;
				}
			}
		}

		// If no separating axis found, the boxes must be intersecting
		if (minOverlap < std::numeric_limits<float>::infinity())
		{
			result.collides = true;
			result.penetrationDepth = minOverlap;
			result.penetrationAxis = minPenetrationAxis;
		}
		return result;
	}



}

