#ifndef BRICKS_H
#define BRICKS_H

#include <vector>
#include <malloc.h>

struct Brick {
	float l, r, b, t;
	unsigned int life;
};

class Bricks {
public:
	std::vector<Brick> brick_list;

private:
	float* brick_positions;
	unsigned int* brick_indices;
	size_t position_size;
	size_t index_size;
	size_t position_count;
	size_t index_count;

public:
	Bricks();
	~Bricks();

	size_t get_position_size() const;
	size_t get_index_size() const;
	size_t get_position_count() const;
	size_t get_index_count() const;
	float* get_bricks_positions() const;
	unsigned int* get_bricks_indices() const;
	void generate(float brick_width, float brick_height, float brick_horizontal_offset, float brick_vertical_offset,
				  float left, float right, float bottom, float top,
				  float left_offset, float right_offset, float bottom_offset, float top_offset);
};

#endif // !BRICKS_H
