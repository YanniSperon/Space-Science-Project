#pragma once
#include "IntersectData.h"
#include "SpritePhysicsBody.h"

class CollidableSprite : public SpritePhysicsBody {
public:
	enum class BodyType {
		rectangle = 0, circle = 1
	};
private:
	glm::vec3 minExtent;
	glm::vec3 maxExtent;
	bool canJump;
	bool anyCollisionInTheLastIntersectCollidable;
	BodyType bodyType;

public:
	CollidableSprite();
	CollidableSprite(glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR, BodyType bt);
	CollidableSprite(glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, glm::vec2 collisionMinExtents, glm::vec2 collisionMaxExtents, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR, BodyType bt);
	~CollidableSprite();

	bool UpdateCollision(float deltaTime, std::vector<CollidableSprite>& ground);
	IntersectData GetDoesIntersect(const CollidableSprite& other);
	IntersectData IsPointInside(const glm::vec3& point);

	bool GetCanJump();
	void SetCanJump(bool newValue);

	inline const glm::vec3 GetMinExtents() const { return (glm::vec3(minExtent.x*GetScale().x, minExtent.y*GetScale().y, minExtent.z) + GetTranslation()); }
	inline const glm::vec3 GetMaxExtents() const { return (glm::vec3(maxExtent.x * GetScale().x, maxExtent.y * GetScale().y, maxExtent.z) + GetTranslation()); }

	void SetMinExtents(const glm::vec3& newMinExtents);
	void SetMaxExtents(const glm::vec3& newMaxExtents);
};