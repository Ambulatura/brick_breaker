#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <iostream>
#include "ball.h"
#include "shader.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_buffer_layout.h"
#include "vertex_array.h"
#include "transform.h"
#include "bricks.h"
#include <memory>

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
void APIENTRY gl_error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
auto frame = Transform::align_origin_to_center(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(void) {
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	/* Initialize the library */
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Brick Breaker Test", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	glDebugMessageCallback(gl_error, NULL);
	glEnable(GL_DEBUG_OUTPUT);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	Bricks bricks;
	bricks.generate(50.0f, 20.0f, 10.0f, 10.0f,
					frame.left, frame.right, frame.bottom, frame.top,
					50.0f, 50.0f, 230.0f, 20.0f);

	const float* bricks_positions = bricks.get_vertex_positions();
	const unsigned int* bricks_indices = bricks.get_vertex_indices();

	VertexArray vao_bricks;
	VertexBuffer vbo_bricks;
	IndexBuffer ebo_bricks;
	VertexBufferLayout bricks_layout;
	bricks_layout.add(2, GL_FLOAT, GL_FALSE);
	
	Ball ball(0.0f, 0.0f, 10.0f);
	ball.create();
	const float* ball_positions = ball.get_vertex_positions();
	const unsigned int* ball_indices = ball.get_vertex_indices();

	VertexArray vao_ball;
	VertexBuffer vbo_ball;
	IndexBuffer ebo_ball;
	VertexBufferLayout layout;
	layout.add(2, GL_FLOAT, GL_FALSE);

	Shader shader;

	std::string vertex_source = shader.parser("shaders/vertex_shader.glsl");
	std::string fragment_source = shader.parser("shaders/fragment_shader.glsl");
	shader.create(vertex_source, fragment_source);

	float g = 0.0f;
	float g_increment = 0.032f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		auto ortho = Transform::orthographic_projection(frame.left, frame.right, frame.bottom, frame.top);
		frame = Transform::align_origin_to_center(SCREEN_WIDTH, SCREEN_HEIGHT);

		shader.bind();
		shader.set_uniform_matrix4f("u_ortho", ortho);
		shader.set_uniform_4f("u_color", 1.0f, g, 0.0f, 1.0f);
		
		vao_ball.bind();
		vbo_ball.bind();
		ebo_ball.bind();
		vbo_ball.buffer_data(ball_positions, ball.get_vertex_size(), GL_DYNAMIC_DRAW);
		ebo_ball.buffer_data((unsigned int*)ball_indices, ball.get_index_size(), GL_DYNAMIC_DRAW);
		vao_ball.add_attribute(vbo_ball, layout);

		ball.move(frame.left, frame.right, frame.bottom, frame.top);
		ball_positions = ball.get_vertex_positions();

		glDrawElements(GL_TRIANGLE_FAN, ball.get_index_count(), GL_UNSIGNED_INT, 0);

		vao_ball.unbind();
		vbo_ball.unbind();
		ebo_ball.unbind();

		vao_bricks.bind();
		vbo_bricks.bind();
		ebo_bricks.bind();
		vbo_bricks.buffer_data(bricks_positions, bricks.get_vertex_size(), GL_STATIC_DRAW);
		ebo_bricks.buffer_data((unsigned int*)bricks_indices, bricks.get_index_size(), GL_STATIC_DRAW);
		vao_bricks.add_attribute(vbo_bricks, bricks_layout);

		glDrawElements(GL_TRIANGLES, bricks.get_index_count(), GL_UNSIGNED_INT, 0);
		
		if (g > 1.0f || g < 0.0f) {
			g_increment = -g_increment;
		}
		g += g_increment;

		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	glViewport(0, 0, width, height);
}

void APIENTRY gl_error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
	std::cout << "An error occurred!" << std::endl;
	//std::cout << "Source: " << source << std::endl;
	//std::cout << "Type: " << type << std::endl;
	std::cout << "Id: " << id << std::endl;
	//std::cout << "Severity: " << severity << std::endl;
	// std::cout << "Length: " << length << std::endl;
	std::cout << message << std::endl;

	exit(-1);
}