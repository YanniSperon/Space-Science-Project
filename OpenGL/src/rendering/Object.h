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
public:
	Object();
	Object(type type, std::string dir, std::string name);
	Object(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans);
	Object(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, const std::string& texDir, const std::string& texName);
	~Object();

	void Draw(glm::mat4 view, glm::mat4 proj);
	void Bind();
	void Unbind();
	unsigned int GetNumIndices();
	///*void ChangeShape(ShapeData newShape);*/
	void SetUniformMat4(const std::string& name, glm::mat4 mat);
};