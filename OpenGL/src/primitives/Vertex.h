#pragma once
#include "glm/glm.hpp"

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texCoord;
};

struct texCoords {
	glm::vec2 bottomLeft, topRight;
};