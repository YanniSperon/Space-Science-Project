#include "Mesh.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "primitives/ShapeGenerator.h"
#include <iostream>

Mesh::Mesh()
	: directory(""), fileName("Error"), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), shape(), minExtents(0.0f, 0.0f, 0.0f), maxExtents(0.0f, 0.0f, 0.0f)
{

}

Mesh::Mesh(type type, std::string dir, std::string name)
	: directory(directory), fileName(fileName), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), minExtents(0.0f, 0.0f, 0.0f), maxExtents(0.0f, 0.0f, 0.0f)
{
	if (type == type::cubeModel) {
		shape = ShapeGenerator::makeCube(minExtents, maxExtents);
	}
	else if (type == type::blankModel) {
		shape = ShapeGenerator::loadShape(dir + name, minExtents, maxExtents);
	}
	else if (type == type::texturedModel) {
		shape = ShapeGenerator::loadTexturedShape(dir, name, minExtents, maxExtents);
	}
	else {
		shape = ShapeGenerator::makeTriangle(minExtents, maxExtents);
	}
}

Mesh::Mesh(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans)
	: directory(directory), fileName(fileName), rotation(rot), translation(trans), minExtents(0.0f, 0.0f, 0.0f), maxExtents(0.0f, 0.0f, 0.0f)
{
	if (type == type::cubeModel) {
		shape = ShapeGenerator::makeCube(minExtents, maxExtents);
	}
	else if (type == type::blankModel) {
		shape = ShapeGenerator::loadShape(dir + name, minExtents, maxExtents);
	}
	else if (type == type::texturedModel) {
		shape = ShapeGenerator::loadTexturedShape(dir, name, minExtents, maxExtents);
	}
	else {
		shape = ShapeGenerator::makeTriangle(minExtents, maxExtents);
	}
}

Mesh::Mesh(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, const std::string& texDir, const std::string& texName)
	: directory(directory), fileName(fileName), rotation(rot), translation(trans)
{
	if (type == type::cubeModel) {
		shape = ShapeGenerator::makeCube(minExtents, maxExtents);
	}
	else if (type == type::blankModel) {
		shape = ShapeGenerator::loadShape(dir + name, minExtents, maxExtents);
	}
	else if (type == type::texturedModel) {
		shape = ShapeGenerator::loadTexturedShape(dir, name, minExtents, maxExtents);
	}
	else {
		shape = ShapeGenerator::makeTriangle(minExtents, maxExtents);
	}
}

Mesh::~Mesh()
{

}

glm::mat4 Mesh::GetModelTransformMatrix()
{
	return (glm::translate(glm::mat4(), translation) * glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)));
}

void Mesh::Rotate3f(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void Mesh::RotateVec3(glm::vec3 rot) {
	rotation = rot;
}

void Mesh::RotateAdd3f(float x, float y, float z)
{
	rotation.x += x;
	rotation.y += y;
	rotation.z += z;
}

void Mesh::RotateAddVec3(glm::vec3 rot)
{
	rotation += rot;
}

void Mesh::Translate3f(float x, float y, float z)
{
	translation.x = x;
	translation.y = y;
	translation.z = z;
}

void Mesh::TranslateVec3(glm::vec3 trans) {
	translation = trans;
}

void Mesh::TranslateAdd3f(float x, float y, float z)
{
	translation.x += x;
	translation.y += y;
	translation.z += z;
}

void Mesh::TranslateAddVec3(glm::vec3 trans)
{
	translation += trans;
}

glm::vec3 Mesh::GetTranslation()
{
	return translation;
}

glm::vec3 Mesh::GetRotation()
{
	return rotation;
}

ShapeData Mesh::GetShape()
{
	return shape;
}

void Mesh::SetShape(ShapeData newShape)
{
	shape = newShape;
}
