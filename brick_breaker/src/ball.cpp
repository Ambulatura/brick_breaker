#include "ball.h"
#include <iostream>
#include "utils.h"

Ball::Ball(float cx, float cy, float r) : center_x(cx), center_y(cy), radius(r) {
	unsigned int random = random_number();
	float direction_x = 0.5;
	float direction_y = 0.5;
	velocity_x = (random % 2 == 0 ? direction_x * 10.0f : -direction_x *10.0f);
	velocity_y = direction_y * 10.0f;
}

void Ball::create() {
	size_t steps = 360;
	float step = 360.0f / float(steps);
	float angles = 0.0f;
	float x = center_x;
	float y = center_y;
	vertex_count = (steps + 1);
	size = 2 * vertex_count * sizeof(float);
	vertex_positions = (float*)_malloca(size);
	size_t index = 0;
	vertex_positions[index++] = x, vertex_positions[index++] = y;
	for (size_t _ = 0; _ < steps; _++) {
		x = center_x + (radius * glm::cos(angles));
		y = center_y + (radius * glm::sin(angles));
		angles += step;
		vertex_positions[index++] = x, vertex_positions[index++] = y;
	}
}

const size_t Ball::get_size() const
{
	return size;
}

const size_t Ball::get_vertex_count() const
{
	return vertex_count;
}

float* Ball::get_vertex_positions() const
{
	return vertex_positions;
}

void Ball::move(int left, int right, int bottom, int top) {
	if ((right - (center_x + radius)) < 1.0f) {
		velocity_x = -velocity_x;
	} else if (((center_x - radius) - left) < 1.0f) {
		velocity_x = -velocity_x;
	} else if ((top - (center_y + radius)) < -1.0f) {
		velocity_y = -velocity_y;
	} else if (((center_y - radius) - bottom) < 1.0f) {
		velocity_y = -velocity_y;
	}

	for (size_t i = 0; i < vertex_count * 2; i++) {
		if (i % 2 == 0) {
			vertex_positions[i] += velocity_x;
		}
		else {
			vertex_positions[i] += velocity_y;
		}
	}
	
	center_x = vertex_positions[0];
	center_y = vertex_positions[1];
}
