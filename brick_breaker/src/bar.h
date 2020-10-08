#ifndef BAR_H
#define BAR_H

#include <vector>
#include "object.h"
#include "rectangle.h"

class Bar : public Object {
public:
	float bar_width, bar_height, bar_bottom_offset;
	float velocity_x;
	Rectangle rect;
	std::vector<float> positions;
	std::vector<float> colors;

public:
	Bar(float bar_w, float bar_h, float bar_b_offset, float l, float r, float b, float t);
	Bar(const Bar& other) = delete;
	Bar& operator=(const Bar& other) = delete;
	~Bar();

	void move_left();
	void move_right();

private:
	void init() override;
	void set_vertex_positions() override;
	void set_vertex_indices() override;
	void set_primitive() override;
	void set_draw_type() override;
	void set_layout() override;

private:
	float left, right, bottom, top;
};

#endif // !BAR_H
