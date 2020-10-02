#include "ball.h"
#include "glm/glm.hpp"
#include "utils.h"

Ball::Ball(float cx, float cy, float rad, float l, float r, float b, float t) : 
	       center_x(cx), center_y(cy), radius(rad), left(l), right(r), bottom(b), top(t) {
	uint32_t random = random_number();
	float direction_x = 0.5f;
	float direction_y = 0.5f;
	float multiplier = 15.0f;
	velocity_x = (random % 2 == 0 ? direction_x * multiplier : -direction_x * multiplier);
	velocity_y = direction_y * multiplier;

	init();
}

Ball::~Ball() {}

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
	vertex_positions = positions;

	vertex_count = vertex_positions.size() / 2;
	vertex_size = 2 * vertex_count * sizeof(float);
}

void Ball::set_vertex_indices() {
	for (size_t i = 0; i < (vertex_count - 2); i++) {
		vertex_indices.push_back(0);
		vertex_indices.push_back(1 + i);
		vertex_indices.push_back(2 + i);
	}

	index_count = vertex_indices.size();
	index_size = index_count * sizeof(uint32_t);
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

/*enum class Direction {
	LEFT = 0,
	RIGHT = 1,
	BOTTOM = 2,
	TOP = 3,
};

Direction direction(glm::vec2 target) {
	glm::vec2 directions[] = {
		glm::vec2(-1.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, -1.0f),
		glm::vec2(0.0f, 1.0f),
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++) {
		float dot = glm::dot(glm::normalize(target), directions[i]);
		if (dot > max) {
			max = dot;
			best_match = i;
		}
	}
	return (Direction)best_match;
}*/

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

	/*for (size_t i = 0; i < bricks.elements.size(); i++) {
		Brick& brick = bricks.elements[i];
		glm::vec2 half_extents((brick.r - brick.l) / 2.0f, (brick.t - brick.b) / 2.0f);
		glm::vec2 brick_center(brick.l + half_extents.x, brick.b + half_extents.y);
		glm::vec2 difference(center_x - brick_center.x, center_y - brick_center.y);
		glm::vec2 clamped = glm::clamp(difference, -half_extents, half_extents);
		glm::vec2 closest = brick_center + clamped;
		difference = { closest.x - center_x, closest.y - center_y };

		if (glm::length(difference) < radius && brick.life > 0) {
			Direction direct = direction(difference);
			if (direct == Direction::LEFT || direct == Direction::RIGHT) {
				velocity_x = -velocity_x;
			}
			else if (direct == Direction::BOTTOM || direct == Direction::TOP) {
				velocity_y = -velocity_y;
			}
			brick.life -= 1;
			bricks.refresh_vertices();
		}
	}
	*/
}