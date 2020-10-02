#include "game.h"
#include "transform.h"

Game::Game(uint32_t width, uint32_t height) : screen_width(width), screen_height(height) {}

Game::~Game() {}

void Game::init() {
	std::string vertex_source = shader.parser("shaders/vertex_shader.glsl");
	std::string fragment_source = shader.parser("shaders/fragment_shader.glsl");
	shader.create(vertex_source, fragment_source);

	Object* ball = new Ball(static_cast<float>(screen_width) / 2.0f, 50.0f, 10.0f, 0.0f, static_cast<float>(screen_width), 0.0f, static_cast<float>(screen_height));
	Object* bricks = new Bricks(60.0f, 25.0f, 3.0f, 3.0f,
		                        0.0f, static_cast<float>(screen_width), 0.0f, static_cast<float>(screen_height),
		                        50.0f, 50.0f, 280.0f, 20.0f);

	add_object(ball);
	add_object(bricks);
}

void Game::add_object(Object* object) {
	objects.push_back(object);
}

void Game::update() {
	Ball* ball = static_cast<Ball*>(objects[0]);
	ball->move();
}

void Game::draw() {
	auto ortho = Transform::orthographic_projection(0.0f, static_cast<float>(screen_width), 0.0f, static_cast<float>(screen_height));
	shader.bind();
	shader.set_uniform_matrix4f("u_ortho", ortho);
	shader.set_uniform_4f("u_color", 1.0f, 0.5f, 0.7f, 1.0f);

	renderer.clear_color(0.5f, 0.7f, 1.0f, 1.0f);
	renderer.clear();
	renderer.render(objects[0], shader);
	renderer.render(objects[1], shader);
}