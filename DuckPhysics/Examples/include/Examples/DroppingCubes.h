#pragma once
#include "ExampleParent.h"

class ExampleDroppingCubes : public ExampleParent
{
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Update(float DeltaTime) override;
};