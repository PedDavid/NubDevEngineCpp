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

#include "../ext/gorilla-audio/ga.h"
#include "../ext/gorilla-audio/gau.h"

#define WIDTH	1280
#define HEIGHT	720
#define TITLE	"NubDevEngine"

#define DEBUG_TYPE 2

#if DEBUG_TYPE == 0
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

	//mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader *s = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
	Shader shader = *s;
	shader.enable();
	//shader.setUniformMat4("pr_matrix", ortho);

	TileLayer layer(s);

	int i = 0;
	for (float y = -9.0f; y < 9.0f; y+= 0.1f){
		for (float x = -16.0f; x < 16.0f; x+=0.1f){
			layer.add(new Sprite(x, y, 0.09f, 0.09f, vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			i++;
		}
	}
	std::cout << "Sprite Amount : " << i << std::endl;

	//VAO *vao = new VAO();
	//IBO ibo = read_obj("res/objects/dragon.obj", vao);

	unsigned short frames = 0;
	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.enable();
		shader.setUniform2f("light", vec2((float)(x * 32.0f / 1280.0f - 16.0f), (float)(9.0f - y * 18.0f / 720.0f)));

		//layer.render();

		//vao->bind();
		//ibo.bind();
		//glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0);
		//ibo.unbind();
		//vao->unbind();

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
#elif DEBUG_TYPE == 1
int main(){

	const char *filename = "res/textures/test.png";
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	std::cout << width << " | " << height << std::endl;
	for (int i = 0; i < width * height * 3;){
		std::cout << (int)bits[i++] << " | " << (int)bits[i++] << " | " << (int)bits[i++] << std::endl;
	}
	std::cin.get();

	return 0;
}
#elif DEBUG_TYPE == 2
static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
{
	gc_int32* flag = (gc_int32*)(in_context);
	*flag = 1;
	ga_handle_destroy(in_handle);
}

int main(){

	gau_Manager* mgr;
	ga_Mixer* mixer;
	ga_Sound* sound;
	ga_Handle* handle;
	gau_SampleSourceLoop* loopSrc = 0;
	gau_SampleSourceLoop** pLoopSrc = &loopSrc;
	gc_int32 loop = 0;
	gc_int32 quit = 0;

	/* Initialize library + manager */
	gc_initialize(0);
	mgr = gau_manager_create();
	mixer = gau_manager_mixer(mgr);

	/* Create and play shared sound */
	if (!loop)
		pLoopSrc = 0;
	sound = gau_load_sound_file("test.wav", "wav");
	handle = gau_create_handle_sound(mixer, sound, &setFlagAndDestroyOnFinish, &quit, pLoopSrc);
	ga_handle_play(handle);

	/* Bounded mix/queue/dispatch loop */
	while (!quit)
	{
		gau_manager_update(mgr);
		printf("%d / %d\n", ga_handle_tell(handle, GA_TELL_PARAM_CURRENT), ga_handle_tell(handle, GA_TELL_PARAM_TOTAL));
		gc_thread_sleep(1);
	}

	/* Clean up sound */
	ga_sound_release(sound);

	/* Clean up library + manager */
	gau_manager_destroy(mgr);
	gc_shutdown();

	std::cin.get();

	return 0;
}
#endif
