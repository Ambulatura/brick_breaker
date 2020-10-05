#include "ball.h"
#include "glm/glm.hpp"
#include "utils.h"

Ball::Ball(float cx, float cy, float rad, float l, float r, float b, float t) : 
	       center_x(cx), center_y(cy), radius(rad), left(l), right(r), bottom(b), top(t) {
	uint32_t random = random_number();
	float direction_x = 0.5f;
	float direction_y = 0.5f;
	float multiplier = 22.5f;
	velocity_x = (random % 2 == 0 ? direction_x * multiplier : -direction_x * multiplier);
	velocity_y = direction_y * multiplier;

	init();
}

Ball::~Ball() {
	delete[] vertex_positions;
	delete[] vertex_indices;
}

void Ball::init() {
	uint32_t steps = 360;
	float step = 360.0f / float(steps);
	float angles = 0.0f;
	float x = center_x;
	float y = center_y;
	positions.push_back(x);
	positions.push_back(y);
	// Vertex positions
	for (uint32_t _ = 0; _ < steps; _++) {
		x = center_x + (radius * glm::cos(angles));
		y = center_y + (radius * glm::sin(angles));
		angles += step;

		positions.push_back(x);
		positions.push_back(y);
	}

	set_vertex_positions();
	set_vertex_indices();
	set_primitive();
	set_draw_type();
	set_layout();
}

void Ball::set_vertex_positions() {
	if (vertex_positions == nullptr) {
		vertex_size = positions.size() * sizeof(float);
		vertex_positions = new float[positions.size()];
	}

	for (uint32_t i = 0; i < positions.size(); i++) {
		vertex_positions[i] = positions[i];
	}
}

void Ball::set_vertex_indices() {
	if (vertex_indices == nullptr) {
		index_count = ((positions.size() / 2) - 2) * 3;
		index_size = index_count * sizeof(uint32_t);
		vertex_indices = new uint32_t[index_count];
	}
	uint32_t index = 0;
	for (uint32_t i = 0; i < (positions.size() / 2) - 2; i++) {
		vertex_indices[index++] = 0;
		vertex_indices[index++] = 1 + i;
		vertex_indices[index++] = 2 + i;
	}
}

void Ball::set_primitive() {
	primitive = GL_TRIANGLE_FAN;
}

void Ball::set_draw_type() {
	draw_type = GL_DYNAMIC_DRAW;
}

void Ball::set_layout() {
	layout.add(2, GL_FLOAT, GL_FALSE);
}

void Ball::move() {
	for (size_t i = 0; i < positions.size(); i++) {
		if (i % 2 == 0) {
			positions[i] += velocity_x;
		}
		else {
			positions[i] += velocity_y;
		}
	}
	center_x = positions[0];
	center_y = positions[1];

	set_vertex_positions();

	if (right - (center_x + radius) <= 1.0f) {
		velocity_x = -velocity_x;
	}
	else if ((center_x - radius) - left <= 1.0f) {
		velocity_x = -velocity_x;
	}
	if (top - (center_y + radius) <= 1.0f) {
		velocity_y = -velocity_y;
	}
	else if ((center_y - radius) - bottom <= 1.0f) {
		velocity_y = -velocity_y;
	}
}

void Ball::change_position(float x, float y) {
	if (x == 0.0f && y == 0.0f) return;
	for (uint32_t i = 0; i < positions.size(); i++) {
		if (i % 2 == 0)
			positions[i] += x;
		else
			positions[i] += y;
	}

	center_x = positions[0];
	center_y = positions[1];

}
