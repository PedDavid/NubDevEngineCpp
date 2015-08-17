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

	//timer.reset();
	//read_obj("res/objects/dragon.obj");
	//std::cout << timer.elapsed() << " : char until /n " << std::endl;
	Window window(TITLE, WIDTH, HEIGHT);
	//glClearColor(0.9f, 0.9f, 1.0f, 1.0f);

	GLfloat vertices[] = {
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLuint indices[] = {
		0, 1, 2, 2, 3, 0
	};

	VAO vao;
	VBO *vbo = new VBO(vertices, 4 * 3, 3);
	IBO ibo(indices, 6);

	vao.addBuffers(vbo, 0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	//shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	unsigned short frames = 0;

	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light", vec2((float)(x * 16.0f / 1280.0f), (float)(9.0f - y * 9.0f / 720.0f)));

		vao.bind();
		ibo.bind();
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0);
		ibo.unbind();
		vao.unbind();
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
