#include "SpritePhysicsBody.h"

SpritePhysicsBody::SpritePhysicsBody()
	: Sprite(), mass(0.0f), linearVelocity(0.0f, 0.0f, 0.0f), force(0.0f, 0.0f, 0.0f), angularVelocity(0.0f, 0.0f, 0.0f), torque(0.0f, 0.0f, 0.0f), momentOfInertia(0.0f), gravitationalAcceleration(0.0f), coefficientOfRestitution(0.0f), lastDeltaT(0.0f)
{

}

SpritePhysicsBody::SpritePhysicsBody(glm::vec3 rot, glm::vec3 trans, glm::vec2 collisionMinExtent, glm::vec2 collisionMaxExtent, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR)
	: Sprite(rot, trans, collisionMinExtent, collisionMaxExtent, minExtents, maxExtents, z, bottomLeftTexCoord, topRightTexCoord, tex, startingFrame), mass(m), linearVelocity(linearVel), force(f), angularVelocity(angularVel), torque(t), momentOfInertia(MOI), gravitationalAcceleration(gravity), coefficientOfRestitution(COR), lastDeltaT(0.0f)
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

void SpritePhysicsBody::ReverseLastUpdate(float delta)
{
	linearVelocity -= gravitationalAcceleration * delta;
	TranslateSubtractVec3(linearVelocity * delta);
}

void SpritePhysicsBody::ReverseLastVelocityUpdate(float delta)
{
	linearVelocity -= gravitationalAcceleration * delta;
}

void SpritePhysicsBody::Stop()
{
	linearVelocity = angularVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

void SpritePhysicsBody::StopX()
{
	linearVelocity.x = 0.0f;
}

void SpritePhysicsBody::StopY()
{
	linearVelocity.y = 0.0f;
}

void SpritePhysicsBody::StopZ()
{
	linearVelocity.z = 0.0f;
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

void SpritePhysicsBody::ApplyImpulse(glm::vec3 changeInVelocity)
{
	linearVelocity += changeInVelocity;
}

void SpritePhysicsBody::ApplyImpulse(glm::vec3 averageForce, float time)
{
	linearVelocity += (averageForce * time) / mass;
}

void SpritePhysicsBody::ApplyForce(glm::vec3 f)
{
	force += f;
}

void SpritePhysicsBody::ApplyTorque(glm::vec3 t)
{
	torque += t;
}

void SpritePhysicsBody::ApplyLinearVelocity(glm::vec3 velocity)
{
	linearVelocity += velocity;
}

void SpritePhysicsBody::ApplyAngularVelocity(glm::vec3 velocity)
{
	angularVelocity += velocity;
}

void SpritePhysicsBody::ApplyLinearAcceleration(glm::vec3 acceleration)
{
	force += acceleration / mass;
}

void SpritePhysicsBody::ApplyAngularAcceleration(glm::vec3 acceleration)
{
	torque += acceleration / momentOfInertia;
}

void SpritePhysicsBody::SetLinearVelocity(glm::vec3 velocity)
{
	linearVelocity = velocity;
}
