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
		fm::vec3 location;
	};

	PhysicsObject(const ConstructData& constructData);

	const fm::vec3& GetLocation() { return location; }
	void SetLocation(const fm::vec3& newLocation) { location = newLocation; }
	CollisionShape* GetShape() { return m_shape.get(); }

private:
	std::unique_ptr<CollisionShape> m_shape = nullptr;

	fm::vec3 location;
};

DP_NAMESPACE_END