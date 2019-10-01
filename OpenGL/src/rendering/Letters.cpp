#include "Letters.h"
#include "Loader.h"

Letters::Letters()
{

}

Letters::Letters(std::string sentence, GLuint tex, GLuint lines, glm::vec2 min, glm::vec2 max)
{
	int valuesPerLine = sentence.size() / lines;
	float incrementX = (max.x - min.x) / valuesPerLine;
	float incrementY = (max.y - min.y) / lines;
	printf("incrementX: %f\nincrementY: %f\n", incrementX, incrementY);
	int incrementXTimes = 0;
	int incrementYTimes = 0;
	glm::vec2 firstPos = glm::vec2(min.x, max.y);
	float deltaX = max.x - min.x;
	float deltaY = max.y - min.y;
	printf("deltaX: %f\ndeltaY: %f\n", deltaX, deltaY);
	float sizeX = deltaX * (incrementX/2);
	float sizeY = deltaY * (incrementY/2);
	printf("sizeX: %f\nsizeY: %f\n", sizeX, sizeY);
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	texCoords aTex = Loader::getImageCoordinates(0, 15, 1, 16, 8, 16);
	texCoords bTex = Loader::getImageCoordinates(2, 15, 3, 16, 8, 16);
	texCoords cTex = Loader::getImageCoordinates(4, 15, 5, 16, 8, 16);
	texCoords dTex = Loader::getImageCoordinates(6, 15, 7, 16, 8, 16);
	//////////////////////////////////////////////////////////////////
	texCoords eTex = Loader::getImageCoordinates(0, 14, 1, 15, 8, 16);
	texCoords fTex = Loader::getImageCoordinates(2, 14, 3, 15, 8, 16);
	texCoords gTex = Loader::getImageCoordinates(4, 14, 5, 15, 8, 16);
	texCoords hTex = Loader::getImageCoordinates(6, 14, 7, 15, 8, 16);
	//////////////////////////////////////////////////////////////////
	texCoords iTex = Loader::getImageCoordinates(0, 13, 1, 14, 8, 16);
	texCoords jTex = Loader::getImageCoordinates(2, 13, 3, 14, 8, 16);
	texCoords kTex = Loader::getImageCoordinates(4, 13, 5, 14, 8, 16);
	texCoords lTex = Loader::getImageCoordinates(6, 13, 7, 14, 8, 16);
	//////////////////////////////////////////////////////////////////
	texCoords mTex = Loader::getImageCoordinates(0, 12, 1, 13, 8, 16);
	texCoords nTex = Loader::getImageCoordinates(2, 12, 3, 13, 8, 16);
	texCoords oTex = Loader::getImageCoordinates(4, 12, 5, 13, 8, 16);
	texCoords pTex = Loader::getImageCoordinates(6, 12, 7, 13, 8, 16);
	//////////////////////////////////////////////////////////////////
	texCoords qTex = Loader::getImageCoordinates(0, 11, 1, 12, 8, 16);
	texCoords rTex = Loader::getImageCoordinates(2, 11, 3, 12, 8, 16);
	texCoords sTex = Loader::getImageCoordinates(4, 11, 5, 12, 8, 16);
	texCoords tTex = Loader::getImageCoordinates(6, 11, 7, 12, 8, 16);
	//////////////////////////////////////////////////////////////////
	texCoords uTex = Loader::getImageCoordinates(0, 10, 1, 11, 8, 16);
	texCoords vTex = Loader::getImageCoordinates(2, 10, 3, 11, 8, 16);
	texCoords wTex = Loader::getImageCoordinates(4, 10, 5, 11, 8, 16);
	texCoords xTex = Loader::getImageCoordinates(6, 10, 7, 11, 8, 16);
	//////////////////////////////////////////////////////////////////
	texCoords yTex = Loader::getImageCoordinates(0, 9, 1, 10, 8, 16);
	texCoords zTex = Loader::getImageCoordinates(2, 9, 3, 10, 8, 16);
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	texCoords ATex = Loader::getImageCoordinates(1, 15, 2, 16, 8, 16);
	texCoords BTex = Loader::getImageCoordinates(3, 15, 4, 16, 8, 16);
	texCoords CTex = Loader::getImageCoordinates(5, 15, 6, 16, 8, 16);
	texCoords DTex = Loader::getImageCoordinates(7, 15, 8, 16, 8, 16);
	//////////////////////////////////////////////////////////////////
	texCoords ETex = Loader::getImageCoordinates(1, 14, 2, 15, 8, 16);
	texCoords FTex = Loader::getImageCoordinates(3, 14, 4, 15, 8, 16);
	texCoords GTex = Loader::getImageCoordinates(5, 14, 6, 15, 8, 16);
	texCoords HTex = Loader::getImageCoordinates(7, 14, 8, 15, 8, 16);
	//////////////////////////////////////////////////////////////////
	texCoords ITex = Loader::getImageCoordinates(1, 13, 2, 14, 8, 16);
	texCoords JTex = Loader::getImageCoordinates(3, 13, 4, 14, 8, 16);
	texCoords KTex = Loader::getImageCoordinates(5, 13, 6, 14, 8, 16);
	texCoords LTex = Loader::getImageCoordinates(7, 13, 8, 14, 8, 16);
	//////////////////////////////////////////////////////////////////
	texCoords MTex = Loader::getImageCoordinates(1, 12, 2, 13, 8, 16);
	texCoords NTex = Loader::getImageCoordinates(3, 12, 4, 13, 8, 16);
	texCoords OTex = Loader::getImageCoordinates(5, 12, 6, 13, 8, 16);
	texCoords PTex = Loader::getImageCoordinates(7, 12, 8, 13, 8, 16);
	//////////////////////////////////////////////////////////////////
	texCoords QTex = Loader::getImageCoordinates(1, 11, 2, 12, 8, 16);
	texCoords RTex = Loader::getImageCoordinates(3, 11, 4, 12, 8, 16);
	texCoords STex = Loader::getImageCoordinates(5, 11, 6, 12, 8, 16);
	texCoords TTex = Loader::getImageCoordinates(7, 11, 8, 12, 8, 16);
	//////////////////////////////////////////////////////////////////
	texCoords UTex = Loader::getImageCoordinates(1, 10, 2, 11, 8, 16);
	texCoords VTex = Loader::getImageCoordinates(3, 10, 4, 11, 8, 16);
	texCoords WTex = Loader::getImageCoordinates(5, 10, 6, 11, 8, 16);
	texCoords XTex = Loader::getImageCoordinates(7, 10, 8, 11, 8, 16);
	//////////////////////////////////////////////////////////////////
	texCoords YTex = Loader::getImageCoordinates(1, 9, 2, 10, 8, 16);
	texCoords ZTex = Loader::getImageCoordinates(3, 9, 4, 10, 8, 16);
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	for (unsigned int i = 0; i < sentence.size(); i++) {
		if (i % valuesPerLine == 0) {
			incrementYTimes++;
			incrementXTimes = 0;
		}
		else {
			incrementXTimes++;
		}
		char letter = sentence[i];
		glm::vec3 pos = glm::vec3(firstPos.x + incrementX * incrementXTimes, firstPos.y - incrementY * incrementYTimes, 0.0f);
		switch (letter) {
		case 'a':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, aTex.bottomLeft, aTex.topRight, tex));
			break;
		case 'b':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, bTex.bottomLeft, bTex.topRight, tex));
			break;
		case 'c':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, cTex.bottomLeft, cTex.topRight, tex));
			break;
		case 'd':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, dTex.bottomLeft, dTex.topRight, tex));
			break;
		case 'e':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, eTex.bottomLeft, eTex.topRight, tex));
			break;
		case 'f':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, fTex.bottomLeft, fTex.topRight, tex));
			break;
		case 'g':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, gTex.bottomLeft, gTex.topRight, tex));
			break;
		case 'h':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, hTex.bottomLeft, hTex.topRight, tex));
			break;
		case 'i':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, iTex.bottomLeft, iTex.topRight, tex));
			break;
		case 'j':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, jTex.bottomLeft, jTex.topRight, tex));
			break;
		case 'k':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, kTex.bottomLeft, kTex.topRight, tex));
			break;
		case 'l':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, lTex.bottomLeft, lTex.topRight, tex));
			break;
		case 'm':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, mTex.bottomLeft, mTex.topRight, tex));
			break;
		case 'n':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, nTex.bottomLeft, nTex.topRight, tex));
			break;
		case 'o':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, oTex.bottomLeft, oTex.topRight, tex));
			break;
		case 'p':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, pTex.bottomLeft, pTex.topRight, tex));
			break;
		case 'q':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, qTex.bottomLeft, qTex.topRight, tex));
			break;
		case 'r':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, rTex.bottomLeft, rTex.topRight, tex));
			break;
		case 's':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, sTex.bottomLeft, sTex.topRight, tex));
			break;
		case 't':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, tTex.bottomLeft, tTex.topRight, tex));
			break;
		case 'u':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, uTex.bottomLeft, uTex.topRight, tex));
			break;
		case 'v':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, vTex.bottomLeft, vTex.topRight, tex));
			break;
		case 'w':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, wTex.bottomLeft, wTex.topRight, tex));
			break;
		case 'x':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, xTex.bottomLeft, xTex.topRight, tex));
			break;
		case 'y':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, yTex.bottomLeft, yTex.topRight, tex));
			break;
		case 'z':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, zTex.bottomLeft, zTex.topRight, tex));
			break;
		case 'A':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, ATex.bottomLeft, ATex.topRight, tex));
			break;
		case 'B':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, BTex.bottomLeft, BTex.topRight, tex));
			break;
		case 'C':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, CTex.bottomLeft, CTex.topRight, tex));
			break;
		case 'D':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, DTex.bottomLeft, DTex.topRight, tex));
			break;
		case 'E':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, ETex.bottomLeft, ETex.topRight, tex));
			break;
		case 'F':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, FTex.bottomLeft, FTex.topRight, tex));
			break;
		case 'G':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, GTex.bottomLeft, GTex.topRight, tex));
			break;
		case 'H':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, HTex.bottomLeft, HTex.topRight, tex));
			break;
		case 'I':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, ITex.bottomLeft, ITex.topRight, tex));
			break;
		case 'J':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, JTex.bottomLeft, JTex.topRight, tex));
			break;
		case 'K':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, KTex.bottomLeft, KTex.topRight, tex));
			break;
		case 'L':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, LTex.bottomLeft, LTex.topRight, tex));
			break;
		case 'M':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, MTex.bottomLeft, MTex.topRight, tex));
			break;
		case 'N':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, NTex.bottomLeft, NTex.topRight, tex));
			break;
		case 'O':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, OTex.bottomLeft, OTex.topRight, tex));
			break;
		case 'P':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, PTex.bottomLeft, PTex.topRight, tex));
			break;
		case 'Q':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, QTex.bottomLeft, QTex.topRight, tex));
			break;
		case 'R':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, RTex.bottomLeft, RTex.topRight, tex));
			break;
		case 'S':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, STex.bottomLeft, STex.topRight, tex));
			break;
		case 'T':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, TTex.bottomLeft, TTex.topRight, tex));
			break;
		case 'U':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, UTex.bottomLeft, UTex.topRight, tex));
			break;
		case 'V':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, VTex.bottomLeft, VTex.topRight, tex));
			break;
		case 'W':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, WTex.bottomLeft, WTex.topRight, tex));
			break;
		case 'X':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, XTex.bottomLeft, XTex.topRight, tex));
			break;
		case 'Y':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, YTex.bottomLeft, YTex.topRight, tex));
			break;
		case 'Z':
			letters.push_back(Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), glm::vec2(-sizeX/2, -sizeY/2), glm::vec2(sizeX/2, sizeY/2), 0.004f, ZTex.bottomLeft, ZTex.topRight, tex));
			break;
		default:
			printf("unrecognized character: %c\n", letter);
			break;
		}
	}
}

void Letters::SubmitForceRender(Simple2DRenderer& renderer)
{
	for (unsigned int i = 0; i < letters.size(); i++) {
		renderer.submitForceRender(&letters[i]);
	}
}

void Letters::Submit(Simple2DRenderer& renderer, glm::vec3 camPos)
{
	for (unsigned int i = 0; i < letters.size(); i++) {
		if (letters[i].IsDisplayed()) {
			renderer.submit(&letters[i], camPos);
		}
	}
}

void Letters::SetIsDisplayed(bool newValue)
{
	for (unsigned int i = 0; i < letters.size(); i++) {
		letters[i].SetIsDisplayed(newValue);
	}
}

Letters::~Letters()
{
}
