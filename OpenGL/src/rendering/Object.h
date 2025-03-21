#pragma once
#include "Mesh.h"
#include "primitives/ShapeData.h"
#include "Shader.h"

class Object : public Mesh {
private:
	GLuint vertexBufferID;
	GLuint indexBufferID;
	GLuint texID;
	GLsizei numIndices;
	Shader shader;
	GLuint currentFrame;
public:
	Object();
	Object(type type, std::string dir, std::string name);
	Object(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 scle);
	Object(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, const std::string& texDir, const std::string& texName);
	Object(type type, glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex);
	Object(type type, glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, glm::vec2 collisionMinExtent, glm::vec2 collisionMaxExtent, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex);
	~Object();

	void Draw(glm::mat4 view, glm::mat4 proj);
	void Bind();
	void Unbind();
	unsigned int GetNumIndices();
	void PlayFrame(GLuint nextFrame);
	void SetUniformMat4(const std::string& name, glm::mat4 mat);

	void StrafeLeft(float deltaT, float movementSpeed);
	void StrafeRight(float deltaT, float movementSpeed);
	void MoveUp(float deltaT, float movementSpeed);
	void MoveDown(float deltaT, float movementSpeed);
};