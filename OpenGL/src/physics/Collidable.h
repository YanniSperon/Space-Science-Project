#pragma once
#include "AxisAlignedBoundingBox.h"
#include "PhysicsBody.h"

class Collidable : public AxisAlignedBoundingBox, public PhysicsBody {
private:

public:
	Collidable();
	Collidable(const glm::vec3& minCorner, const glm::vec3& maxCorner, type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity);
	Collidable(const glm::vec3& minCorner, const glm::vec3& maxCorner, type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, const std::string& texDir, const std::string& texName, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity);
	/*Collidable(type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity);
	Collidable(type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, const std::string& texDir, const std::string& texName, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity);*/
	~Collidable();
	

};