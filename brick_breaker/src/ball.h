#ifndef BALL_H
#define BALL_H

#include <malloc.h>
#include "glm/glm.hpp"

class Ball {
public:
	Ball(float cx, float cy, float r);

	const size_t get_size() const;
	const size_t get_vertex_count() const;
	float* get_vertex_positions() const;

public:
	float center_x;
	float center_y;
	float radius;

private:
	size_t size;
	size_t vertex_count;
	float* vertex_positions;
};

#endif // !BALL_H
