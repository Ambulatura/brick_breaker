#include "game.h"
#include "transform.h"
#include "ball.h"
#include "bricks.h"
#include "ball.h"
#include "bar.h"
#include "collision.h"
#include "shader.h"
#include "renderer.h"

Game::Game(uint32_t width, uint32_t height) : screen_width(width), screen_height(height) {

	glfwSetErrorCallback(error_callback_dispatcher);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(screen_width, screen_height, "Brick Breaker Test", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	set_handler();

	glfwSetKeyCallback(window, key_callback_dispatcher);
	//glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	glDebugMessageCallback(gl_error_dispatcher, NULL);
	glEnable(GL_DEBUG_OUTPUT);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}

Game::~Game() {}

void Game::run() {

	Ball ball(static_cast<float>(screen_width) / 2.0f, 70.0f, 12.5f,
		0.0f, static_cast<float>(screen_width), 0.0f, static_cast<float>(screen_height));
	Bricks bricks(70.0f, 35.0f, 1.0f, 0.0f,
		0.0f, static_cast<float>(screen_width), 0.0f, static_cast<float>(screen_height),
		70.0f, 70.0f, 280.0f, 50.0f);
	Bar bar(170.0f, 25.0f, 20.0f,
		0.0f, static_cast<float>(screen_width), 0.0f, static_cast<float>(screen_height));
	
	objects.push_back(&ball);
	objects.push_back(&bar);

	Shader shader;
	std::string vertex_source = shader.parser("shaders/vertex_shader.glsl");
	std::string fragment_source = shader.parser("shaders/fragment_shader.glsl");
	shader.create(vertex_source, fragment_source);

	Renderer renderer;

	auto ortho = Transform::orthographic_projection(0.0f, static_cast<float>(screen_width), 0.0f, static_cast<float>(screen_height));

	while (!glfwWindowShouldClose(window)) {
		
		if (!ball.stuck) {
			Collision::collision(ball, bricks, bar);
			ball.move();
		}

		shader.bind();
		shader.set_uniform_matrix4f("u_ortho", ortho);
		//shader.set_uniform_4f("u_color", 0.862f, 0.196f, 0.184f, 1.0f);

		renderer.clear_color(0.992f, 0.964f, 0.890f, 1.0f);
		renderer.clear();
		renderer.render(&ball, shader);

		shader.bind();
		//shader.set_uniform_4f("u_color", 1.0f, 0.4f, 0.6f, 1.0f);
		renderer.render(&bricks, shader);

		shader.bind();
		//shader.set_uniform_4f("u_color", 0.796f, 0.294f, 0.086f, 1.0f);
		renderer.render(&bar, shader);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}


void Game::error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		Ball* ball = static_cast<Ball*>(objects[0]);
		Bar* bar = static_cast<Bar*>(objects[1]);
		if (ball->stuck) {
			ball->change_position(-bar->velocity_x, 0.0f);
			bar->move_left();
		}
		else {
			bar->move_left();
		}
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		Ball* ball = static_cast<Ball*>(objects[0]);
		Bar* bar = static_cast<Bar*>(objects[1]);
		if (ball->stuck) {
			bar->move_right();
			ball->change_position(bar->velocity_x, 0.0f);
		}
		else {
			bar->move_right();
		}
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		Ball* ball = static_cast<Ball*>(objects[0]);
		if (ball->stuck)
			ball->stuck = false;
	}
}

/*
void Game::frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
	//screen_width = width;
	//screen_height = height;
	glViewport(0, 0, width, height);
}*/

void APIENTRY Game::gl_error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
	std::cout << "An error occurred!" << std::endl;
	//std::cout << "Source: " << source << std::endl;
	//std::cout << "Type: " << type << std::endl;
	std::cout << "Id: " << id << std::endl;
	//std::cout << "Severity: " << severity << std::endl;
	// std::cout << "Length: " << length << std::endl;
	std::cout << message << std::endl;
	std::cin.get();
	exit(-1);
}