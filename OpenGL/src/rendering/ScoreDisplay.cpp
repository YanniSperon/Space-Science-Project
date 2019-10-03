#include "ScoreDisplay.h"
#include "Vertex.h"
#include "Loader.h"

ScoreDisplay::ScoreDisplay()
	: maxValues(5)
{

}

ScoreDisplay::ScoreDisplay(glm::vec2 min, glm::vec2 max, int places, glm::vec3 trans, GLuint tex)
	: maxValues(places)
{
	int valuesPerLine = places;
	float incrementX = (max.x - min.x) / valuesPerLine;
	int incrementXTimes = 0;
	int incrementYTimes = 0;
	glm::vec2 firstPos = glm::vec2(min.x, max.y);
	float deltaX = max.x - min.x;
	float deltaY = max.y - min.y;
	float sizeX = incrementX;
	float sizeY = deltaY;
	texCoords zeroTex = Loader::getImageCoordinates(1, 7, 2, 8, 8, 16);
	texCoords oneTex = Loader::getImageCoordinates(0, 8, 1, 9, 8, 16);
	texCoords twoTex = Loader::getImageCoordinates(1, 8, 2, 9, 8, 16);
	texCoords threeTex = Loader::getImageCoordinates(2, 8, 3, 9, 8, 16);
	texCoords fourTex = Loader::getImageCoordinates(3, 8, 4, 9, 8, 16);
	texCoords fiveTex = Loader::getImageCoordinates(4, 8, 5, 9, 8, 16);
	texCoords sixTex = Loader::getImageCoordinates(5, 8, 6, 9, 8, 16);
	texCoords sevenTex = Loader::getImageCoordinates(6, 8, 7, 9, 8, 16);
	texCoords eightTex = Loader::getImageCoordinates(7, 8, 8, 9, 8, 16);
	texCoords nineTex = Loader::getImageCoordinates(0, 7, 1, 8, 8, 16);

	// 0
	for (unsigned int i = 0; i < places; i++) {
		glm::vec3 pos = glm::vec3(firstPos.x + incrementX * incrementXTimes, firstPos.y, 0.0f) + trans;
		zeros.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), 0.004f, zeroTex.bottomLeft, zeroTex.topRight, tex));
		ones.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), 0.004f, oneTex.bottomLeft, oneTex.topRight, tex));
		twos.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), 0.004f, twoTex.bottomLeft, twoTex.topRight, tex));
		threes.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), 0.004f, threeTex.bottomLeft, threeTex.topRight, tex));
		fours.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), 0.004f, fourTex.bottomLeft, fourTex.topRight, tex));
		fives.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), 0.004f, fiveTex.bottomLeft, fiveTex.topRight, tex));
		sixes.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), 0.004f, sixTex.bottomLeft, sixTex.topRight, tex));
		sevens.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), 0.004f, sevenTex.bottomLeft, sevenTex.topRight, tex));
		eights.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), 0.004f, eightTex.bottomLeft, eightTex.topRight, tex));
		nines.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), glm::vec2(-sizeX / 2, -sizeY / 2), glm::vec2(sizeX / 2, sizeY / 2), 0.004f, nineTex.bottomLeft, nineTex.topRight, tex));
		translations.push_back(pos);
		incrementXTimes++;
	}
	incrementX = 0;
	currentValue = 0;
}

ScoreDisplay::~ScoreDisplay()
{

}

void ScoreDisplay::DisplayScore(int value, Simple2DRenderer& renderer)
{
	std::string stringRepresentation = std::to_string(value);
	for (unsigned int i = 0; i < stringRepresentation.size(); i++) {
		zeros[i].TranslateVec3(translations[i] + universalTrans);
		ones[i].TranslateVec3(translations[i] + universalTrans);
		twos[i].TranslateVec3(translations[i] + universalTrans);
		threes[i].TranslateVec3(translations[i] + universalTrans);
		fours[i].TranslateVec3(translations[i] + universalTrans);
		fives[i].TranslateVec3(translations[i] + universalTrans);
		sixes[i].TranslateVec3(translations[i] + universalTrans);
		sevens[i].TranslateVec3(translations[i] + universalTrans);
		eights[i].TranslateVec3(translations[i] + universalTrans);
		nines[i].TranslateVec3(translations[i] + universalTrans);
		char valueInPlace = stringRepresentation[i];
		switch (valueInPlace) {
		case '0':
			renderer.submitForceRender(&zeros[i]);
			break;
		case '1':
			renderer.submitForceRender(&ones[i]);
			break;
		case '2':
			renderer.submitForceRender(&twos[i]);
			break;
		case '3':
			renderer.submitForceRender(&threes[i]);
			break;
		case '4':
			renderer.submitForceRender(&fours[i]);
			break;
		case '5':
			renderer.submitForceRender(&fives[i]);
			break;
		case '6':
			renderer.submitForceRender(&sixes[i]);
			break;
		case '7':
			renderer.submitForceRender(&sevens[i]);
			break;
		case '8':
			renderer.submitForceRender(&eights[i]);
			break;
		case '9':
			renderer.submitForceRender(&nines[i]);
			break;
		default:
			printf("Unrecognized value\n");
			break;
		}
	}
}

void ScoreDisplay::DisplayScore(Simple2DRenderer& renderer)
{
	std::string stringRepresentation = std::to_string(currentValue);
	for (unsigned int i = 0; i < stringRepresentation.size(); i++) {
		zeros[i].TranslateVec3(translations[i] + universalTrans);
		ones[i].TranslateVec3(translations[i] + universalTrans);
		twos[i].TranslateVec3(translations[i] + universalTrans);
		threes[i].TranslateVec3(translations[i] + universalTrans);
		fours[i].TranslateVec3(translations[i] + universalTrans);
		fives[i].TranslateVec3(translations[i] + universalTrans);
		sixes[i].TranslateVec3(translations[i] + universalTrans);
		sevens[i].TranslateVec3(translations[i] + universalTrans);
		eights[i].TranslateVec3(translations[i] + universalTrans);
		nines[i].TranslateVec3(translations[i] + universalTrans);
		char valueInPlace = stringRepresentation[i];
		switch (valueInPlace) {
		case '0':
			renderer.submitForceRender(&zeros[i]);
			break;
		case '1':
			renderer.submitForceRender(&ones[i]);
			break;
		case '2':
			renderer.submitForceRender(&twos[i]);
			break;
		case '3':
			renderer.submitForceRender(&threes[i]);
			break;
		case '4':
			renderer.submitForceRender(&fours[i]);
			break;
		case '5':
			renderer.submitForceRender(&fives[i]);
			break;
		case '6':
			renderer.submitForceRender(&sixes[i]);
			break;
		case '7':
			renderer.submitForceRender(&sevens[i]);
			break;
		case '8':
			renderer.submitForceRender(&eights[i]);
			break;
		case '9':
			renderer.submitForceRender(&nines[i]);
			break;
		default:
			printf("Unrecognized value\n");
			break;
		}
	}
}

void ScoreDisplay::SetScore(int value)
{
	currentValue = value;
}

void ScoreDisplay::SetIsDisplayed(bool newValue)
{
	for (unsigned int i = 0; i < zeros.size(); i++) {
		ones[i].SetIsDisplayed(newValue);
		twos[i].SetIsDisplayed(newValue);
		threes[i].SetIsDisplayed(newValue);
		fours[i].SetIsDisplayed(newValue);
		fives[i].SetIsDisplayed(newValue);
		sixes[i].SetIsDisplayed(newValue);
		sevens[i].SetIsDisplayed(newValue);
		eights[i].SetIsDisplayed(newValue);
		nines[i].SetIsDisplayed(newValue);
		zeros[i].SetIsDisplayed(newValue);
	}
}

void ScoreDisplay::TranslateVec3(glm::vec3 translation)
{
	universalTrans = translation;
}

void ScoreDisplay::TranslateAddVec3(glm::vec3 translation)
{
	universalTrans += translation;
}