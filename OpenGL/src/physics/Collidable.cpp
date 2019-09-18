#include "Collidable.h"

Collidable::Collidable()
	: AxisAlignedBoundingBox(), PhysicsBody()
{

}

Collidable::Collidable(const glm::vec3& minCorner, const glm::vec3& maxCorner, type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity)
	: AxisAlignedBoundingBox(minCorner, maxCorner), PhysicsBody(type, dir, name, rotation, translation, m, linearVel, angularVel, f, t, MOI, gravity)
{
}

Collidable::Collidable(const glm::vec3& minCorner, const glm::vec3& maxCorner, type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, const std::string& texDir, const std::string& texName, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity)
	: AxisAlignedBoundingBox(minCorner, maxCorner), PhysicsBody(type, dir, name, rotation, translation, texDir, texName, m, linearVel, angularVel, f, t, MOI, gravity)
{

}

//Collidable::Collidable(type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity)
//	: AxisAlignedBoundingBox(minCorner, maxCorner), PhysicsBody(type, dir, name, rotation, translation, m, linearVel, angularVel, f, t, MOI, gravity)
//{
//}
//
//Collidable::Collidable(type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, const std::string& texDir, const std::string& texName, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity)
//	: AxisAlignedBoundingBox(minCorner, maxCorner), PhysicsBody(type, dir, name, rotation, translation, texDir, texName, m, linearVel, angularVel, f, t, MOI, gravity)
//{
//
//}

Collidable::~Collidable()
{
}
