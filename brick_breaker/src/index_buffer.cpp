#include "index_buffer.h"
#include <glad/glad.h>

IndexBuffer::IndexBuffer() {
	glGenBuffers(1, &obj_id);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &obj_id);
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_id);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::buffer_data(uint32_t* indices, uint32_t size, uint32_t usage) const {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
}
