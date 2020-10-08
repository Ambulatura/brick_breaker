#ifndef BRICKS_H
#define BRICKS_H

#include <vector>
#include "object.h"
#include "rectangle.h"

struct Brick {
	Rectangle rect;
	uint32_t life;
};

class Bricks : public Object {
public:
	std::vector<Brick> elements;

public:
	Bricks(float brick_w, float brick_h, float brick_h_offset, float brick_v_offset,
		   float l, float r, float b, float t,
		   float l_offset, float r_offset, float b_offset, float t_offset);
	Bricks(const Bricks& other) = delete;
	Bricks& operator=(const Bricks& other) = delete;
	~Bricks();

	void refresh_vertices();

private:
	float brick_width, brick_height, brick_horizontal_offset, brick_vertical_offset;
	float left, right, bottom, top;
	float left_offset, right_offset, bottom_offset, top_offset;
	uint32_t horizontal_brick_count;
	uint32_t vertical_brick_count;

private:
	void init() override;
	void set_vertex_positions() override;
	void set_vertex_indices() override;
	void set_primitive() override;
	void set_draw_type() override;
	void set_layout() override;
};

#endif // !BRICKS_H
