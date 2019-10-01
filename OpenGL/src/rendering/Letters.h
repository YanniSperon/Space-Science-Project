#pragma once
#include "Object.h"
#include "Simple2DRenderer.h"
#include "glm/glm.hpp"
class Letters {
private:
	std::vector<Object> letters;
public:
	Letters();
	Letters(std::string sentence, GLuint tex, GLuint lines, glm::vec2 min, glm::vec2 max);

	void SubmitForceRender(Simple2DRenderer& renderer);
	void Submit(Simple2DRenderer& renderer, glm::vec3 camPos);

	void SetIsDisplayed(bool newValue);

	~Letters();
};