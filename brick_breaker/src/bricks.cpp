#include "bricks.h"
#include <malloc.h>

Bricks::Bricks() {}

Bricks::~Bricks() {}

size_t Bricks::get_vertex_size() const {
	return vertex_size;
}

size_t Bricks::get_index_size() const {
	return index_size;
}

size_t Bricks::get_vertex_count() const {
	return vertex_count;
}

size_t Bricks::get_index_count() const {
	return index_count;
}

const float* Bricks::get_vertex_positions() const {
	return vertex_positions;
}

const unsigned int* Bricks::get_vertex_indices() const {
	return vertex_indices;
}

void Bricks::generate(float brick_width, float brick_height, float brick_horizontal_offset, float brick_vertical_offset,
					  float left, float right, float bottom, float top,
					  float left_offset, float right_offset, float bottom_offset, float top_offset) {

	left = left + left_offset;
	right = right - right_offset;
	bottom = bottom + bottom_offset;
	top = top - top_offset;

	unsigned int horizontal_brick_count = 0;
	unsigned int vertical_brick_count = 0;

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

	for (size_t i = 0; i < vertical_brick_count; i++) {
		for (size_t j = 0; j < horizontal_brick_count; j++) {
			if (j == 0) {
				brick_list.push_back({ x, x + brick_width, y - brick_height, y, 1 });
				x += brick_width;
			}
			else {
				brick_list.push_back({ x + brick_horizontal_offset, x + brick_width + brick_horizontal_offset, y - brick_height, y, 1 });
				x += brick_width + brick_horizontal_offset;
			}
		}
		x = start_x;
		y -= brick_height + brick_vertical_offset;
	}

	vertex_count = horizontal_brick_count * vertical_brick_count * 8;
	vertex_size = vertex_count * sizeof(float);
	vertex_positions = (float*)_malloca(vertex_size);
	
	
	for (size_t i = 0; i < horizontal_brick_count * vertical_brick_count; i++) {
		Brick& br = brick_list[i];
		vertex_positions[i * 8 + 0] = br.l;
		vertex_positions[i * 8 + 1] = br.b;

		vertex_positions[i * 8 + 2] = br.r;
		vertex_positions[i * 8 + 3] = br.b;

		vertex_positions[i * 8 + 4] = br.r;
		vertex_positions[i * 8 + 5] = br.t;

		vertex_positions[i * 8 + 6] = br.l;
		vertex_positions[i * 8 + 7] = br.t;
	}

	index_count = horizontal_brick_count * vertical_brick_count * 6;
	index_size = index_count * sizeof(unsigned int);
	vertex_indices = (unsigned int*)_malloca(index_size);

	unsigned int index_offset = 0;
	for (size_t i = 0; i < horizontal_brick_count * vertical_brick_count; i++) {
		vertex_indices[i * 6 + 0] = 0 + index_offset;
		vertex_indices[i * 6 + 1] = 1 + index_offset;
		vertex_indices[i * 6 + 2] = 2 + index_offset;
		vertex_indices[i * 6 + 3] = 2 + index_offset;
		vertex_indices[i * 6 + 4] = 3 + index_offset;
		vertex_indices[i * 6 + 5] = 0 + index_offset;

		index_offset += 4;
	}
}