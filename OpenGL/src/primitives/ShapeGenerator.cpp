#include "ShapeGenerator.h"
#include "glm/glm.hpp"
#include "Vertex.h"
#include <fstream>
#include <string>
#include <vector>
#include <strstream>
#include <iostream>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a);

ShapeData ShapeGenerator::makeTriangle(glm::vec3& min, glm::vec3& max) {
	float minX = -INFINITY;
	float minY = -INFINITY;
	float minZ = -INFINITY;

	float maxX = -INFINITY;
	float maxY = -INFINITY;
	float maxZ = -INFINITY;

	ShapeData ret;

	Vertex positions[] = {
		glm::vec3(-1.0f, -1.0f, +0.0f),     // 0
		glm::vec3(+0.0f, +1.0f, +0.0f),
		glm::vec2(+0.0f, +0.0f),

		glm::vec3(+1.0f, -1.0f, +0.0f),      // 1
		glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec2(+0.0f, +0.0f),

		glm::vec3(+0.0f, +1.0f, +0.0f),      // 2
		glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec2(+0.0f, +0.0f),
	};
	minX = -1.0f;
	minY = -1.0f;
	minZ = +0.0f;

	min = glm::vec3(minX, minY, minZ);
	max = glm::vec3(maxX, maxY, maxZ);

	maxX = +1.0f;
	maxY = +1.0f;
	maxZ = +0.0f;

	ret.numVertices = NUM_ARRAY_ELEMENTS(positions);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, positions, sizeof(positions));

	GLuint indices[] = {
		0, 1, 2
	};
	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLuint[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}

ShapeData ShapeGenerator::makeCube(glm::vec3& min, glm::vec3& max)
{
	float minX = -INFINITY;
	float minY = -INFINITY;
	float minZ = -INFINITY;

	float maxX = -INFINITY;
	float maxY = -INFINITY;
	float maxZ = -INFINITY;
	
	ShapeData ret;

	Vertex positions[] = {
		glm::vec3(-0.5f, -0.5f, +0.0f), // 0
		glm::vec3(+1.0f, +0.0f, +0.0f), // color
		glm::vec2(+0.0f, +0.0f),        // texCoord

		glm::vec3(+0.5f, -0.5f, +0.0f), // 1
		glm::vec3(+0.0f, +1.0f, +0.0f), // color
		glm::vec2(+1.0f, +0.0f),        // texCoord

		glm::vec3(+0.5f, +0.5f, +0.0f), // 2
		glm::vec3(+0.0f, +0.0f, +1.0f), // color
		glm::vec2(+1.0f, +1.0f),        // texCoord

		glm::vec3(-0.5f, +0.5f, +0.0f), // 3
		glm::vec3(+1.0f, +1.0f, +1.0f), // color
		glm::vec2(+0.0f, +1.0f),        // texCoord
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(positions);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, positions, sizeof(positions));

	GLuint indices[] = {
		0, 1, 2, // Front face
		0, 2, 3
	};
	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLuint[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}

ShapeData ShapeGenerator::loadShape(std::string fileName, glm::vec3& min, glm::vec3& max)
{
	ShapeData ret;

	std::vector<Vertex> positions;
	std::vector<GLuint> indices;

	std::ifstream f(fileName);

	unsigned int positionsSize = 0;
	unsigned int indicesSize = 0;

	if (!f.is_open()) {
		return ret;
	}

	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);

		std::strstream s;
		s << line;

		char junk;

		if (line[0] == 'v')
		{
			glm::vec3 v;
			s >> junk >> v.x >> v.y >> v.z;
			Vertex vert;
			vert.position = v;
			vert.color = glm::vec3(1.0f, 1.0f, 1.0f);
			positions.push_back(vert);
			positionsSize += 1;
		}

		if (line[0] == 'f')
		{
			unsigned int f[3];
			s >> junk >> f[0] >> f[1] >> f[2];
			indices.push_back(f[0] - 1);
			indices.push_back(f[1] - 1);
			indices.push_back(f[2] - 1);
			indicesSize += 3;
		}
	}

	ret.numVertices = positionsSize;
	ret.vertices = new Vertex[positionsSize];
	for (unsigned int i = 0; i < positionsSize; i++) {
		ret.vertices[i] = positions[i];
	}

	ret.numIndices = indicesSize;
	ret.indices = new GLuint[indicesSize];
	for (unsigned int k = 0; k < indicesSize; k++) {
		ret.indices[k] = indices[k];
	}

	return ret;
}

ShapeData ShapeGenerator::loadTexturedShape(std::string directory, std::string name, glm::vec3& min, glm::vec3& max)
{
	ShapeData ret;

	std::vector<Vertex> positions;
	std::vector<GLuint> indices;
	std::vector<TexCoord> tempTex;

	std::string fileName = directory + name;

	std::ifstream obj(fileName);

	unsigned int positionsSize = 0;
	unsigned int indicesSize = 0;

	if (!obj.is_open()) {
		return ret;
	}

	std::string mtlName;

	while (!obj.eof())
	{
		char line[128];
		obj.getline(line, 128);

		std::strstream s;
		s << line;

		std::string str(line);

		char junk;
		char slash = '/';

		// Load materials from mtl file
		/*if (str.find("mtllib") != std::string::npos)
		{
			mtlName = str.substr(str.find("mtllib") + 7);
			std::cout << mtlName << std::endl;
			std::ifstream mtl(mtlName);

			std::string mtlFileName = directory + mtlName;

			bool fileLoadedProperly = true;

			if (!mtl.is_open()) {
				std::cout << "Error loading mtl file: \"" << mtlFileName << "\"\n";
				fileLoadedProperly = false;
			}
			while (!mtl.eof() && fileLoadedProperly)
			{
				char lineMTL[128];
				mtl.getline(lineMTL, 128);

				std::strstream sMTL;
				sMTL << lineMTL;

				std::string str(lineMTL);

				char junk;
				std::cout << "Loaded mtl file and grabbed line: " << lineMTL << "\n";
			}
		}*/
		// finished loading materials from mtl, now scan obj file for information referencing that file.
		//else if (str.find())
		/*else*/ if (line[0] == 'v' && line[1] == ' ')
		{
			glm::vec3 v;
			s >> junk >> v.x >> v.y >> v.z;
			Vertex vert;
			vert.position = v;
			vert.color = glm::vec3(1.0f, 0.0f, 1.0f);
			positions.push_back(vert);
			positionsSize += 1;
		}
		else if (line[0] == 'f' && line[1] == ' ')
		{
			unsigned int f[3];
			unsigned int uv[3];
			
			s >> junk >> f[0] >> slash >> uv[0] >>  f[1] >> slash >> uv[1] >> f[2] >> slash >> uv[2];
			indices.push_back(f[0] - 1);
			indices.push_back(f[1] - 1);
			indices.push_back(f[2] - 1);
			indicesSize += 3;
			positions[f[0] - 1].texCoord = glm::vec2(tempTex[uv[0] - 1].u, tempTex[uv[0] - 1].v);
			positions[f[1] - 1].texCoord = glm::vec2(tempTex[uv[1] - 1].u, tempTex[uv[1] - 1].v);
			positions[f[2] - 1].texCoord = glm::vec2(tempTex[uv[2] - 1].u, tempTex[uv[2] - 1].v);
		}
		else if (line[0] == 'v' && line[1] == 't') {
			float one;
			float two;
			std::string name;
			s >> name;
			s >> one;
			s >> two;
			TexCoord uv;
			uv.u = one;
			uv.v = two;
			tempTex.push_back(uv);
		}
	}

	ret.numVertices = positionsSize;
	ret.vertices = new Vertex[positionsSize];
	for (unsigned int i = 0; i < positionsSize; i++) {
		ret.vertices[i] = positions[i];
	}

	ret.numIndices = indicesSize;
	ret.indices = new GLuint[indicesSize];
	for (unsigned int k = 0; k < indicesSize; k++) {
		ret.indices[k] = indices[k];
	}

	return ret;
}

ShapeData ShapeGenerator::loadRectangle(std::string directory, std::string name, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord)
{
	float minX = -INFINITY;
	float minY = -INFINITY;
	float minZ = -INFINITY;

	float maxX = -INFINITY;
	float maxY = -INFINITY;
	float maxZ = -INFINITY;

	ShapeData ret;

	Vertex positions[] = {
		glm::vec3(-0.5f, -0.5f, +0.0f), // 0
		glm::vec3(+1.0f, +0.0f, +0.0f), // color
		glm::vec2(+bottomLeftTexCoord.x, +bottomLeftTexCoord.y),        // texCoord

		glm::vec3(+0.5f, -0.5f, +0.0f), // 1
		glm::vec3(+0.0f, +1.0f, +0.0f), // color
		glm::vec2(+topRightTexCoord.x, +bottomLeftTexCoord.y),        // texCoord

		glm::vec3(+0.5f, +0.5f, +0.0f), // 2
		glm::vec3(+0.0f, +0.0f, +1.0f), // color
		glm::vec2(+topRightTexCoord.x, +topRightTexCoord.y),        // texCoord

		glm::vec3(-0.5f, +0.5f, +0.0f), // 3
		glm::vec3(+1.0f, +1.0f, +1.0f), // color
		glm::vec2(+bottomLeftTexCoord.x, +topRightTexCoord.y),        // texCoord
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(positions);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, positions, sizeof(positions));

	GLuint indices[] = {
		0, 1, 2, // Front face
		0, 2, 3
	};
	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLuint[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}
