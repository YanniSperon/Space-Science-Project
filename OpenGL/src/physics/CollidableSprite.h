#pragma once
#include "IntersectData.h"
#include "SpritePhysicsBody.h"

class CollidableSprite : public SpritePhysicsBody {
private:
	const glm::vec3 minExtent;
	const glm::vec3 maxExtent;
	bool canJump;
public:
	CollidableSprite();
	CollidableSprite(glm::vec3 rot, glm::vec3 trans, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR);
	CollidableSprite(glm::vec3 rot, glm::vec3 trans, glm::vec2 collisionMinExtents, glm::vec2 collisionMaxExtents, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR);
	~CollidableSprite();

	IntersectData IntersectCollidableSprite(const CollidableSprite& other);

	bool UpdateCollision(float deltaT, CollidableSprite s[], unsigned int size);

	bool GetCanJump();
	void SetCanJump(bool newValue);

	inline const glm::vec3& GetMinExtents() const { return minExtent + GetTranslation(); }
	inline const glm::vec3& GetMaxExtents() const { return maxExtent + GetTranslation(); }
};