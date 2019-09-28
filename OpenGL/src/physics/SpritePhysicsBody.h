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
	float coefficientOfRestitution;
public:
	SpritePhysicsBody();
	SpritePhysicsBody(glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, glm::vec2 collisionMinExtent, glm::vec2 collisionMaxExtent, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR);
	~SpritePhysicsBody();

	void Update(float delta);
	void ReverseLastUpdate(float delta);
	void ReverseLastVelocityUpdate(float delta);

	void Stop();
	void StopX();
	void StopY();
	void StopZ();

	glm::vec3 GetLinearAcceleration();
	glm::vec3 GetLinearAccelerationWithoutGravity();
	glm::vec3 GetLinearVelocity();



	void ApplyImpulse(glm::vec3 changeInVelocity);
	void ApplyImpulse(glm::vec3 averageForce, float time);
	void ApplyForce(glm::vec3 f);
	void ApplyTorque(glm::vec3 t);

	void ApplyLinearVelocity(glm::vec3 velocity);
	void ApplyAngularVelocity(glm::vec3 velocity);

	void ApplyLinearAcceleration(glm::vec3 acceleration);
	void ApplyAngularAcceleration(glm::vec3 acceleration);

	void SetLinearVelocity(glm::vec3 velocity);
	void SetLinearAcceleration(glm::vec3 acceleration);

	void SetGravitationalAcceleration(glm::vec3 gravity);

	float GetMass();
	void SetMass(float newMass);
	void AddMass(float newMass);

	inline const glm::vec3& GetVelocity() const { return linearVelocity; }
};