#include "collision.h"

Collision::Collision() {
}

Collision::~Collision() {
}

void Collision::collision(Ball& ball, Bricks& bricks, Bar& bar) {
	for (uint32_t i = 0; i < bricks.elements.size(); i++) {
		Brick& brick = bricks.elements[i];
		if (brick.life > 0) {
			auto collision_info = Collision::check_collision(ball, brick.rect);
			auto[is_collision, direction, difference] = collision_info;
			if (is_collision) {
				if (Direction::Left == direction || Direction::Right == direction) {
					ball.velocity_x = -ball.velocity_x;
					float penetration = ball.radius - std::abs(difference.x);
					if (Direction::Left == direction)
						ball.change_position(penetration, 0.0f);
					else
						ball.change_position(-penetration, 0.0f);
				}
				else {
					ball.velocity_y = -ball.velocity_y;
					float penetration = ball.radius - std::abs(difference.y);
					if (Direction::Down == direction)
						ball.change_position(0.0f, penetration);
					else
						ball.change_position(0.0f, -penetration);
				}
				brick.life -= 1;
				bricks.refresh_vertices();
			}
		}
	}

	auto collision_info = Collision::check_collision(ball, bar.rect);
	auto [is_collision, direction, difference] = collision_info;
	if (is_collision) {
		if (Direction::Down == direction)
			ball.velocity_y = -ball.velocity_y;
		/*std::cout << is_collision << std::endl;
		float center_board = (bar.rect.right - bar.rect.left) / 2.0f;
		float distance = ball.center_x - center_board;
		float percentage = distance / bar.bar_width;
		float strength = 2.0f;
		glm::vec2 velocity(ball.velocity_x, ball.velocity_y);
		glm::vec2 old_velocity(ball.velocity_x, ball.velocity_y);
		velocity.x = velocity.x * percentage * strength;
		velocity.y = -velocity.y;
		velocity = glm::normalize(velocity) * glm::length(old_velocity);
		ball.velocity_x = velocity.x;
		ball.velocity_y = -old_velocity.y;
		std::cout << old_velocity.y << std::endl;
		std::cout << ball.velocity_x << std::endl;
		std::cout << ball.velocity_y << std::endl;*/
	}
}

std::tuple<bool, Direction, glm::vec2> Collision::check_collision(const Ball& ball, const Rectangle& rect) {
	glm::vec2 half_extents((rect.right - rect.left) / 2.0f, (rect.top - rect.bottom) / 2.0f);
	glm::vec2 brick_center(rect.left + half_extents.x, rect.bottom + half_extents.y);
	glm::vec2 difference(ball.center_x - brick_center.x, ball.center_y - brick_center.y);
	glm::vec2 clamped = glm::clamp(difference, -half_extents, half_extents);
	glm::vec2 p = brick_center + clamped;
	difference = { p.x - ball.center_x, p.y - ball.center_y };

	if (glm::length(difference) < ball.radius)
		return std::make_tuple(true, check_direction(difference), difference);
	else
		return std::make_tuple(false, Direction::Left, difference);

}

Direction Collision::check_direction(glm::vec2& target) {
	glm::vec2 compass[] = {
		glm::vec2(-1.0f, 0.0f), // Left
		glm::vec2(1.0f,  0.0f), // Right
		glm::vec2(0.0f,  1.0f), // Up
		glm::vec2(0.0f, -1.0f), // Down
	};
	
	float value = 0.0f;
	uint32_t index = 0;
	for (uint32_t i = 0; i < 4; i++) {
		float dot = glm::dot(glm::normalize(target), compass[i]);
		if (dot > value) {
			value = dot;
			index = i;
		}
	}
	return (Direction)index;
}
