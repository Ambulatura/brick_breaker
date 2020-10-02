#include "renderer.h"
#include <glad/glad.h>

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::clear_color(float r, float g, float b, float a) const {
	glClearColor(r, g, b, a);
}

void Renderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(const Object* object, const Shader& shader) const {
	shader.bind();
	object->vao.bind();
	object->vbo.bind();
	object->ebo.bind();
	object->vbo.buffer_data(object->get_vertex_positions(), object->get_vertex_size(), object->get_draw_type());
	object->ebo.buffer_data(const_cast<uint32_t*>(object->get_vertex_indices()), object->get_index_size(), object->get_draw_type());
	object->vao.add_attribute(object->vbo, object->layout);

	glDrawElements(object->get_primitive(), object->get_index_count(), GL_UNSIGNED_INT, 0);

	shader.unbind();
	object->vao.unbind();
	object->vbo.unbind();
	object->ebo.unbind();
}