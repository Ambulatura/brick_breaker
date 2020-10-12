#include "bar.h"

Bar::Bar(float bar_w, float bar_h, float bar_b_offset, float l, float r, float b, float t) : 
	bar_width(bar_w), bar_height(bar_h), bar_bottom_offset(bar_b_offset), left(l), right(r), bottom(b), top(t) {
	velocity_x = 100.0f;
	init();
}

Bar::~Bar() {}

void Bar::init() {
	float screen_center_x = (right - left) / 2.0f;
	float half_bar_width = bar_width / 2.0f;
	rect.left = screen_center_x - half_bar_width;
	rect.right = screen_center_x + half_bar_width;
	rect.bottom = bar_bottom_offset;
	rect.top = bar_height + bar_bottom_offset;

	float bar[8] = {
		rect.left, rect.bottom,
		rect.right, rect.bottom,
		rect.right, rect.top,
		rect.left, rect.top,
	};

	/*float bar_colors[16] = {
		1.0f,   0.4f,   0.6f,   0.99f,
		0.92f,  0.94f,  0.89f,  0.99f,
		0.5f,   0.5f,   0.6f,   0.99f,
		0.796f, 0.294f, 0.086f, 0.99f,
	};*/

	float bar_colors[16] = {
		0.92f,  0.94f,  0.89f,  0.99f,
		0.92f,  0.94f,  0.89f,  0.99f,
		0.796f, 0.294f, 0.086f, 0.99f,
		0.796f, 0.294f, 0.086f, 0.99f,
	};
	
	for (uint32_t i = 0; i < 8; i++) {
		positions.push_back(bar[i]);
	}

	for (uint32_t i = 0; i < 16; i++) {
		colors.push_back(bar_colors[i]);
	}

	set_vertex_positions();
	set_vertex_indices();
	set_primitive();
	set_draw_type();
	set_layout();
}

void Bar::move_left() {
	rect.left -= velocity_x;
	rect.right -= velocity_x;
	for (uint32_t i = 0; i < positions.size(); i = i + 2) {
		positions[i] -= velocity_x;
	}

	set_vertex_positions();
}

void Bar::move_right() {
	rect.left += velocity_x;
	rect.right += velocity_x;
	for (uint32_t i = 0; i < positions.size(); i = i + 2) {
		positions[i] += velocity_x;
	}

	set_vertex_positions();
}

void Bar::set_vertex_positions() {
	if (vertex_positions == nullptr) {
		vertex_size = positions.size() * sizeof(float) * 4;
		vertex_positions = new float[positions.size() * 4];
	}

	uint32_t index = 0;
	uint32_t c_index = 0;
	uint32_t counter = 0;
	for (uint32_t i = 0; i < positions.size(); i++) {
		vertex_positions[index++] = positions[i];
		if (counter == 1) {
			vertex_positions[index++] = colors[c_index++];
			vertex_positions[index++] = colors[c_index++];
			vertex_positions[index++] = colors[c_index++];
			vertex_positions[index++] = colors[c_index++];
			counter = 0;
		}
		else {
			counter++;
		}
	}

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
	layout.add(4, GL_FLOAT, GL_FALSE);
}
