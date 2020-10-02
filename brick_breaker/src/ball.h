#ifndef BALL_H
#define BALL_H

#include <vector>
#include "object.h"

class Ball : public Object {
public:
	float center_x, center_y;
	float radius;
	float velocity_x, velocity_y;
private:
	float left, right, bottom, top;
	std::vector<float> positions;

public:
	Ball(float cx, float cy, float rad, float l, float r, float b, float t);
	~Ball();

	void move();

private:
	void init() override;
	void set_vertex_positions() override;
	void set_vertex_indices() override;
	void set_primitive() override;
	void set_draw_type() override;
	void set_layout() override;
};

#endif // !BALL_H
