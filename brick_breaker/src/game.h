#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "bricks.h"
#include "shader.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_buffer_layout.h"
#include "vertex_array.h"
#include <vector>
#include "object.h"
#include "renderer.h"

class Game {
private:
	uint32_t screen_width;
	uint32_t screen_height;
	Renderer renderer;
	Shader shader;
	std::vector<Object*> objects;
	
public:
	Game(uint32_t width, uint32_t height);
	~Game();

	void init();
	void add_object(Object* object);
	void update();
	void draw();
};

#endif // !GAME_H
