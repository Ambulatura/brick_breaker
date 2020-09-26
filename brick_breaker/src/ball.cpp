#include "ball.h"

Ball::Ball(float cx, float cy, float r) : center_x(cx), center_y(cy), radius(r) {
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