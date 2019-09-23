#include "Letter.h"

Letter::Letter()
	: distanceFromCamera(0.0f), Object()
{

}

Letter::Letter(float size, type type, glm::vec3 rot, glm::vec3 trans, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex)
	: distanceFromCamera(-size), Object(type, rot, trans, minExtents, maxExtents, z, bottomLeftTexCoord, topRightTexCoord, tex)
{

}

Letter::~Letter()
{

}

float Letter::GetDistanceFromCamera()
{
	return distanceFromCamera;
}

void Letter::SetDistanceFromCamera(float newDist)
{
	distanceFromCamera = newDist;
}
