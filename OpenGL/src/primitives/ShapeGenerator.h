#pragma once
#include "ShapeData.h"
#include <string>
class ShapeGenerator {
public:
	static ShapeData makeTriangle(glm::vec3& min, glm::vec3& max);
	static ShapeData makeCube(glm::vec3& min, glm::vec3& max);
	static ShapeData loadShape(std::string fileName, glm::vec3& min, glm::vec3& max);
	static ShapeData loadTexturedShape(std::string directory, std::string name, glm::vec3& min, glm::vec3& max);
	static ShapeData loadRectangle(std::string directory, std::string name, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord);
};