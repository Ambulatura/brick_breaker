#include "transform.h"

Frame Transform::align_origin_to_center(uint32_t screen_width, uint32_t screen_height) {
	Frame frame;
	frame.right = static_cast<float>(screen_width) / 2.0f;
	frame.left = 0.0f - frame.right;
	frame.top = static_cast<float>(screen_height) / 2.0f;
	frame.bottom = 0.0f - frame.top;
	return frame;
}

glm::mat4 Transform::orthographic_projection(float left, float right, float bottom, float top) {
	return transpose(glm::mat4(2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left),
							   0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom),
							   0.0f, 0.0f, -1.0f, 0.0f,
							   0.0f, 0.0f, 0.0f, 1.0f));
}