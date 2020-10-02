#ifndef RENDERER_H
#define RENDERER_H

#include "object.h"
#include "shader.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	void clear_color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f) const;
	void clear() const;
	void render(const Object* object, const Shader& shader) const;
};

#endif // !RENDERER_H
