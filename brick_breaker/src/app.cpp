#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
void APIENTRY gl_error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
float* create_sphere(float cx, float cy, float radius);
std::string parser(const std::string& file_path);

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

int main(void) {
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	/* Initialize the library */
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	std::string vertex_source = parser("shaders/vertex_shader.glsl");
	std::string fragment_source = parser("shaders/fragment_shader.glsl");
	
	const char* vertex = vertex_source.c_str();
	const char* fragment = fragment_source.c_str();

	unsigned int program = glCreateProgram();
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vs, 1, &vertex, 0);
	glCompileShader(vs);
	glShaderSource(fs, 1, &fragment, 0);
	glCompileShader(fs);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	glUseProgram(program);

	float* sphere_positions = create_sphere(0.0f, 0.0f, 20.0f);
	unsigned int vao_sphere;
	unsigned int vbo_sphere;
	glGenVertexArrays(1, &vao_sphere);
	glBindVertexArray(vao_sphere);
	glGenBuffers(1, &vbo_sphere);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_sphere);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 361 * 2, sphere_positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	

	int location = glGetUniformLocation(program, "u_ortho");
	if (location == -1)
		std::cout << "Location error!" << std::endl;
	//glm::mat4 ortographic_projection = { 1.0f };
	glm::vec2 origin(0.0f, 0.0f);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glm::vec2 lower_left_corner(origin.x - SCREEN_WIDTH / 2, origin.y - SCREEN_HEIGHT / 2);
		float left = lower_left_corner.x;
		float bottom = lower_left_corner.y;
		float right = origin.x - lower_left_corner.x;
		float top = origin.y - lower_left_corner.y;
		
		glm::mat4 ortographic_projection(2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left),
										 0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom),
										 0.0f, 0.0f, -1.0f, 0.0f,
										 0.0f, 0.0f, 0.0f, 1.0f);
		ortographic_projection = glm::transpose(ortographic_projection);
		
		glUniformMatrix4fv(location, 1, GL_FALSE, &ortographic_projection[0][0]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 361);

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
	///std::cout << "Severity: " << severity << std::endl;
	// std::cout << "Length: " << length << std::endl;
	std::cout << message << std::endl;

	exit(-1);
}

float* create_sphere(float cx, float cy, float radius) {
	float step = 1.0f;
	float angles = 0.0f;
	float x = cx;
	float y = cy;
	float* points = (float*)_malloca(2 * sizeof(float) * 361);
	size_t index = 0;
	points[index++] = x, points[index++] = y;
	for (size_t _ = 0; _ < 360; _++) {
		x = cx + radius * glm::cos(angles);
		y = cy + radius * glm::sin(angles);
		angles += step;
		points[index++] = x, points[index++] = y;
	}

	//std::cout << points[721] << " " << points[721] << std::endl;
	return points;
}

std::string parser(const std::string& file_path) {
	std::fstream stream(file_path);
	std::string line;
	std::string shader;
	while (std::getline(stream, line))
		shader += line + '\n';
	return shader;
}


