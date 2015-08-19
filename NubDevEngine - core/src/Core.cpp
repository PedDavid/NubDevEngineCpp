#include <iostream>

#include "window/window.h"
#include "maths/maths.h"

#include "graphics/renderers/batchrenderer2d.h"
#include "graphics/renderers/simplerenderer2d.h"
#include "graphics/renderers/sprite.h"
#include "utils/timer.h"
#include "graphics\layers\tilelayer.h"

#define WIDTH	1280
#define HEIGHT	720
#define TITLE	"NubDevEngine"

#define BATCH_RENDERER 1

int main(){
	using namespace engine;
	using namespace graphics;
	using namespace maths;

	Timer timer;
	float time = timer.elapsed();

	//timer.reset();
	//read_obj("res/objects/dragon.obj");
	//std::cout << timer.elapsed() << " : char until /n " << std::endl;

	Window window(TITLE, WIDTH, HEIGHT);
	//glClearColor(0.9f, 0.9f, 1.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader *s = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	Shader shader = *s;
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	//shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

	TileLayer layer(s);

	int i = 0;
	for (float y = -9.0f; y < 9.0f; y+= 0.1f){
		for (float x = -16.0f; x < 16.0f; x+=0.1f){
			layer.add(new Sprite(x, y, 0.04f, 0.04f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			i++;
		}
	}
	std::cout << "Sprite Amount : " << i << std::endl;


	unsigned short frames = 0;
	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.enable();
		shader.setUniform2f("light", vec2((float)(x * 32.0f / 1280.0f - 16.0f), (float)(9.0f - y * 18.0f / 720.0f)));

		layer.render();

		window.update();

		frames++;
		if ((timer.elapsed() - time) > 1.0f){
			time += 1.0f;
			printf("%d FPS \n", frames);
			frames = 0;
		}
	}

	return 0;
}
