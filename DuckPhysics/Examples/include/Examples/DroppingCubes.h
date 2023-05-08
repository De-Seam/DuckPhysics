#pragma once
#include "ExampleParent.h"

#include <DuckPhysics/PhysicsWorld.h>

class ExampleDroppingCubes : public ExampleParent
{
public:
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Update(float DeltaTime) override;
	virtual void Draw() override;

private:
	DP::PhysicsWorld m_physicsWorld = {};
};