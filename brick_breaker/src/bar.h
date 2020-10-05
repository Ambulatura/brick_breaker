#ifndef BAR_H
#define BAR_H

#include "object.h"
#include <vector>

class Bar : public Object {
public:
	float center_x, center_y;
	float bar_width, bar_height, bar_bottom_offset;
	float left, right, bottom, top;
	float velocity_x;
	float velocity_y;
	std::vector<float> positions;

public:
	Bar(float bar_w, float bar_h, float bar_b_offset, float l, float r, float b, float t);
	~Bar();

private:
	void init() override;
	void set_vertex_positions() override;
	void set_vertex_indices() override;
	void set_primitive() override;
	void set_draw_type() override;
	void set_layout() override;
};

#endif // !BAR_H
