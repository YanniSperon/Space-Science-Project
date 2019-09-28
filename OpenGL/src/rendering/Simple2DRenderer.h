#pragma once

#include <deque>
#include "Renderer2D.h"

class Simple2DRenderer : public Renderer2D {
private:
	std::deque<Object*> renderQueue;
public:
	void submit(Object* renderable, glm::vec3 camPos) override;
	void submitForceRender(Object* renderable);
	void flush(glm::mat4 view, glm::mat4 projection) override;
};