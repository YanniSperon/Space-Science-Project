#include "Simple2DRenderer.h"

void Simple2DRenderer::submit(Object* renderable)
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
