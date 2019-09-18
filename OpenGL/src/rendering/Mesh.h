#pragma once

#include "glm/glm.hpp"
#include "primitives/ShapeData.h"
#include <string>

enum type
{
	triangle, cubeModel, blankModel, texturedModel
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
public:
	Mesh();
	Mesh(type type, std::string dir, std::string name);
	Mesh(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans);
	Mesh(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, const std::string& texDir, const std::string& texName);
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
	glm::vec3 GetTranslation();
	glm::vec3 GetRotation();
	ShapeData GetShape();
	void SetShape(ShapeData newShape);
};