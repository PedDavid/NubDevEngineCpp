#include <iostream>

#include <FreeImage.h>
#include "window/window.h"
#include "maths/maths.h"

#include "graphics/renderers/batchrenderer2d.h"
#include "graphics/renderers/simplerenderer2d.h"
#include "graphics/renderers/sprite.h"
#include "utils/timer.h"
#include "graphics/layers/tilelayer.h"
#include "graphics/layers/group.h"
#include "graphics/Texture.h"

#include "audio/SoundManager.h";

#define WIDTH	1280
#define HEIGHT	720
#define TITLE	"NubDevEngine"

int main(){
	using namespace engine;
	using namespace graphics;
	using namespace maths;
	using namespace audio;

	Timer timer;
	float time = timer.elapsed();

	//timer.reset();
	//read_obj("res/objects/dragon.obj");
	//std::cout << timer.elapsed() << " : char until /n " << std::endl;

	Window window(TITLE, WIDTH, HEIGHT);
	//glClearColor(0.9f, 0.9f, 1.0f, 1.0f);

	//glActiveTexture(GL_TEXTURE0);
	Texture *texture = new Texture("res/textures/test.png");
	Texture *texture2 = new Texture("res/textures/crate.png");
	Texture *texture3 = new Texture("res/textures/dirt.png");
	//texture.bind();

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader *s = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	Shader shader = *s;
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	

	GLint texIDs[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.setUniform1iv("textures", texIDs, 10);

	TileLayer layer(s);

	int i = 0;
	for (float y = -9.0f; y < 9.0f; y++){
		for (float x = -16.0f; x < 16.0f; x++){
			int r = i % 3;//rand() % 3;
			if (r == 0)
				layer.add(new Sprite(x, y, 0.9f, 0.9f, texture));
			else if (r == 1)
				layer.add(new Sprite(x, y, 0.9f, 0.9f, texture2));
			else if (r == 2)
				layer.add(new Sprite(x, y, 0.9f, 0.9f, texture3));
			i++;
		}
	}
	std::cout << "Sprite Amount : " << i << std::endl;

	SoundManager::init();

	float gain = 0.5f;
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
		SoundManager::update();

		frames++;
		if ((timer.elapsed() - time) > 1.0f){
			time += 1.0f;
			printf("%d FPS \n", frames);
			frames = 0;
		}
	}

	return 0;
}
