#include <iostream>

#include "window/window.h"
#include "maths/maths.h"

#include "graphics/renderers/simplerenderer2d.h"
#include "utils/timer.h"

#define WIDTH	1280
#define HEIGHT	720
#define TITLE	"NubDevEngine"

int main(){
	using namespace engine;
	using namespace graphics;
	using namespace maths;

	Timer timer;
	float time = timer.elapsed();

	timer.reset();
	std::deque<std::string> file = read_file_lines1("res/objects/dragon.obj");
	std::cout << timer.elapsed() << " : char until /n " << std::endl;

	system("PAUSE");
	return 0;

	Window window(TITLE, WIDTH, HEIGHT);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	unsigned short frames = 0;

	while (!window.closed())
	{
		window.clear();
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
