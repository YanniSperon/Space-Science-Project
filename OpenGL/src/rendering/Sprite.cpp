#include "Sprite.h"

Sprite::Sprite()
	: Object(), currentFrame(0), reversing(false)
{

}

Sprite::Sprite(glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, glm::vec2 collisionMinExtent, glm::vec2 collisionMaxExtent, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame)
	: Object(type::rectangle, rot, trans, scle, collisionMinExtent, collisionMaxExtent, minExtents, maxExtents, z, bottomLeftTexCoord, topRightTexCoord, tex), currentFrame(startingFrame), reversing(false)
{

}

Sprite::~Sprite()
{

}

void Sprite::Play(GLuint param[], GLuint size)
{
	currentFrame++;
	if (currentFrame == size) {
		currentFrame = 0;
	}
	Object::PlayFrame(param[currentFrame]);
}

void Sprite::PlayReversible(GLuint param[], GLuint size)
{
	if (!reversing) {
		currentFrame++;
	}
	else {
		currentFrame--;
	}

	if (currentFrame == size - 1) {
		reversing = true;
	}
	else if (currentFrame == 0) {
		reversing = false;
	}
	Object::PlayFrame(param[currentFrame]);
}
