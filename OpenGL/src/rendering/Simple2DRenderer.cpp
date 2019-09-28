#include "Simple2DRenderer.h"

void Simple2DRenderer::submit(Object* renderable, glm::vec3 camPos)
{
	glm::vec3 changeInValues = renderable->GetTranslation() - camPos;
	float distanceSquared = changeInValues.x * changeInValues.x + changeInValues.y * changeInValues.y;
	if (distanceSquared < 50.0f*50.0f) {
		renderQueue.push_back(renderable);
	}
}

void Simple2DRenderer::submitForceRender(Object* renderable)
{
	renderQueue.push_back(renderable);
}

void Simple2DRenderer::flush(glm::mat4 view, glm::mat4 projection)
{
	while (!renderQueue.empty())
	{
		Object* renderable = renderQueue.front();
		renderable->Draw(view, projection);
		renderQueue.pop_front();
	}
}
