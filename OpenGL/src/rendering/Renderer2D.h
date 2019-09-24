#pragma once
#include "Object.h"
#include "GL/glew.h"
#include "glm/glm.hpp"

class Renderer2D {
public:
	virtual void submit(Object* renderable) = 0;
	virtual void flush(glm::mat4 view, glm::mat4 projection) = 0;
};