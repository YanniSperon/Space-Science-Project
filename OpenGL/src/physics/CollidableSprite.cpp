#include "CollidableSprite.h"
#include <iostream>

CollidableSprite::CollidableSprite()
	: SpritePhysicsBody(), minExtent(0.0f, 0.0f, 0.0f), maxExtent(0.0f, 0.0f, 0.0f), canJump(false), anyCollisionInTheLastIntersectCollidable(false)
{

}

CollidableSprite::CollidableSprite(glm::vec3 rot, glm::vec3 trans, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR)
	: SpritePhysicsBody(rot, trans, minExtents, maxExtents, minExtents, maxExtents, z, bottomLeftTexCoord, topRightTexCoord, tex, startingFrame, m, linearVel, angularVel, f, t, MOI, gravity, COR), minExtent(minExtents.x, minExtents.y, z), maxExtent(maxExtents.x, maxExtents.y, z), canJump(true), anyCollisionInTheLastIntersectCollidable(false)
{

}

CollidableSprite::CollidableSprite(glm::vec3 rot, glm::vec3 trans, glm::vec2 collisionMinExtents, glm::vec2 collisionMaxExtents, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR)
	: SpritePhysicsBody(rot, trans, collisionMinExtents, collisionMaxExtents, minExtents, maxExtents, z, bottomLeftTexCoord, topRightTexCoord, tex, startingFrame, m, linearVel, angularVel, f, t, MOI, gravity, COR), minExtent(collisionMinExtents.x, collisionMinExtents.y, z), maxExtent(collisionMaxExtents.x, collisionMaxExtents.y, z), canJump(true), anyCollisionInTheLastIntersectCollidable(false)
{

}

CollidableSprite::~CollidableSprite()
{

}

IntersectData CollidableSprite::IntersectCollidableSprite(const CollidableSprite& other)
{
	////////////////////////////////////////////////////////////////////////////////
	glm::vec3 minExtents = GetMinExtents();
	glm::vec3 maxExtents = GetMaxExtents();
	////////////////////////////////////////////////////////////////////////////////
	glm::vec3 otherMinExtents = other.GetMinExtents();
	glm::vec3 otherMaxExtents = other.GetMaxExtents();
	////////////////////////////////////////////////////////////////////////////////
	glm::vec3 distance = minExtents - otherMinExtents;
	////////////////////////////////////////////////////////////////////////////////
	glm::vec2 obj1Point1 = glm::vec2(minExtents.x, maxExtents.y);
	glm::vec2 obj1Point2 = glm::vec2(maxExtents.x, maxExtents.y);
	glm::vec2 obj1Point3 = glm::vec2(minExtents.x, minExtents.y);
	glm::vec2 obj1Point4 = glm::vec2(maxExtents.x, minExtents.y);
	////////////////////////////////////////////////////////////////////////////////
	glm::vec2 obj2Point1 = glm::vec2(otherMinExtents.x, otherMaxExtents.y);
	glm::vec2 obj2Point2 = glm::vec2(otherMaxExtents.x, otherMaxExtents.y);
	glm::vec2 obj2Point3 = glm::vec2(otherMinExtents.x, otherMinExtents.y);
	glm::vec2 obj2Point4 = glm::vec2(otherMaxExtents.x, otherMinExtents.y);
	////////////////////////////////////////////////////////////////////////////////
	if (((obj2Point1.x >= obj1Point3.x && obj2Point1.x <= obj1Point2.x &&
		obj2Point1.y >= obj1Point3.y && obj2Point1.y <= obj1Point2.y) ||
		(obj2Point2.x >= obj1Point3.x && obj2Point2.x <= obj1Point2.x &&
		obj2Point2.y >= obj1Point3.y && obj2Point2.y <= obj1Point2.y) ||
		(obj2Point3.x >= obj1Point3.x && obj2Point3.x <= obj1Point2.x &&
		obj2Point3.y >= obj1Point3.y && obj2Point3.y <= obj1Point2.y) ||
		(obj2Point4.x >= obj1Point3.x && obj2Point4.x <= obj1Point2.x &&
		obj2Point4.y >= obj1Point3.y && obj2Point4.y <= obj1Point2.y))
		||
		((obj1Point1.x >= obj2Point3.x && obj1Point1.x <= obj2Point2.x &&
		obj1Point1.y >= obj2Point3.y && obj1Point1.y <= obj2Point2.y) ||
		(obj1Point2.x >= obj2Point3.x && obj1Point2.x <= obj2Point2.x &&
		obj1Point2.y >= obj2Point3.y && obj1Point2.y <= obj2Point2.y) ||
		(obj1Point3.x >= obj2Point3.x && obj1Point3.x <= obj2Point2.x &&
		obj1Point3.y >= obj2Point3.y && obj1Point3.y <= obj2Point2.y) ||
		(obj1Point4.x >= obj2Point3.x && obj1Point4.x <= obj2Point2.x &&
		obj1Point4.y >= obj2Point3.y && obj1Point4.y <= obj2Point2.y)))
	{
		////////////////////////////////////////////////////////////////////////////////
		glm::vec3 currentPos = GetTranslation();
		glm::vec3 absDist = glm::vec3(std::abs(distance.x), std::abs(distance.y), std::abs(distance.z));
		if (absDist.x > absDist.y) {
			if (distance.x > 0) {
				Translate3f(other.GetTranslation().x + (other.GetSize().x), currentPos.y, currentPos.z);
				ApplyLinearVelocity(glm::vec3(1.0f, 0.0f, 0.0f));
			}
			else {
				Translate3f(other.GetTranslation().x - (other.GetSize().x), currentPos.y, currentPos.z);
				ApplyLinearVelocity(glm::vec3(-1.0f, 0.0f, 0.0f));
			}
			StopX();
		}
		else {
			if (distance.y > 0) {
				Translate3f(currentPos.x, other.GetTranslation().y + (other.GetSize().y), currentPos.z);
			}
			else {
				Translate3f(currentPos.x, other.GetTranslation().y - (other.GetSize().y), currentPos.z);
			}
			StopY();
			canJump = true;
		}
		return IntersectData(true, 0.0f);
		////////////////////////////////////////////////////////////////////////////////
	}
	return IntersectData(false, 0.0f);
}

bool CollidableSprite::UpdateCollision(float deltaT, CollidableSprite s[], unsigned int size)
{
	Update(deltaT);
	bool anyCollision = false;
	/*int indexWithSmallestDistance = 0;
	float smallestDistance = INFINITY;*/
	for (unsigned int i = 0; i < size; i++) {
		/*glm::vec3 minExtents = GetMinExtents();
		glm::vec3 maxExtents = GetMaxExtents();

		glm::vec3 otherMinExtents = s[i].GetMinExtents();
		glm::vec3 otherMaxExtents = s[i].GetMaxExtents();

		glm::vec3 changeInValues = minExtents - otherMinExtents;

		float distance = (changeInValues.x * changeInValues.x) + (changeInValues.y * changeInValues.y) + (changeInValues.z * changeInValues.z);

		if (distance < smallestDistance) {
			smallestDistance = distance;
			indexWithSmallestDistance = i;
		}*/
		if (IntersectCollidableSprite(s[i]).GetDoesIntersect()) {
			anyCollision = true;
		}
	}
	/*if (IntersectCollidableSprite(s[indexWithSmallestDistance]).GetDoesIntersect()) {
		anyCollision = true;
	}*/
	if (anyCollision) {
		ReverseLastUpdate(deltaT);
		return true;
	}
	return false;
}

bool CollidableSprite::GetCanJump()
{
	return canJump;
}

void CollidableSprite::SetCanJump(bool newValue)
{
	canJump = newValue;
}