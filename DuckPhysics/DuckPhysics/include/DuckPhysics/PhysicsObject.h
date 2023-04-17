#pragma once
#include "DuckPhysics/Core.h"
#include "CollisionShapes/CollisionShape.h"

#include <memory>

DP_NAMESPACE_BEGIN

class PhysicsObject
{
private: //Deleted operators
	PhysicsObject(const PhysicsObject&);
	PhysicsObject& operator=(const PhysicsObject&);

public:
	struct ConstructData
	{
		CollisionShape* shape;
	};

	PhysicsObject(const ConstructData& constructData);



private:
	std::unique_ptr<CollisionShape> m_shape = nullptr;
};

DP_NAMESPACE_END