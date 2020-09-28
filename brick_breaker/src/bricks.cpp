#include "bricks.h"

Bricks::Bricks() {}

Bricks::~Bricks() {
	_freea(brick_positions);
	_freea(brick_indices);
}

size_t Bricks::get_position_size() const {
	return position_size;
}

size_t Bricks::get_index_size() const {
	return index_size;
}

size_t Bricks::get_position_count() const
{
	return position_count;
}

size_t Bricks::get_index_count() const
{
	return index_count;
}

float* Bricks::get_bricks_positions() const
{
	return brick_positions;
}

unsigned int* Bricks::get_bricks_indices() const
{
	return brick_indices;
}

void Bricks::generate(float brick_width, float brick_height, float brick_horizontal_offset, float brick_vertical_offset,
	float left, float right, float bottom, float top,
	float left_offset, float right_offset, float bottom_offset, float top_offset) {

	left = left + left_offset;
	right = right - right_offset;
	bottom = bottom + bottom_offset;
	top = top - top_offset;

	size_t horizontal_brick_count = 0;
	size_t vertical_brick_count = 0;

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

	position_count = horizontal_brick_count * vertical_brick_count * 8;
	position_size = position_count * sizeof(float);
	brick_positions = (float*)_malloca(position_size);

	for (size_t i = 0; i < horizontal_brick_count * vertical_brick_count; i++) {
		Brick& br = brick_list[i];
		brick_positions[i * 8 + 0] = br.l;
		brick_positions[i * 8 + 1] = br.b;

		brick_positions[i * 8 + 2] = br.r;
		brick_positions[i * 8 + 3] = br.b;

		brick_positions[i * 8 + 4] = br.r;
		brick_positions[i * 8 + 5] = br.t;

		brick_positions[i * 8 + 6] = br.l;
		brick_positions[i * 8 + 7] = br.t;

	}

	index_count = horizontal_brick_count * vertical_brick_count * 6;
	index_size = index_count * sizeof(unsigned int);
	brick_indices = (unsigned int*)_malloca(index_size);

	size_t index_offset = 0;
	for (size_t i = 0; i < horizontal_brick_count * vertical_brick_count; i++) {
		brick_indices[i * 6 + 0] = 0 + index_offset;
		brick_indices[i * 6 + 1] = 1 + index_offset;
		brick_indices[i * 6 + 2] = 2 + index_offset;
		brick_indices[i * 6 + 3] = 2 + index_offset;
		brick_indices[i * 6 + 4] = 3 + index_offset;
		brick_indices[i * 6 + 5] = 0 + index_offset;
		index_offset += 4;
	}

	/*for (int i = 0; i < horizontal_brick_count * vertical_brick_count; i++) {
		std::cout << brick_indices[i * 6 + 0] << " " << brick_indices[i * 6 + 1] << " " << brick_indices[i * 6 + 2] << std::endl;
		std::cout << brick_indices[i * 6 + 3] << " " << brick_indices[i * 6 + 4] << " " << brick_indices[i * 6 + 5] << std::endl;
	}*/
}