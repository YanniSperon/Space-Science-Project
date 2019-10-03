#pragma once
#include "Simple2DRenderer.h"
#include "Object.h"

class ScoreDisplay {
private:
	std::vector<Object> ones;
	std::vector<Object> twos;
	std::vector<Object> threes;
	std::vector<Object> fours;
	std::vector<Object> fives;
	std::vector<Object> sixes;
	std::vector<Object> sevens;
	std::vector<Object> eights;
	std::vector<Object> nines;
	std::vector<Object> zeros;
	std::vector<glm::vec3> translations;
	glm::vec3 universalTrans;
	int maxValues = 5;
	int currentValue = 0;
public:
	ScoreDisplay();
	ScoreDisplay(glm::vec2 min, glm::vec2 max, int places, glm::vec3 trans, GLuint tex);
	~ScoreDisplay();
	
	void DisplayScore(int value, Simple2DRenderer& renderer);
	void DisplayScore(Simple2DRenderer& renderer);
	void SetScore(int value);

	void SetIsDisplayed(bool newValue);
	void TranslateVec3(glm::vec3 translation);
	void TranslateAddVec3(glm::vec3 translation);
};