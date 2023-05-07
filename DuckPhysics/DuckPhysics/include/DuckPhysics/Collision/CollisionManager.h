#pragma once
#include "DuckPhysics/Core.h"
#include "DuckPhysics/PhysicsObject.h"

#include <vector>

DP_NAMESPACE_BEGIN

#define MAXHITLOCATIONCOUNT 2

struct HitData
{
	fm::vec3 location;
	fm::vec3 normal;
};

struct CollisionData
{
	PhysicsObject* selfObject;
	PhysicsObject* otherObject;

	size_t hitDataCount;
	HitData hitDatas[MAXHITLOCATIONCOUNT];
};

struct CollisionManifest
{
	std::vector<CollisionData> collisionDatas = {};
};

class CollisionManager
{
public:


private:
	std::vector<PhysicsObject*> m_physicsObjects;
};

DP_NAMESPACE_END