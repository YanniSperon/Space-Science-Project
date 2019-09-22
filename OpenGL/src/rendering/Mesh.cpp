#include "Mesh.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "primitives/ShapeGenerator.h"
#include <iostream>

Mesh::Mesh()
	: directory(""), fileName("Error"), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), shape(), minExtents(0.0f, 0.0f, 0.0f), maxExtents(0.0f, 0.0f, 0.0f), size(maxExtents - minExtents)
{

}

Mesh::Mesh(type type, std::string dir, std::string name)
	: directory(directory), fileName(fileName), rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), minExtents(0.0f, 0.0f, 0.0f), maxExtents(0.0f, 0.0f, 0.0f), size(maxExtents - minExtents)
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
	else if (type == type::rectangle) {
		shape = ShapeGenerator::loadRectangle(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
	}
	else {
		shape = ShapeGenerator::makeTriangle(minExtents, maxExtents);
	}
}

Mesh::Mesh(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans)
	: directory(directory), fileName(fileName), rotation(rot), translation(trans), minExtents(0.0f, 0.0f, 0.0f), maxExtents(0.0f, 0.0f, 0.0f), size(maxExtents - minExtents)
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
	else if (type == type::rectangle) {
		shape = ShapeGenerator::loadRectangle(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
	}
	else {
		shape = ShapeGenerator::makeTriangle(minExtents, maxExtents);
	}
}

Mesh::Mesh(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, const std::string& texDir, const std::string& texName)
	: directory(directory), fileName(fileName), rotation(rot), translation(trans), minExtents(0.0f, 0.0f, 0.0f), maxExtents(0.0f, 0.0f, 0.0f), size(maxExtents - minExtents)
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
	else if (type == type::rectangle) {
		shape = ShapeGenerator::loadRectangle(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
	}
	else {
		shape = ShapeGenerator::makeTriangle(minExtents, maxExtents);
	}
}

Mesh::Mesh(type type, glm::vec3 rot, glm::vec3 trans, glm::vec2 minExtent, glm::vec2 maxExtent, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord)
	: directory(""), fileName(""), rotation(rot), translation(trans), minExtents(minExtent, z), maxExtents(maxExtent, z), size(maxExtents - minExtents)
{
	// Only supports primitives
	if (type == type::cubeModel) {
		shape = ShapeGenerator::makeCube(glm::vec3(minExtent.x, minExtent.y, z), glm::vec3(maxExtent.x, maxExtent.y, z));
	}
	else if (type == type::rectangle) {
		shape = ShapeGenerator::loadRectangle(minExtent, maxExtent, z, bottomLeftTexCoord, topRightTexCoord);
	}
	else {
		shape = ShapeGenerator::makeTriangle(glm::vec3(minExtent.x, minExtent.y, z), glm::vec3(maxExtent.x, maxExtent.y, z));
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

void Mesh::TranslateSubtract3f(float x, float y, float z)
{
	translation.x -= x;
	translation.y -= y;
	translation.z -= z;
}

void Mesh::TranslateSubtractVec3(glm::vec3 trans)
{
	translation -= trans;
}

glm::vec3 Mesh::GetTranslation() const
{
	return translation;
}

glm::vec3 Mesh::GetRotation()
{
	return rotation;
}

glm::vec3 Mesh::GetSize() const
{
	return size;
}

ShapeData Mesh::GetShape()
{
	return shape;
}

void Mesh::SetShape(ShapeData newShape)
{
	shape = newShape;
}
