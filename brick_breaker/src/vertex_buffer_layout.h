#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <vector>
#include <glad/glad.h>
#include <iostream>

struct VertexBufferLayoutElement {
	uint32_t count;
	uint32_t type;
	uint8_t normalized;

	static uint32_t get_type_size(uint32_t type) {
		switch (type) {
		case GL_FLOAT:			return sizeof(float);
		case GL_UNSIGNED_INT:	return sizeof(uint32_t);
		case GL_UNSIGNED_BYTE:	return sizeof(uint8_t);
		}
		std::cout << "[VertexBufferLayoutElement] Type error!" << std::endl;
		exit(-1);
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferLayoutElement> elements;
	uint32_t stride;

public:
	VertexBufferLayout();
	~VertexBufferLayout();

	void add(uint32_t count, uint32_t type, uint8_t normalized);

	const std::vector<VertexBufferLayoutElement> get_elements() const;
	const uint32_t get_stride() const;
};

#endif // !VERTEX_BUFFER_LAYOUT_H
