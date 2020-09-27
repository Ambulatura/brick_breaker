#ifndef BALL_H
#define BALL_H

#include <malloc.h>
#include "glm/glm.hpp"

class Ball {
public:
	float center_x;
	float center_y;
	float radius;

public:
	Ball(float cx, float cy, float r);

	void create();
	const size_t get_vertex_size() const;
	const size_t get_vertex_count() const;
	const size_t get_index_count() const;
	const size_t get_index_size() const;
	float* get_vertex_positions() const;
	unsigned int* get_vertex_indices() const;
	void move(int left, int right, int bottom, int top);

private:
	float velocity_x;
	float velocity_y;
	size_t size;
	size_t vertex_count;
	float* vertex_positions;
	size_t index_size;
	size_t index_count;
	unsigned int* vertex_indices;
};

#endif // !BALL_H
