#include "vertex_buffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &obj_id);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &obj_id);
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, obj_id);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::buffer_data(const void* data, size_t size, unsigned int usage) {
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}
