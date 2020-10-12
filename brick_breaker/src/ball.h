#ifndef BALL_H
#define BALL_H

#include <vector>
#include "object.h"

class Ball : public Object {
public:
	float center_x, center_y;
	float radius;
	float velocity_x, velocity_y;
	bool stuck;
	std::vector<float> positions;
private:
	float left, right, bottom, top;

public:
	Ball(float cx, float cy, float rad, float l, float r, float b, float t);
	Ball(const Ball& other) = delete;
	Ball& operator=(const Ball& other) = delete;
	~Ball();

	void move();
	void change_position(float x=0.0f, float y=0.0f);

private:
	void init() override;
	void set_vertex_positions() override;
	void set_vertex_indices() override;
	void set_primitive() override;
	void set_draw_type() override;
	void set_layout() override;
};

#endif // !BALL_H
