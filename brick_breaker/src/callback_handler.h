#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class CallbackHandler {
public:
	inline static CallbackHandler* callback_handler;

	virtual void set_handler() { callback_handler = this; }

	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
	virtual void error_callback(int error, const char* description) = 0;
	virtual void APIENTRY gl_error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) = 0;

	static void key_callback_dispatcher(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (callback_handler) {
			callback_handler->key_callback(window, key, scancode, action, mods);
		}
	}

	static void error_callback_dispatcher(int error, const char* description) {
		if (callback_handler) {
			callback_handler->error_callback(error, description);
		}
	}

	static void APIENTRY gl_error_dispatcher(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
		if (callback_handler) {
			callback_handler->gl_error(source, type, id, severity, length, message, userParam);
		}
	}

};

#endif // !INPUT_HANDLER_H
