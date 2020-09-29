#include <iostream>
#include "ball.h"
#include "glm/glm.hpp"
#include "utils.h"
#include <malloc.h>

Ball::Ball(float cx, float cy, float r) : center_x(cx), center_y(cy), radius(r) {
	unsigned int random = random_number();
	float direction_x = 0.5;
	float direction_y = 0.5;
	float multiplier = 15.0f;
	velocity_x = (random % 2 == 0 ? direction_x * multiplier : -direction_x * multiplier);
	velocity_y = direction_y * multiplier;
}

void Ball::create() {
	size_t steps = 360;
	float step = 360.0f / float(steps);
	float angles = 0.0f;
	float x = center_x;
	float y = center_y;
	vertex_count = (steps + 1);
	vertex_size = 2 * vertex_count * sizeof(float);
	vertex_positions = (float*)_malloca(vertex_size);
	unsigned int index = 0;
	vertex_positions[index++] = x, vertex_positions[index++] = y;
	
	// Vertex positions
	for (size_t _ = 0; _ < steps; _++) {
		x = center_x + (radius * glm::cos(angles));
		y = center_y + (radius * glm::sin(angles));
		angles += step;
		vertex_positions[index++] = x, vertex_positions[index++] = y;
	}

	index_count = (steps - 1) * 3;
	index_size = index_count * sizeof(unsigned int);
	vertex_indices = (unsigned int*)_malloca(index_size);


	size_t counter = 0;
	index = 1;
	// Indices for GL_TRIANGLE_FAN
	for (size_t i = 0; i < index_count; i++) {
		if (counter == 0) {
			vertex_indices[i] = 0;
			counter++;
		}
		else if (counter == 1) {
			vertex_indices[i] = index++;
			counter++;
		}
		else if (counter == 2) {
			vertex_indices[i] = index;
			counter = 0;
		}
	}
}

size_t Ball::get_vertex_size() const {
	return vertex_size;
}

size_t Ball::get_index_count() const {
	return index_count;
}

size_t Ball::get_index_size() const {
	return index_size;
}

size_t Ball::get_vertex_count() const {
	return vertex_count;
}

const float* Ball::get_vertex_positions() const {
	return vertex_positions;
}

const unsigned int* Ball::get_vertex_indices() const {
	return vertex_indices;
}

void Ball::move(float left, float right, float bottom, float top) {
	if ((right - (center_x + radius)) < 1.0f) {
		velocity_x = -velocity_x;
	}
	else if (((center_x - radius) - left) < 1.0f) {
		velocity_x = -velocity_x;
	}
	else if ((top - (center_y + radius)) < -1.0f) {
		velocity_y = -velocity_y;
	}
	else if (((center_y - radius) - bottom) < 1.0f) {
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