#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "callback_handler.h"
#include <vector>
#include "object.h"

class Game : public CallbackHandler {
public:
	Game(uint32_t width, uint32_t height);
	~Game();

	void run();

	std::vector<Object*> objects;
private:
	uint32_t screen_width;
	uint32_t screen_height;
	GLFWwindow* window;


private:
	void error_callback(int error, const char* description) override;
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	//void frame_buffer_size_callback(GLFWwindow* window, int width, int height) override;
	void APIENTRY gl_error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) override;
};

#endif // !GAME_H
