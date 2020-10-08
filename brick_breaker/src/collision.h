#ifndef COLLISION_H
#define COLLISION_H

#include "ball.h"
#include "bricks.h"
#include "bar.h"
#include "glm/glm.hpp"
#include <tuple>

enum Direction {
	Left, Right,
	Up, Down
};

class Collision {
public:
	Collision();
	~Collision();

	static void collision(Ball& ball, Bricks& bricks, Bar& bar);
	
private:
	static std::tuple<bool, Direction, glm::vec2> check_collision(const Ball& ball, const Rectangle& rect);
	static Direction check_direction(glm::vec2& target);
};

#endif // !COLLISION_H
