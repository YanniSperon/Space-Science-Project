#pragma once
#include "Object.h"
#include "glm/glm.hpp"

class PhysicsBody : public Object {
private:
	float mass;
	glm::vec3 gravitationalAcceleration;
	glm::vec3 linearVelocity;
	glm::vec3 angularVelocity;
	glm::vec3 force;
	glm::vec3 torque;
	float momentOfInertia;
public:
	PhysicsBody();
	PhysicsBody(type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity);
	PhysicsBody(type type, std::string dir, std::string name, glm::vec3 rotation, glm::vec3 translation, const std::string& texDir, const std::string& texName, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity);

	void Update(float delta);

	void Stop();

	glm::vec3 GetLinearAcceleration();
	glm::vec3 GetLinearAccelerationWithoutGravity();
	glm::vec3 GetLinearVelocity();

	inline const glm::vec3& GetVelocity() const { return linearVelocity; }
};