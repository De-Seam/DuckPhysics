#pragma once
#include "ExampleRenderer.h"

#include "DuckPhysics/PhysicsWorld.h"

class ExampleParent
{
public:
	//Make sure to call these parent functions
	virtual void Initialize();
	virtual void Destroy();
	virtual void Update(float DeltaTime);
	virtual void Draw();

protected:
	DP::PhysicsWorld m_physicsWorld = {};
};