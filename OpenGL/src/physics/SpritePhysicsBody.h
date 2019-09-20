#pragma once
#include "Sprite.h"

class SpritePhysicsBody : public Sprite {
private:
	float mass;
	glm::vec3 gravitationalAcceleration;
	glm::vec3 linearVelocity;
	glm::vec3 angularVelocity;
	glm::vec3 force;
	glm::vec3 torque;
	float momentOfInertia;
	float lastDeltaT;
public:
	SpritePhysicsBody();
	SpritePhysicsBody(glm::vec3 rot, glm::vec3 trans, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity);
	~SpritePhysicsBody();

	void Update(float delta);
	void ReverseLastUpdate(float delta);

	void Stop();

	void Jump(glm::vec3 vel);

	glm::vec3 GetLinearAcceleration();
	glm::vec3 GetLinearAccelerationWithoutGravity();
	glm::vec3 GetLinearVelocity();

	inline const glm::vec3& GetVelocity() const { return linearVelocity; }
};