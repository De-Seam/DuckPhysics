#pragma once
#include "DuckPhysics/Core.h"
#include "DuckPhysics/PhysicsObject.h"

#include <vector>

DP_NAMESPACE_BEGIN

class PhysicsWorld
{
private: //Deleted operators
	PhysicsWorld(const PhysicsWorld&);
	PhysicsWorld& operator=(const PhysicsWorld&);
public:
	PhysicsWorld();

	template<typename TCollisionShape, typename... TArgs>
	TCollisionShape* CreateShape(TArgs&&... args);

	template<typename TPhysicsObject, typename... TArgs>
	TPhysicsObject* CreatePhysicsObject(TArgs&&... args);

	void Update(float DeltaTime);

private:
	std::vector<PhysicsObject*> m_physicsObjects;
	std::vector<CollisionShape*> m_shapes;
};


template<typename TCollisionShape, typename... TArgs>
inline TCollisionShape* PhysicsWorld::CreateShape(TArgs&&... args)
{
	//TODO: Custom allocator
	TCollisionShape* shape = new TCollisionShape(std::forward<TArgs>(args)...);
	m_shapes.emplace_back(shape);
	return shape;
}

template<typename TPhysicsObject, typename ...TArgs>
inline TPhysicsObject* PhysicsWorld::CreatePhysicsObject(TArgs && ...args)
{
	//TODO: Custom allocator
	TPhysicsObject object = new TPhysicsObject(args);
	m_physicsObjects.emplace_back(object);

	//TODO: Acceleration structure

	return object;
}

DP_NAMESPACE_END