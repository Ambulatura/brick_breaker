#include "vertex_buffer_layout.h"
#include <glad/glad.h>

VertexBufferLayout::VertexBufferLayout() : stride(0) {}

VertexBufferLayout::~VertexBufferLayout() {}

void VertexBufferLayout::add(unsigned int count, unsigned int type, unsigned char normalized) {
	elements.push_back({ count, type, normalized });
	stride += count * VertexBufferLayoutElement::get_type_size(type);
}

const std::vector<VertexBufferLayoutElement> VertexBufferLayout::get_elements() const {
	return elements;
}

const unsigned int VertexBufferLayout::get_stride() const {
	return stride;
}