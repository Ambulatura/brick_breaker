#include "vertex_array.h"
#include <glad/glad.h>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &obj_id);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &obj_id);
}

void VertexArray::bind() const {
	glBindVertexArray(obj_id);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}

void VertexArray::add_attribute(const VertexBuffer& vertex_buffer, const IndexBuffer& index_buffer, const VertexBufferLayout& layout) const {
	bind();
	vertex_buffer.bind();
	index_buffer.bind();
	const auto& elements = layout.get_elements();
	const auto stride = layout.get_stride();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		auto element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, stride, (const void*)offset);
		offset += VertexBufferLayoutElement::get_type_size(element.type) * element.count;
	}
}
