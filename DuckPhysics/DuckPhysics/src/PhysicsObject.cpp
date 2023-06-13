#include "DuckPhysics/Core.h"
#include "DuckPhysics/PhysicsObject.h"

namespace DP_NAMESPACE
{

	PhysicsObject::PhysicsObject(const ConstructData& constructData)
		: m_shape(constructData.shape), location(constructData.location)
	{

	}

	CollisionResult PhysicsObject::Collides(PhysicsObject* other)
	{
		return m_shape->Collides(location, other->location, other->m_shape.get());
	}

}

