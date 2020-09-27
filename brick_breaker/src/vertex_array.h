#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "vertex_buffer_layout.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

class VertexArray {
private:
	unsigned int obj_id;

public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	void add_attribute(const VertexBuffer& vertex_buffer, const IndexBuffer& index_buffer, const VertexBufferLayout& layout) const;
};

#endif // !VERTEX_ARRAY_H
