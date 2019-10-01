#pragma once
#include "CollidableSprite.h"

class Generator {
public:
	static void AddRandomMeteor(std::vector<CollidableSprite>& vec, texCoords texCoord, GLuint image);
	static void AddRandomIncomingMeteor(std::vector<CollidableSprite>& vec, texCoords texCoord, GLuint image, GLuint value);
	static void AddPool(std::vector<CollidableSprite>& vec, texCoords texCoord, GLuint image, GLuint value);
};