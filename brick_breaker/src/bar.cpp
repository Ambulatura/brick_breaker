#include "bar.h"

Bar::Bar(float bar_w, float bar_h, float bar_b_offset, float l, float r, float b, float t) : 
	bar_width(bar_w), bar_height(bar_h), bar_bottom_offset(bar_b_offset), left(l), right(r), bottom(b), top(t) {
	init();
}

Bar::~Bar() {}

void Bar::init() {
	float screen_center_x = (right - left) / 2.0f;
	float half_bar_width = bar_width / 2.0f;
	//float half_bar_height = bar_height / 2.0f;
	float bar[8] = {
		screen_center_x - half_bar_width, bar_bottom_offset,
		screen_center_x + half_bar_width, bar_bottom_offset,
		screen_center_x + half_bar_width, bar_height + bar_bottom_offset,
		screen_center_x - half_bar_width, bar_height + bar_bottom_offset,
	};
	for (uint32_t i = 0; i < 8; i++) {
		positions.push_back(bar[i]);
	}

	set_vertex_positions();
	set_vertex_indices();
	set_primitive();
	set_draw_type();
	set_layout();
}

void Bar::set_vertex_positions() {
	if (vertex_positions == nullptr) {
		vertex_size = positions.size() * sizeof(float);
		vertex_positions = new float[vertex_size];
	}

	for (uint32_t i = 0; i < positions.size(); i++)
		vertex_positions[i] = positions[i];
}

void Bar::set_vertex_indices() {
	if (vertex_indices == nullptr) {
		index_count = 6;
		index_size = index_count * sizeof(uint32_t);
		vertex_indices = new uint32_t[index_size];
	}
	vertex_indices[0] = 0;
	vertex_indices[1] = 1;
	vertex_indices[2] = 2;
	vertex_indices[3] = 2;
	vertex_indices[4] = 3;
	vertex_indices[5] = 0;
}

void Bar::set_primitive() {
	primitive = GL_TRIANGLES;
}

void Bar::set_draw_type() {
	draw_type = GL_DYNAMIC_DRAW;
}

void Bar::set_layout() {
	layout.add(2, GL_FLOAT, GL_FALSE);
}
