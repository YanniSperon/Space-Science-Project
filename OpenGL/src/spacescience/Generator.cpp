#include "Generator.h"

void Generator::AddRandomMeteor(std::vector<CollidableSprite>& vec, texCoords texCoord, GLuint image)
{
	float rx = (float)((rand() / (float)RAND_MAX * 100) - 50);
	float ry = (float)((rand() / (float)RAND_MAX * 50) - 25);
	float rsx = (float)((rand() / (float)RAND_MAX * 0.25) + 0.25);
	float rsy = (float)((rand() / (float)RAND_MAX * 0.25) + 0.25);
	int randInt = (int)std::round((rand() / (double)RAND_MAX * 4));
	glm::vec2 bottomLeftTexCoord;
	glm::vec2 topRightTexCoord;

	if (randInt == 0 || randInt == 4) {
		bottomLeftTexCoord = texCoord.bottomLeft;
		topRightTexCoord = texCoord.topRight;
	}
	else if (randInt == 1) {
		bottomLeftTexCoord = texCoord.topRight;
		topRightTexCoord = texCoord.bottomLeft;
	}
	else if (randInt == 2) {
		bottomLeftTexCoord = glm::vec2(texCoord.topRight.x, texCoord.bottomLeft.y);
		topRightTexCoord = glm::vec2(texCoord.bottomLeft.x, texCoord.topRight.y);
	}
	else if (randInt == 3) {
		bottomLeftTexCoord = glm::vec2(texCoord.bottomLeft.x, texCoord.topRight.y);
		topRightTexCoord = glm::vec2(texCoord.topRight.x, texCoord.bottomLeft.y);
	}
	vec.push_back(CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(rx, ry, 0.0f), glm::vec3(rsx, rsy, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, bottomLeftTexCoord, topRightTexCoord, image, 0, rsx * rsy, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, CollidableSprite::BodyType::circle));
}

void Generator::AddRandomIncomingMeteor(std::vector<CollidableSprite>& vec, texCoords texCoord, GLuint image, GLuint value)
{
	float rx = ((value * 25.0f) + 25.0f);
	float ry = (float)((rand() / (float)RAND_MAX * 5 * ((float)value) * ((float)value)) - 2.5 * ((float)value) * ((float)value));
	float rsx = (float)((rand() / (float)RAND_MAX * 1.0) + 0.5);
	float rsy = (float)((rand() / (float)RAND_MAX * 1.0) + 0.5);
	int randInt = (int)std::round((rand() / (double)RAND_MAX * 4));
	glm::vec2 bottomLeftTexCoord;
	glm::vec2 topRightTexCoord;

	if (randInt == 0 || randInt == 4) {
		bottomLeftTexCoord = texCoord.bottomLeft;
		topRightTexCoord = texCoord.topRight;
	}
	else if (randInt == 1) {
		bottomLeftTexCoord = texCoord.topRight;
		topRightTexCoord = texCoord.bottomLeft;
	}
	else if (randInt == 2) {
		bottomLeftTexCoord = glm::vec2(texCoord.topRight.x, texCoord.bottomLeft.y);
		topRightTexCoord = glm::vec2(texCoord.bottomLeft.x, texCoord.topRight.y);
	}
	else if (randInt == 3) {
		bottomLeftTexCoord = glm::vec2(texCoord.bottomLeft.x, texCoord.topRight.y);
		topRightTexCoord = glm::vec2(texCoord.topRight.x, texCoord.bottomLeft.y);
	}
	float vel = -5.0f - (0.1f * ((float)value));

	glm::vec3 changeInValues = glm::vec3(rx + 4.0f, ry, 0.0f);
	glm::vec3 normalizedChangeInValues = glm::normalize(changeInValues);

	float xVel = normalizedChangeInValues.x * vel;
	float yVel = normalizedChangeInValues.y * vel;

	vec.push_back(CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(rx, ry, 0.0f), glm::vec3(rsx, rsy, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.002f, bottomLeftTexCoord, topRightTexCoord, image, 0, rsx * rsy, glm::vec3(xVel, yVel, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, CollidableSprite::BodyType::circle));
}

void Generator::AddRandomIncomingMeteorFast(std::vector<CollidableSprite>& vec, texCoords texCoord, GLuint image, GLuint value)
{
	float rx = (((float)value * 25.0f) + 10.0f);
	float ry = (float)((rand() / (float)RAND_MAX * 5 * ((float)value) * ((float)value)) - 2.5 * ((float)value) * ((float)value));
	float rsx = (float)((rand() / (float)RAND_MAX * 1.0) + 0.5);
	float rsy = (float)((rand() / (float)RAND_MAX * 1.0) + 0.5);
	int randInt = (int)std::round((rand() / (double)RAND_MAX * 4));
	glm::vec2 bottomLeftTexCoord;
	glm::vec2 topRightTexCoord;

	if (randInt == 0 || randInt == 4) {
		bottomLeftTexCoord = texCoord.bottomLeft;
		topRightTexCoord = texCoord.topRight;
	}
	else if (randInt == 1) {
		bottomLeftTexCoord = texCoord.topRight;
		topRightTexCoord = texCoord.bottomLeft;
	}
	else if (randInt == 2) {
		bottomLeftTexCoord = glm::vec2(texCoord.topRight.x, texCoord.bottomLeft.y);
		topRightTexCoord = glm::vec2(texCoord.bottomLeft.x, texCoord.topRight.y);
	}
	else if (randInt == 3) {
		bottomLeftTexCoord = glm::vec2(texCoord.bottomLeft.x, texCoord.topRight.y);
		topRightTexCoord = glm::vec2(texCoord.topRight.x, texCoord.bottomLeft.y);
	}
	float vel = -10.0f - (2.0f * ((float)value));

	glm::vec3 changeInValues = glm::vec3(rx + 4.0f, ry, 0.0f);
	glm::vec3 normalizedChangeInValues = glm::normalize(changeInValues);

	float xVel = normalizedChangeInValues.x * vel;
	float yVel = normalizedChangeInValues.y * vel;

	vec.push_back(CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(rx, ry, 0.0f), glm::vec3(rsx, rsy, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.002f, bottomLeftTexCoord, topRightTexCoord, image, 0, rsx * rsy, glm::vec3(xVel, yVel, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, CollidableSprite::BodyType::circle));
}

void Generator::AddPool(std::vector<CollidableSprite>& vec, texCoords texCoord, GLuint image, GLuint value)
{
	float xPos = (float)((rand() / (float)RAND_MAX * 10) - 5);
	vec.push_back(CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(xPos, ((float)value) * 10.0f + 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-1.0f, -0.5f), glm::vec2(1.0f, 0.5f), 0.0f, texCoord.bottomLeft, texCoord.topRight, image, 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, -0.75f, 0.0f), 1.0f, CollidableSprite::BodyType::rectangle));
}
