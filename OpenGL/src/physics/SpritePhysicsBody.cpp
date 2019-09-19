#include "SpritePhysicsBody.h"

SpritePhysicsBody::SpritePhysicsBody()
	: Sprite(), mass(0.0f), linearVelocity(0.0f, 0.0f, 0.0f), force(0.0f, 0.0f, 0.0f), angularVelocity(0.0f, 0.0f, 0.0f), torque(0.0f, 0.0f, 0.0f), momentOfInertia(0.0f), gravitationalAcceleration(0.0f)
{

}

SpritePhysicsBody::SpritePhysicsBody(glm::vec3 rot, glm::vec3 trans, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity)
	: Sprite(rot, trans, minExtents, maxExtents, z, bottomLeftTexCoord, topRightTexCoord, tex, startingFrame), mass(m), linearVelocity(linearVel), force(f), angularVelocity(angularVel), torque(t), momentOfInertia(MOI), gravitationalAcceleration(gravity)
{

}

SpritePhysicsBody::~SpritePhysicsBody()
{

}

void SpritePhysicsBody::Update(float delta)
{
	linearVelocity += gravitationalAcceleration * delta;
	TranslateAddVec3(linearVelocity * delta);
}

void SpritePhysicsBody::Stop()
{
	linearVelocity = angularVelocity = force = torque = glm::vec3(0.0f, 0.0f, 0.0f);
}

void SpritePhysicsBody::Jump(glm::vec3 vel)
{
	linearVelocity += vel;
}

glm::vec3 SpritePhysicsBody::GetLinearAcceleration()
{
	return glm::vec3(force / mass) + gravitationalAcceleration;
}

glm::vec3 SpritePhysicsBody::GetLinearAccelerationWithoutGravity()
{
	return glm::vec3(force / mass);
}

glm::vec3 SpritePhysicsBody::GetLinearVelocity()
{
	return linearVelocity;
}
