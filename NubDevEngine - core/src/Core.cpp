//#include <iostream>
//
//#include "window/window.h"
//#include "maths/maths.h"
//
//#include "graphics/renderers/sprite.h"
//#include "utils/timer.h"
//#include "graphics/layers/tilelayer.h"
//#include "graphics/layers/group.h"
//#include "graphics/Texture.h"
//#include "graphics/renderers/label.h"
//#include "graphics/renderers/batchrenderer2d.h"
//
//#include "audio/SoundManager.h";
//
//#define WIDTH	1280
//#define HEIGHT	720
//#define TITLE	"NubDevEngine"
//
//int main(){
//	using namespace engine;
//	using namespace graphics;
//	using namespace maths;
//	using namespace audio;
//
//	Timer timer;
//	float time = timer.elapsed();
//
//	Window window(TITLE, WIDTH, HEIGHT);
//	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//	Texture *texture = new Texture("res/textures/test.png");
//	Texture *texture2 = new Texture("res/textures/crate.png");
//	Texture *texture3 = new Texture("res/textures/dirt.png");
//
//	Shader *s = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
//
//	TileLayer layer(s);
//
//	int i = 0;
//	for (float y = -9.0f; y < 9.0f; y+=1){
//		for (float x = -16.0f; x < 16.0f; x+=1){
//			int r = rand() % 4;
//
//			int color = 0xffff0000 | rand() % 256;
//			if (r == 0)
//				layer.add(new Sprite(x, y, 0.9f, 0.9f, texture));
//			else if (r == 1)
//				layer.add(new Sprite(x, y, 0.9f, 0.9f, texture2));
//			else if (r == 2)
//				layer.add(new Sprite(x, y, 0.9f, 0.9f, texture3));
//			else if (r == 3){
//				layer.add(new Sprite(x, y, 0.9f, 0.9f, color));
//			}
//			i++;
//		}
//	}
//	std::cout << "Sprite Amount : " << i << std::endl;
//
//	Group* g = new Group(maths::mat4::translation(maths::vec3(-15.8f, 7.0f, 0.0f)));
//	Label* fps = new Label("", 0.4f, 0.4f);
//	g->add(new Sprite(0, 0, 5, 1.5f, maths::vec4(0.3f, 0.3f, 0.3f, 0.9f)));
//	g->add(fps);
//	
//	layer.add(g);
//
//	unsigned short frames = 0;
//	while (!window.closed())
//	{
//		window.clear();
//		double x, y;
//		window.getMousePosition(x, y);
//		s->enable();
//		s->setUniform2f("light", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
//
//		layer.render();
//		window.update();
//
//		frames++;
//		if ((timer.elapsed() - time) > 1.0f){
//			time += 1.0f;
//			fps->text = std::to_string(frames) + " fps";
//			printf("%d FPS \n", frames);
//			frames = 0;
//		}
//	}
//
//	return 0;
//}