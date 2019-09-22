#pragma once

#include "glm/glm.hpp"
#include "primitives/ShapeData.h"
#include <string>

enum type
{
	triangle, cubeModel, blankModel, texturedModel, rectangle
};

class Mesh {
private:
	std::string directory;
	std::string fileName;
	glm::vec3 rotation;
	glm::vec3 translation;
	ShapeData shape;
	glm::vec3 minExtents;
	glm::vec3 maxExtents;
	glm::vec3 size;
public:
	Mesh();
	Mesh(type type, std::string dir, std::string name);
	Mesh(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans);
	Mesh(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, const std::string& texDir, const std::string& texName);
	Mesh(type type, glm::vec3 rot, glm::vec3 trans, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord);
	~Mesh();

	glm::mat4 GetModelTransformMatrix();
	void Rotate3f(float x, float y, float z);
	void RotateVec3(glm::vec3 rot);
	void RotateAdd3f(float x, float y, float z);
	void RotateAddVec3(glm::vec3 rot);
	void Translate3f(float x, float y, float z);
	void TranslateVec3(glm::vec3 trans);
	void TranslateAdd3f(float x, float y, float z);
	void TranslateAddVec3(glm::vec3 trans);
	void TranslateSubtract3f(float x, float y, float z);
	void TranslateSubtractVec3(glm::vec3 trans);
	glm::vec3 GetTranslation() const;
	glm::vec3 GetRotation();
	glm::vec3 GetSize() const;
	ShapeData GetShape();
	void SetShape(ShapeData newShape);
};