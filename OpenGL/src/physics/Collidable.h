#pragma once
#include "AxisAlignedBoundingBox.h"
#include "SpritePhysicsBody.h"

class CollidableSprite : public AxisAlignedBoundingBox, public SpritePhysicsBody {
private:

public:
	CollidableSprite();
	CollidableSprite(glm::vec3 rot, glm::vec3 trans, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity);
	~CollidableSprite();
};