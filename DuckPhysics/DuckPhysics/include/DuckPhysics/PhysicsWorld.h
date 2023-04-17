#pragma once
#include "DuckPhysics/Core.h"
#include "DuckPhysics/PhysicsObject.h"

#include <vector>

DP_NAMESPACE_BEGIN

class PhysicsObject;

class PhysicsWorld
{
private: //Deleted operators
	PhysicsWorld(const PhysicsWorld&);
	PhysicsWorld& operator=(const PhysicsWorld&);
public:
	PhysicsWorld();

	void Update(float DeltaTime);

private:
	std::vector<PhysicsObject*> m_physicsObjects;
};

DP_NAMESPACE_END