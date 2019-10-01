#include "Loader.h"
#include "stb_image/stb_image.h"

GLuint Loader::loadSpriteSheet(const std::string texDir, const std::string texName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter) {
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	stbi_set_flip_vertically_on_load(1);

	int width, height, nrChannels;
	std::string str = texDir + texName;
	const char* c = str.c_str();
	unsigned char* data = stbi_load(c, &width, &height, &nrChannels, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureMaxFilter);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture!\n");
	}
	return texID;
}
texCoords Loader::getImageCoordinates(unsigned int bottomLeftSquareX, unsigned int bottomLeftSquareY, unsigned int topRightSquareX, unsigned int topRightSquareY, unsigned int maxSquaresX, unsigned int maxSquaresY) {
	texCoords answer;
	answer.bottomLeft = glm::vec2((float)bottomLeftSquareX / (float)maxSquaresX, (float)bottomLeftSquareY / (float)maxSquaresY);
	answer.topRight = glm::vec2((float)topRightSquareX / (float)maxSquaresX, (float)topRightSquareY / (float)maxSquaresY);
	return answer;
}