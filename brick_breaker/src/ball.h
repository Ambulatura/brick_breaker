#ifndef BALL_H
#define BALL_H

class Ball {
public:
	float center_x;
	float center_y;
	float radius;

public:
	Ball(float cx, float cy, float r);

	void create();
	size_t get_vertex_size() const;
	size_t get_vertex_count() const;
	size_t get_index_count() const;
	size_t get_index_size() const;
	const float* get_vertex_positions() const;
	const unsigned int* get_vertex_indices() const;
	void move(float left, float right, float bottom, float top);

private:
	float velocity_x;
	float velocity_y;
	size_t vertex_size;
	size_t vertex_count;
	float* vertex_positions;
	size_t index_size;
	size_t index_count;
	unsigned int* vertex_indices;
};

#endif // !BALL_H
