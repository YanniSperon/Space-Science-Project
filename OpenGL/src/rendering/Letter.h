#pragma once
#include "Object.h"

class Letter : public Object {
private:
	float distanceFromCamera;
public:
	Letter();
	Letter(float size, type type, glm::vec3 rot, glm::vec3 trans, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex);
	~Letter();

	float GetDistanceFromCamera();
	void SetDistanceFromCamera(float newDist);
};