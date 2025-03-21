#pragma once
#include "Object.h"

class Sprite : public Object {
private:
	GLuint currentFrame;
	bool reversing;
public:
	Sprite();
	Sprite(glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, glm::vec2 collisionMinExtent, glm::vec2 collisionMaxExtent, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame);
	~Sprite();

	void Play(GLuint param[], GLuint size);
	void PlayReversible(GLuint param[], GLuint size);
};