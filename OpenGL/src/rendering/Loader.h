#pragma once
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <string>
#include "Vertex.h"

class Loader {
public:
	static GLuint loadSpriteSheet(const std::string texDir, const std::string texName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter);
	static texCoords getImageCoordinates(unsigned int bottomLeftSquareX, unsigned int bottomLeftSquareY, unsigned int topRightSquareX, unsigned int topRightSquareY, unsigned int maxSquaresX, unsigned int maxSquaresY);
};