#pragma once
#include "DuckPhysics/Core.h"

DP_NAMESPACE_BEGIN

struct Shape;

class PhysicsObject
{
private: //Deleted operators
	PhysicsObject(const PhysicsObject&);
	PhysicsObject& operator=(const PhysicsObject&);

public:
	struct ConstructData
	{
		Shape* shape;
	};

	PhysicsObject(const ConstructData& constructData);



private:
	Shape* m_shape = nullptr;
};

DP_NAMESPACE_END