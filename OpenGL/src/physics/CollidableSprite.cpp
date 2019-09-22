#include "CollidableSprite.h"
#include <iostream>

CollidableSprite::CollidableSprite()
	: SpritePhysicsBody(), minExtent(0.0f, 0.0f, 0.0f), maxExtent(0.0f, 0.0f, 0.0f)
{

}

CollidableSprite::CollidableSprite(glm::vec3 rot, glm::vec3 trans, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR)
	: SpritePhysicsBody(rot, trans, minExtents, maxExtents, z, bottomLeftTexCoord, topRightTexCoord, tex, startingFrame, m, linearVel, angularVel, f, t, MOI, gravity, COR), minExtent(minExtents.x, minExtents.y, z), maxExtent(maxExtents.x, maxExtents.y, z)
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
	if (minExtents.x < otherMaxExtents.x &&
		maxExtents.x > otherMinExtents.x &&
		minExtents.y < otherMaxExtents.y &&
		maxExtents.y > otherMinExtents.y)
	{
		glm::vec3 currentPos = GetTranslation();
		glm::vec3 absDist = glm::vec3(fabsf(distance.x), fabsf(distance.y), fabsf(distance.z));
		if (absDist.x > absDist.y) {
			if (distance.x > 0) {
				Translate3f(other.GetTranslation().y + (other.GetSize().y), currentPos.y, currentPos.z);
				ApplyLinearVelocity(glm::vec3(1.0f, 0.0f, 0.0f));
			}
			else {
				Translate3f(other.GetTranslation().y - (other.GetSize().y), currentPos.y, currentPos.z);
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
	}
	return IntersectData(false, 0.0f);
}

bool CollidableSprite::UpdateCollision(float deltaT, CollidableSprite s[], unsigned int size)
{
	Update(deltaT);
	bool anyCollision = false;
	for (unsigned int i = 0; i < size; i++) {
		if (IntersectCollidableSprite(s[i]).GetDoesIntersect()) {
			anyCollision = true;
		}
	}
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

inline const glm::vec3 CollidableSprite::Max(const glm::vec3 first, const glm::vec3 second) const
{
	glm::vec3 answer;
	if (first.x > second.x) {
		answer.x = first.x;
	}
	else {
		answer.x = second.x;
	}

	if (first.y > second.y) {
		answer.y = first.y;
	}
	else {
		answer.y = second.y;
	}

	if (first.z > second.z) {
		answer.z = first.z;
	}
	else {
		answer.z = second.z;
	}
	return answer;
}

inline const float CollidableSprite::MaxValue(const glm::vec3 vec) const
{
	float maxVal = vec[0];
	for (unsigned int i = 0; i < 3; i++) {
		if (vec[i] > maxVal) {
			maxVal = vec[i];
		}
	}
	return maxVal;
}