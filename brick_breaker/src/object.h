#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_buffer_layout.h"

class Object {
public:
	virtual ~Object();

	VertexArray vao;
	VertexBuffer vbo;
	IndexBuffer ebo;
	VertexBufferLayout layout;

protected:
	std::vector<float> vertex_positions;
	std::vector<uint32_t> vertex_indices;
	uint32_t vertex_size;
	uint32_t index_size;
	uint32_t vertex_count;
	uint32_t index_count;
	uint32_t primitive;
	uint32_t draw_type;

public:
	const float* get_vertex_positions() const;
	const uint32_t* get_vertex_indices() const;
	uint32_t get_vertex_size() const;
	uint32_t get_index_size() const;
	uint32_t get_vertex_count() const;
	uint32_t get_index_count() const;
	uint32_t get_primitive() const;
	uint32_t get_draw_type() const;

private:
	virtual void init() = 0;
	virtual void set_vertex_positions() = 0;
	virtual void set_vertex_indices() = 0;
	virtual void set_primitive() = 0;
	virtual void set_draw_type() = 0;
	virtual void set_layout() = 0;
};

#endif // !OBJECT_H
