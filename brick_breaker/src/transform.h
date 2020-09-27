#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

struct Frame {
	float left, right, bottom, top;
};

class Transform {
public:
	static Frame align_origin_to_center(int screen_width, int screen_height);
	static glm::mat4 orthographic_projection(float left, float right, float bottom, float top);
};

#endif // !TRANSFORM_H
