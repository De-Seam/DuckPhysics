#include "DuckPhysics/CollisionShapes/CollisionBoxShape.h"
#include "DuckPhysics/Shapes/Shapes.h"

namespace DP
{


CollisionResult CollisionBoxShape::Collides(fm::vec3 location, fm::vec3 otherLocation, CollisionShape* other)
{
	CollisionResult collisionResult = {};
	switch(other->shapeType)
	{
	case ShapeType::CollisionBoxShape:
	{
		CollisionBoxShape* otherBoxShape = reinterpret_cast<CollisionBoxShape*>(other);
		collisionResult = DP::Collides(location, boxShape, otherLocation, otherBoxShape->boxShape);
	}
		break;
	case ShapeType::CollisionSphereShape:
		std::cout << "Box Sphere not implemented yet \n";
		break;
	case ShapeType::Invalid:
		std::cout << "Invalid shape type \n";
		break;
	}
	return collisionResult;
}

void CollisionBoxShape::CalculateBoundingSphere()
{
}

}