#ifndef BRICKS_H
#define BRICKS_H

#include <vector>

struct Brick {
	float l, r, b, t;
	unsigned int life;
};

class Bricks {
public:
	std::vector<Brick> brick_list;

private:
	float* vertex_positions;
	unsigned int* vertex_indices;
	size_t vertex_size;
	size_t index_size;
	size_t vertex_count;
	size_t index_count;

public:
	Bricks();
	~Bricks();

	size_t get_vertex_size() const;
	size_t get_index_size() const;
	size_t get_vertex_count() const;
	size_t get_index_count() const;
	const float* get_vertex_positions() const;
	const unsigned int* get_vertex_indices() const;
	void generate(float brick_width, float brick_height, float brick_horizontal_offset, float brick_vertical_offset,
				  float left, float right, float bottom, float top,
				  float left_offset, float right_offset, float bottom_offset, float top_offset);
};

#endif // !BRICKS_H
