#include "Examples/DroppingCubes.h"
#include <Examples/ExampleRenderer.h>

#include <DuckPhysics/CollisionShapes/CollisionBoxShape.h>

void ExampleDroppingCubes::Initialize()
{
	//m_physicsWorld.;

	ExampleParent::Initialize();

	DP::CollisionBoxShape* boxShape = m_physicsWorld.CreateShape<DP::CollisionBoxShape>();
	boxShape->boxShape.halfExtents = { 2.f, 2.f, 2.f };
	boxShape->boxShape.rotation = { fm::vec3(0.5f, 0.f, 0.f) };
	DP::PhysicsObject::ConstructData constructData;
	constructData.shape = boxShape;
	constructData.location = { 1.f, 0.f, 0.f };
	DP::PhysicsObject* objectA = m_physicsWorld.CreatePhysicsObject<DP::PhysicsObject>(constructData);
	constructData.location = { 4.f, 0.f, 0.f };
	m_physicsWorld.CreatePhysicsObject<DP::PhysicsObject>(constructData);
}

void ExampleDroppingCubes::Destroy()
{
	ExampleParent::Destroy();
}

void ExampleDroppingCubes::Update(float DeltaTime)
{
	ExampleParent::Update(DeltaTime);
}

void ExampleDroppingCubes::Draw()
{
	// Create the shader program
	static GLuint shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

	// Create the cube VAO
	static GLuint cubeVAO = CreateCubeVAO();

	// Set up the camera matrices
	static glm::mat4 projection = glm::perspective(fm::to_radians(70.f), static_cast<float>(SCREENWIDTH) / static_cast<float>(SCREENHEIGHT), 0.1f, 1000.0f);
	static glm::mat4 view = glm::lookAt(glm::vec3(0.0f, -20.f, 0.f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.f, 1.0f));

	// Set the projection and view matrices in the shader
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

	const std::vector<DP::PhysicsObject*>& physicsObjects = m_physicsWorld.GetPhysicsObjects();
	for (DP::PhysicsObject* object : physicsObjects)
	{
		DP::CollisionShape* shape = object->GetShape();
		const fm::vec3& location = object->GetLocation();

		DP::CollisionBoxShape* boxShape = dynamic_cast<DP::CollisionBoxShape*>(shape);
		if (!boxShape)
			continue;

		fm::vec3& halfExtents = boxShape->boxShape.halfExtents;
		fm::quat& rotation = boxShape->boxShape.rotation;

		fm::vec4 color = { 1.f,1.f,1.f,1.f };

		for (DP::PhysicsObject* otherObject : physicsObjects)
		{
			if (otherObject == object)
				continue;

			DP::CollisionResult collisionResult = object->Collides(otherObject);
			if (collisionResult.collides)
				color = { 1.f,0.f,0.f,1.f };

			for (fm::vec3& contactPoint : collisionResult.contactPoints)
				DrawCube(shaderProgram, cubeVAO,
					contactPoint,
					fm::quat{fm::vec3(0.f)},
					fm::vec3(0.5f),
					fm::vec4(0.f, 0.f, 1.f, 1.f));


		}

		// Draw the cube
		DrawCube(shaderProgram, cubeVAO,
			location,
			rotation,
			halfExtents * 2.f,
			color);
	}
}
