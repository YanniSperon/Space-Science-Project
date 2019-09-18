#pragma once
#include "ShapeData.h"
#include <string>
class ShapeGenerator {
public:
	static ShapeData makeTriangle(glm::vec3& min, glm::vec3& max);
	static ShapeData makeCube(glm::vec3& min, glm::vec3& max);
	static ShapeData loadShape(std::string fileName, glm::vec3& min, glm::vec3& max);
	static ShapeData loadTexturedShape(std::string directory, std::string name, glm::vec3& min, glm::vec3& max);
	static ShapeData loadRectangle(glm::vec2 minExtent, glm::vec2 maxExtent, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord);
};