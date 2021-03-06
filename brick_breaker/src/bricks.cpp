#include "bricks.h"

Bricks::Bricks(float brick_w, float brick_h, float brick_h_offset, float brick_v_offset,
			   float l, float r, float b, float t,
	           float l_offset, float r_offset, float b_offset, float t_offset) : 
               brick_width(brick_w), brick_height(brick_h), brick_horizontal_offset(brick_h_offset), brick_vertical_offset(brick_v_offset),
			   left(l), right(r), bottom(b), top(t),
			   left_offset(l_offset), right_offset(r_offset), bottom_offset(b_offset), top_offset(t_offset) {
	init();
}

Bricks::~Bricks() {
	delete[] vertex_positions;
	delete[] vertex_indices;
}

void Bricks::init() {

	left = left + left_offset;
	right = right - right_offset;
	bottom = bottom + bottom_offset;
	top = top - top_offset;

	uint32_t horizontal_brick_count = 0;
	uint32_t vertical_brick_count = 0;

	float total_width = right - left;
	while (true) {
		if (total_width == right - left) {
			horizontal_brick_count++;
			total_width -= brick_width;
		}
		else {
			total_width -= brick_width + brick_horizontal_offset;
			if (total_width <= 0) {
				break;
			}
			horizontal_brick_count++;
		}
	}
	total_width = brick_width + (brick_width + brick_horizontal_offset) * (horizontal_brick_count - 1);

	float total_height = top - bottom;
	while (true) {
		if (total_height == top - bottom) {
			vertical_brick_count++;
			total_height -= brick_height;
		}
		else {
			total_height -= brick_height + brick_vertical_offset;
			if (total_height <= 0) {
				break;
			}
			vertical_brick_count++;
		}
	}
	total_height = brick_height + (brick_height + brick_vertical_offset) * (vertical_brick_count - 1);

	float x_start_align = (right - left) / 2.0f - (total_width / 2.0f);
	float start_x = left + x_start_align;

	float y_start_align = (top - bottom) / 2.0f - (total_height / 2.0f);
	float start_y = top - y_start_align;

	float x = start_x;
	float y = start_y;

	for (uint32_t i = 0; i < vertical_brick_count; i++) {
		for (uint32_t j = 0; j < horizontal_brick_count; j++) {
			if (j == 0) {
				elements.push_back({ { x, x + brick_width, y - brick_height, y }, 1 });
				x += brick_width;
			}
			else {
				elements.push_back({ { x + brick_horizontal_offset, x + brick_width + brick_horizontal_offset, y - brick_height, y }, 1 });
				x += brick_width + brick_horizontal_offset;
			}
		}
		x = start_x;
		y -= brick_height + brick_vertical_offset;
	}

	set_vertex_positions();
	set_vertex_indices();
	set_primitive();
	set_draw_type();
	set_layout();
}

void Bricks::refresh_vertices() {
	set_vertex_positions();
	set_vertex_indices();
}

void Bricks::set_vertex_positions() {
	if (vertex_positions == nullptr) {
		vertex_size = (elements.size() * 8) * sizeof(float) * 16;
		vertex_positions = new float[elements.size() * 8 * 16];
	}

	uint32_t index = 0;
	for (uint32_t i = 0; i < elements.size(); i++) {
		Brick& br = elements[i];
		if (br.life > 0) {
			vertex_positions[index++] = br.rect.left;
			vertex_positions[index++] = br.rect.bottom;
			/*
			vertex_positions[index++] = 1.0f;
			vertex_positions[index++] = 0.4f;
			vertex_positions[index++] = 0.6f;
			vertex_positions[index++] = 0.99f;
			*/
			vertex_positions[index++] = 0.92f;
			vertex_positions[index++] = 0.94f;
			vertex_positions[index++] = 0.89f;
			vertex_positions[index++] = 0.99f;

			vertex_positions[index++] = br.rect.right;
			vertex_positions[index++] = br.rect.bottom;

			vertex_positions[index++] = 0.92f;
			vertex_positions[index++] = 0.94f;
			vertex_positions[index++] = 0.89f;
			vertex_positions[index++] = 0.99f;
									  	  
			vertex_positions[index++] = br.rect.right;
			vertex_positions[index++] = br.rect.top;
			/*
			vertex_positions[index++] = 0.5f;
			vertex_positions[index++] = 0.5f;
			vertex_positions[index++] = 0.6f;
			vertex_positions[index++] = 0.99f;
			*/
			vertex_positions[index++] = 0.796f;
			vertex_positions[index++] = 0.294f;
			vertex_positions[index++] = 0.086f;
			vertex_positions[index++] = 0.99f;

			vertex_positions[index++] = br.rect.left;
			vertex_positions[index++] = br.rect.top;
			/*
			vertex_positions[index++] = 0.796f;
			vertex_positions[index++] = 0.294f;
			vertex_positions[index++] = 0.086f;
			vertex_positions[index++] = 0.99f;
			*/
			vertex_positions[index++] = 0.796f;
			vertex_positions[index++] = 0.294f;
			vertex_positions[index++] = 0.086f;
			vertex_positions[index++] = 0.99f;
		}
	}
	if (vertex_positions != nullptr) {
		vertex_size = index * sizeof(float);
	}
}

void Bricks::set_vertex_indices() {
	if (vertex_indices == nullptr) {
		index_count = elements.size() * 6;
		index_size = index_count * sizeof(uint32_t);
		vertex_indices = new uint32_t[index_size];
	}
	uint32_t index = 0;
	uint32_t offset = 0;
	for (uint32_t i = 0; i < elements.size(); i++) {
		Brick& br = elements[i];

		if (br.life > 0) {
			vertex_indices[index++] = 0 + offset;
			vertex_indices[index++] = 1 + offset;
			vertex_indices[index++] = 2 + offset;
						  
			vertex_indices[index++] = 2 + offset;
			vertex_indices[index++] = 3 + offset;
			vertex_indices[index++] = 0 + offset;
			offset += 4;
		}
	}
	if (vertex_indices != nullptr) {
		index_count = index;
		index_size = index_count * sizeof(uint32_t);
	}
}

void Bricks::set_primitive() {
	primitive = GL_TRIANGLES;
}

void Bricks::set_draw_type() {
	draw_type = GL_DYNAMIC_DRAW;
}

void Bricks::set_layout() {
	layout.add(2, GL_FLOAT, GL_FALSE);
	layout.add(4, GL_FLOAT, GL_FALSE);
}
