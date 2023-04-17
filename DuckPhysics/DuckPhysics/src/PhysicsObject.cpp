#include "DuckPhysics/Core.h"
#include "DuckPhysics/PhysicsObject.h"

DP_NAMESPACE_BEGIN

PhysicsObject::PhysicsObject(const ConstructData& constructData)
	: m_shape(constructData.shape)
{

}

DP_NAMESPACE_END

