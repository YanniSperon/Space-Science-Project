#include "Object.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image/stb_image.h"

Object::Object()
	: Mesh(), vertexBufferID(0), indexBufferID(0), numIndices(0), texID(0)
{
}

Object::Object(type type, std::string dir, std::string name)
	: Mesh(type, dir, name), shader("res/shaders/Basic.shader"), texID(0), currentFrame(0)
{
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	stbi_set_flip_vertically_on_load(1);


	int width, height, nrChannels;
	std::string str = "blank.png";
	const char* c = str.c_str();
	unsigned char* data = stbi_load(c, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 6));


	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);

	numIndices = (GLsizei)GetShape().numIndices;

	GetShape().cleanUp();

	shader.Bind();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	shader.Unbind();
}

Object::Object(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 scle)
	: Mesh(type, dir, name, rot, trans, scle), shader("res/shaders/Basic.shader"), texID(0), currentFrame(0)
{
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	stbi_set_flip_vertically_on_load(1); 


	int width, height, nrChannels;
	std::string str = "blank.png";
	const char* c = str.c_str();
	unsigned char* data = stbi_load(c, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 6));


	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);

	numIndices = (GLsizei)GetShape().numIndices;

	GetShape().cleanUp();

	shader.Bind();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	shader.Unbind();
}

Object::Object(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, const std::string& texDir, const std::string& texName)
	: Mesh(type, dir, name, rot, trans, scle), shader("res/shaders/Basic.shader"), currentFrame(0)
{
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	stbi_set_flip_vertically_on_load(1);


	int width, height, nrChannels;
	std::string str = texDir + texName;
	const char* c = str.c_str();
	unsigned char* data = stbi_load(c, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 6));


	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);

	numIndices = (GLsizei)GetShape().numIndices;

	GetShape().cleanUp();
	stbi_image_free(data);

	shader.Bind();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	shader.Unbind();
}

Object::Object(type type, glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex)
	: Mesh(type, rot, trans, scle, minExtents, maxExtents, minExtents, maxExtents, z, bottomLeftTexCoord, topRightTexCoord), shader("res/shaders/Basic.shader"), texID(tex), currentFrame(0)
{
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 6));


	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);

	numIndices = (GLsizei)GetShape().numIndices;

	GetShape().cleanUp();

	shader.Bind();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	shader.Unbind();
}

Object::Object(type type, glm::vec3 rot, glm::vec3 trans, glm::vec3 scle, glm::vec2 collisionMinExtent, glm::vec2 collisionMaxExtent, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint& tex)
	: Mesh(type, rot, trans, scle, collisionMinExtent, collisionMaxExtent, minExtents, maxExtents, z, bottomLeftTexCoord, topRightTexCoord), shader("res/shaders/Basic.shader"), texID(tex), currentFrame(0)
{
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, GetShape().vertexBufferSize(), GetShape().vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 6));


	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetShape().indexBufferSize(), GetShape().indices, GL_STATIC_DRAW);

	numIndices = (GLsizei)GetShape().numIndices;

	GetShape().cleanUp();

	shader.Bind();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	shader.Unbind();
}

Object::~Object()
{

}

void Object::Draw(glm::mat4 view, glm::mat4 proj)
{
	Bind();
	glm::mat4 MVP = proj * view * GetModelTransformMatrix();
	shader.SetUniformMat4f("MVP", MVP);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	Unbind();
}

void Object::Bind()
{
	glBindTexture(GL_TEXTURE_2D, texID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	shader.Bind();
}

void Object::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	shader.Unbind();
}

unsigned int Object::GetNumIndices()
{
	return numIndices;
}

void Object::PlayFrame(GLuint nextFrame)
{
	texID = nextFrame;
}

void Object::SetUniformMat4(const std::string& name, glm::mat4 mat)
{
	shader.SetUniformMat4f(name, mat);
}

void Object::StrafeLeft(float deltaT, float movementSpeed)
{
	TranslateSubtract3f((movementSpeed / 0.007777) * deltaT, 0.0f, 0.0f);
}

void Object::StrafeRight(float deltaT, float movementSpeed)
{
	TranslateAdd3f((movementSpeed / 0.007777) * deltaT, 0.0f, 0.0f);
}

void Object::MoveUp(float deltaT, float movementSpeed)
{
	TranslateAdd3f(0.0f, (movementSpeed / 0.007777) * deltaT, 0.0f);
}

void Object::MoveDown(float deltaT, float movementSpeed)
{
	TranslateSubtract3f(0.0f, (movementSpeed / 0.007777) * deltaT, 0.0f);
}