#include "Sprite.h"

Sprite::Sprite()
	: Object(), currentFrame(0)
{

}

Sprite::Sprite(glm::vec3 rot, glm::vec3 trans, glm::vec2 collisionMinExtent, glm::vec2 collisionMaxExtent, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex, GLuint startingFrame)
	: Object(type::rectangle, rot, trans, collisionMinExtent, collisionMaxExtent, minExtents, maxExtents, z, bottomLeftTexCoord, topRightTexCoord, tex), currentFrame(startingFrame)
{

}

Sprite::~Sprite()
{

}

void Sprite::Play(GLuint param[])
{
	currentFrame++;
	if (currentFrame == 4) {
		currentFrame = 0;
	}
	Object::PlayFrame(param[currentFrame]);
}
