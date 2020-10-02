#include "vertex_buffer_layout.h"
#include <glad/glad.h>

VertexBufferLayout::VertexBufferLayout() : stride(0) {}

VertexBufferLayout::~VertexBufferLayout() {}

void VertexBufferLayout::add(uint32_t count, uint32_t type, uint8_t normalized) {
	elements.push_back({ count, type, normalized });
	stride += count * VertexBufferLayoutElement::get_type_size(type);
}

const std::vector<VertexBufferLayoutElement> VertexBufferLayout::get_elements() const {
	return elements;
}

const uint32_t VertexBufferLayout::get_stride() const {
	return stride;
}