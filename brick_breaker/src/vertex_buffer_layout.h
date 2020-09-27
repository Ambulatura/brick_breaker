#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <vector>
#include <glad/glad.h>
#include <iostream>

struct VertexBufferLayoutElement {
	unsigned int count;
	unsigned int type;
	unsigned char normalized;

	static unsigned int get_type_size(unsigned int type) {
		switch (type) {
		case GL_FLOAT:			return sizeof(float);
		case GL_UNSIGNED_INT:	return sizeof(unsigned int);
		case GL_UNSIGNED_BYTE:	return sizeof(unsigned char);
		}
		std::cout << "[VertexBufferLayoutElement] Type error!" << std::endl;
		exit(-1);
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferLayoutElement> elements;
	unsigned int stride;

public:
	VertexBufferLayout();
	~VertexBufferLayout();

	void add(unsigned int count, unsigned int type, unsigned char normalized);

	const std::vector<VertexBufferLayoutElement> get_elements() const;
	const unsigned int get_stride() const;
};

#endif // !VERTEX_BUFFER_LAYOUT_H
