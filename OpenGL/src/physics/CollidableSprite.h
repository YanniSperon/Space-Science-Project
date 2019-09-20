#pragma once
#include "IntersectData.h"
#include "SpritePhysicsBody.h"

class CollidableSprite : public SpritePhysicsBody {
private:
	const glm::vec3 minExtent;
	const glm::vec3 maxExtent;
public:
	CollidableSprite();
	CollidableSprite(glm::vec3 rot, glm::vec3 trans, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR);
	~CollidableSprite();

	IntersectData IntersectCollidableSprite(const CollidableSprite& other);

	bool UpdateCollision(float deltaT, CollidableSprite s[], unsigned int size);

	inline const glm::vec3& GetMinExtents() const { return minExtent + GetTranslation(); }
	inline const glm::vec3& GetMaxExtents() const { return maxExtent + GetTranslation(); }
	inline const glm::vec3 Max(const glm::vec3 first, const glm::vec3 second) const;
	inline const float MaxValue(const glm::vec3 vec) const;
};