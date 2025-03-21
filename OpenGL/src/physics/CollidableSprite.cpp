#include "CollidableSprite.h"
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

CollidableSprite::CollidableSprite()
	: SpritePhysicsBody(), minExtent(0.0f, 0.0f, 0.0f), maxExtent(0.0f, 0.0f, 0.0f), canJump(false), anyCollisionInTheLastIntersectCollidable(false)
{

}

CollidableSprite::CollidableSprite(glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR, BodyType bt)
	: SpritePhysicsBody(rot, trans, scle, minExtents, maxExtents, minExtents, maxExtents, z, bottomLeftTexCoord, topRightTexCoord, tex, startingFrame, m, linearVel, angularVel, f, t, MOI, gravity, COR), minExtent(minExtents.x, minExtents.y, z), maxExtent(maxExtents.x, maxExtents.y, z), canJump(true), anyCollisionInTheLastIntersectCollidable(false), bodyType(bt)
{

}

CollidableSprite::CollidableSprite(glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, glm::vec2 collisionMinExtents, glm::vec2 collisionMaxExtents, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR, BodyType bt)
	: SpritePhysicsBody(rot, trans, scle, collisionMinExtents, collisionMaxExtents, minExtents, maxExtents, z, bottomLeftTexCoord, topRightTexCoord, tex, startingFrame, m, linearVel, angularVel, f, t, MOI, gravity, COR), minExtent(collisionMinExtents.x, collisionMinExtents.y, z), maxExtent(collisionMaxExtents.x, collisionMaxExtents.y, z), canJump(true), anyCollisionInTheLastIntersectCollidable(false), bodyType(bt)
{

}

CollidableSprite::~CollidableSprite()
{

}

IntersectData CollidableSprite::GetDoesIntersect(const CollidableSprite& other)
{
	if (bodyType == BodyType::rectangle && other.bodyType == BodyType::rectangle)
	{
		// Rectangle on Rectangle collision using SAT
		glm::vec3 minExtents = GetMinExtents();
		glm::vec3 maxExtents = GetMaxExtents();
		glm::vec3 otherMinExtents = other.GetMinExtents();
		glm::vec3 otherMaxExtents = other.GetMaxExtents();

		glm::vec3 center = (minExtents + maxExtents) / 2.0f;
		glm::vec3 otherCenter = (otherMinExtents + otherMaxExtents) / 2.0f;

		glm::vec3 halfSize = (maxExtents - minExtents) / 2.0f;
		glm::vec3 otherHalfSize = (otherMaxExtents - otherMinExtents) / 2.0f;

		glm::vec3 axes[4] = {
			glm::rotate(glm::vec3(1, 0, 0), glm::radians(GetRotation().z), glm::vec3(0, 0, 1)),
			glm::rotate(glm::vec3(0, 1, 0), glm::radians(GetRotation().z), glm::vec3(0, 0, 1)),
			glm::rotate(glm::vec3(1, 0, 0), glm::radians(other.GetRotation().z), glm::vec3(0, 0, 1)),
			glm::rotate(glm::vec3(0, 1, 0), glm::radians(other.GetRotation().z), glm::vec3(0, 0, 1))
		};

		float minPenetration = std::numeric_limits<float>::max();
		glm::vec3 penetrationDirection;

		for (int i = 0; i < 4; ++i)
		{
			glm::vec3 axis = axes[i];
			float projection1 = glm::abs(glm::dot(halfSize, axis));
			float projection2 = glm::abs(glm::dot(otherHalfSize, axis));
			float distance = glm::abs(glm::dot(center - otherCenter, axis));

			float penetration = projection1 + projection2 - distance;
			if (penetration < 0)
			{
				return IntersectData(false, 0.0f, glm::vec3(0.0f));
			}

			if (penetration < minPenetration)
			{
				minPenetration = penetration;
				penetrationDirection = axis;
			}
		}

		return IntersectData(true, minPenetration, penetrationDirection);
	}
	else if (bodyType == BodyType::circle && other.bodyType == BodyType::circle)
	{
		// Circle on Circle collision
		glm::vec3 center = (GetMinExtents() + GetMaxExtents()) / 2.0f;
		glm::vec3 otherCenter = (other.GetMinExtents() + other.GetMaxExtents()) / 2.0f;
		float radius = (GetMaxExtents().x - GetMinExtents().x) / 2.0f;
		float otherRadius = (other.GetMaxExtents().x - other.GetMinExtents().x) / 2.0f;

		float distance = glm::distance(center, otherCenter);
		float penetration = (radius + otherRadius) - distance;

		if (penetration > 0)
		{
			return IntersectData(true, penetration, glm::normalize(center - otherCenter));
		}
	}
	else if (bodyType == BodyType::circle && other.bodyType == BodyType::rectangle)
	{
		// Circle on Rectangle collision
		glm::vec3 center = (GetMinExtents() + GetMaxExtents()) / 2.0f;
		float radius = (GetMaxExtents().x - GetMinExtents().x) / 2.0f;
		glm::vec3 otherMinExtents = other.GetMinExtents();
		glm::vec3 otherMaxExtents = other.GetMaxExtents();

		glm::vec3 otherCenter = (otherMinExtents + otherMaxExtents) / 2.0f;
		glm::vec3 otherHalfSize = (otherMaxExtents - otherMinExtents) / 2.0f;

		glm::vec3 closestPoint = otherCenter;
		glm::vec3 direction = glm::normalize(center - otherCenter);

		closestPoint += glm::clamp(glm::dot(direction, glm::rotate(glm::vec3(1, 0, 0), glm::radians(other.GetRotation().z), glm::vec3(0, 0, 1))) * otherHalfSize.x, -otherHalfSize.x, otherHalfSize.x) * glm::rotate(glm::vec3(1, 0, 0), glm::radians(other.GetRotation().z), glm::vec3(0, 0, 1));
		closestPoint += glm::clamp(glm::dot(direction, glm::rotate(glm::vec3(0, 1, 0), glm::radians(other.GetRotation().z), glm::vec3(0, 0, 1))) * otherHalfSize.y, -otherHalfSize.y, otherHalfSize.y) * glm::rotate(glm::vec3(0, 1, 0), glm::radians(other.GetRotation().z), glm::vec3(0, 0, 1));

		float distance = glm::distance(center, closestPoint);
		float penetration = radius - distance;

		if (penetration > 0)
		{
			return IntersectData(true, penetration, glm::normalize(center - closestPoint));
		}
	}
	else if (bodyType == BodyType::rectangle && other.bodyType == BodyType::circle)
	{
		// Rectangle on Circle collision
		glm::vec3 center = (other.GetMinExtents() + other.GetMaxExtents()) / 2.0f;
		float radius = (other.GetMaxExtents().x - other.GetMinExtents().x) / 2.0f;
		glm::vec3 minExtents = GetMinExtents();
		glm::vec3 maxExtents = GetMaxExtents();

		glm::vec3 rectCenter = (minExtents + maxExtents) / 2.0f;
		glm::vec3 halfSize = (maxExtents - minExtents) / 2.0f;

		glm::vec3 closestPoint = rectCenter;
		glm::vec3 direction = glm::normalize(center - rectCenter);

		closestPoint += glm::clamp(glm::dot(direction, glm::rotate(glm::vec3(1, 0, 0), glm::radians(GetRotation().z), glm::vec3(0, 0, 1))) * halfSize.x, -halfSize.x, halfSize.x) * glm::rotate(glm::vec3(1, 0, 0), glm::radians(GetRotation().z), glm::vec3(0, 0, 1));
		closestPoint += glm::clamp(glm::dot(direction, glm::rotate(glm::vec3(0, 1, 0), glm::radians(GetRotation().z), glm::vec3(0, 0, 1))) * halfSize.y, -halfSize.y, halfSize.y) * glm::rotate(glm::vec3(0, 1, 0), glm::radians(GetRotation().z), glm::vec3(0, 0, 1));

		float distance = glm::distance(center, closestPoint);
		float penetration = radius - distance;

		if (penetration > 0)
		{
			return IntersectData(true, penetration, glm::normalize(center - closestPoint));
		}
	}

	return IntersectData(false, 0.0f, glm::vec3(0.0f));
}

IntersectData CollidableSprite::IsPointInside(const glm::vec3& point)
{
	////////////////////////////////////////////////////////////////////////////////
	glm::vec3 minExtents = GetMinExtents();
	glm::vec3 maxExtents = GetMaxExtents();
	////////////////////////////////////////////////////////////////////////////////
	if (point.x <= maxExtents.x && point.x >= minExtents.x && point.y <= maxExtents.y && point.y >= minExtents.y) {
		return IntersectData(true, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	}
	return IntersectData(false, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
}

bool CollidableSprite::UpdateCollision(float deltaT, std::vector<CollidableSprite>& vect)
{
	Update(deltaT);
	bool anyCollision = false;
	float coefficientOfRestitution = 0.8f; // Assuming a uniform coefficient of restitution

	for (unsigned int i = 0; i < vect.size(); i++) {
		IntersectData intersectData = GetDoesIntersect(vect[i]);
		if (intersectData.GetDoesIntersect()) {
			anyCollision = true;

			// Resolve collision based on mass
			float otherMass = vect[i].GetMass();
			if (otherMass <= 0.0f) {
				// The other object is immovable
				glm::vec3 currentPos = GetTranslation();
				glm::vec3 penetrationDepth = intersectData.GetDirection() * intersectData.GetDistance();
				if (glm::length(penetrationDepth) > 0.0f) {
					Translate3f(currentPos.x + penetrationDepth.x, currentPos.y + penetrationDepth.y, currentPos.z + penetrationDepth.z);
				}
				SetLinearVelocity(glm::vec3(0.0f)); // Stop the object
			}
			else {
				// Calculate the response based on mass
				float thisMass = GetMass();
				glm::vec3 thisVelocity = GetLinearVelocity();
				glm::vec3 otherVelocity = vect[i].GetLinearVelocity();

				glm::vec3 relativeVelocity = thisVelocity - otherVelocity;
				glm::vec3 collisionNormal = glm::normalize(intersectData.GetDirection());

				if (glm::length(collisionNormal) == 0.0f) {
					continue; // Avoid normalizing zero vector
				}

				float velocityAlongNormal = glm::dot(relativeVelocity, collisionNormal);
				if (velocityAlongNormal > 0) {
					continue;
				}

				float j = -(1 + coefficientOfRestitution) * velocityAlongNormal;
				j /= (1 / thisMass) + (1 / otherMass);

				glm::vec3 impulse = j * collisionNormal;
				ApplyImpulse(-impulse);
				vect[i].ApplyImpulse(impulse);

				// Adjust positions to resolve penetration
				glm::vec3 penetrationDepth = intersectData.GetDirection() * intersectData.GetDistance();
				if (glm::length(penetrationDepth) > 0.0f) {
					Translate3f(GetTranslation().x + penetrationDepth.x / 2.0f, GetTranslation().y + penetrationDepth.y / 2.0f, GetTranslation().z + penetrationDepth.z / 2.0f);
					vect[i].Translate3f(vect[i].GetTranslation().x - penetrationDepth.x / 2.0f, vect[i].GetTranslation().y - penetrationDepth.y / 2.0f, vect[i].GetTranslation().z - penetrationDepth.z / 2.0f);
				}
			}
		}
	}

	return anyCollision;
}

bool CollidableSprite::GetCanJump()
{
	return canJump;
}

void CollidableSprite::SetCanJump(bool newValue)
{
	canJump = newValue;
}

void CollidableSprite::SetMinExtents(const glm::vec3& newMinExtents)
{
	minExtent = newMinExtents;
}

void CollidableSprite::SetMaxExtents(const glm::vec3& newMaxExtents)
{
	maxExtent = newMaxExtents;
}
