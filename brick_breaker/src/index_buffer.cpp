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

void IndexBuffer::buffer_data(unsigned int* indices, size_t size, unsigned int usage) const {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
}
