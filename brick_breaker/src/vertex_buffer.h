#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <cstdint>

class VertexBuffer {
private:
	uint32_t obj_id;

public:
	VertexBuffer();
	~VertexBuffer();

	void bind() const;
	void unbind() const;

	void buffer_data(const void* data, uint32_t size, uint32_t usage) const;
};

#endif // !VERTEX_BUFFER_H
