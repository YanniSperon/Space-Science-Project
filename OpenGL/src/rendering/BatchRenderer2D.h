#pragma once
#include "Renderer2D.h"

#define RENDERER_MAX_SPRITES 10000
#define RENDERER_VERTEX_SIZE sizeof(float) * 8
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4;
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define	RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6;

class BatchRenderer2D : public Renderer2D {
private:
	GLuint vertexBufferID; // VBO can store 40,000 vertices
	GLuint indexBufferID; //IBO can store 60,000 indices
	GLsizei numIndices;
	Shader shader;
public:
	void submit(Object* renderable) override;
	void flush(glm::mat4 view, glm::mat4 projection) override;
};