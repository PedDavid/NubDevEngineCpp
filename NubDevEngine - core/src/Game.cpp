#include "NubDevEngine.h"
#include <iostream>

#include "graphics\renderers\renderer.h"

using namespace engine;
using namespace graphics;
using namespace audio;
using namespace maths;

class Game : public NubDevEngine{

private:
	Layer *layer;
	Label *fps;
	Shader *shader;
	Renderer *renderer;
	entities::Entity *entity;
	entities::Entity *entity2;
	entities::Camera *camera = new entities::Camera(vec3(0.0f, 0.0f, 0.0f));

public:
	Game(){
		
	}

	~Game(){
		delete layer;
		delete shader;
	}

	void init() override{
		createWindow("Test Game", 960, 540);
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		FontManager::get()->setScale(m_Window->getWidth() / 32.0f, m_Window->getHeight() / 18.0f);
		Font *font = new Font("comic", "comic.ttf");

		Sound *sound = new Sound("swag", "test.wav");

		shader = new Shader("res/shaders/basic1.vert", "res/shaders/basic1.frag");

		std::vector<vec3> positions;
		std::vector<unsigned int> indices;

		read_obj("res/objects/dragon.obj", positions, indices);

		mat4 proj = mat4::prespective(80.0f, 16.0f/9.0f, 0.1f, 100.0f);
		mat4 ortho = mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);
		mat4 simple = mat4::identity();

		renderer = new Renderer(proj, shader, camera);
		entities::Mesh *mesh = new entities::Mesh;
		entity = new entities::Entity(new entities::Mesh(positions, indices), maths::vec3(0, 0, 0), maths::vec3(0, 0, 0), 1.0f);
		entity2 = new entities::Entity(mesh, maths::vec3(0, 0, -5), maths::vec3(0, 0, 0), 1.0f);

		//layer = new Layer(new BatchRenderer2D(), shader, ortho);

		//Texture *texture = new Texture("res/textures/test.png");
		//Texture *texture2 = new Texture("res/textures/crate.png");
		//Texture *texture3 = new Texture("res/textures/dirt.png");

		//int i = 0;
		//for (float y = -9.0f; y < 9.0f; y+=1){
		//	for (float x = -16.0f; x < 16.0f; x+=1){
		//		int r = rand() % 4;
		//
		//		int color = 0xffff0000 | rand() % 256;
		//		if (r == 0)
		//			layer->add(new Sprite(x, y, 0.9f, 0.9f, texture));
		//		else if (r == 1)
		//			layer->add(new Sprite(x, y, 0.9f, 0.9f, texture2));
		//		else if (r == 2)
		//			layer->add(new Sprite(x, y, 0.9f, 0.9f, texture3));
		//		else if (r == 3){
		//			layer->add(new Sprite(x, y, 0.9f, 0.9f, color));
		//		}
		//		i++;
		//	}
		//}
		//std::cout << "Sprite Amount : " << i << std::endl;

		//Group* g = new Group(maths::mat4::translation(maths::vec3(-15.8f, 7.0f, 0.0f)));
		//fps = new Label("", 0.4f, 0.4f, 0xffff00ff);
		//g->add(new Sprite(0, 0, 5, 1.5f, maths::vec4(0.3f, 0.3f, 0.3f, 0.9f)));
		//g->add(fps);
		//	
		//layer->add(g);
	}

	void render() override{
		if (m_Window->isKeyPressed(GLFW_KEY_LEFT)){
			entity->move(maths::vec3(-0.001, 0.0, 0.0));
			entity2->move(maths::vec3(-0.001, 0.0, 0.0));
		}
		if (m_Window->isKeyPressed(GLFW_KEY_RIGHT)){
			entity->move(maths::vec3(+0.001, 0.0, 0.0));
			entity2->move(maths::vec3(+0.001, 0.0, 0.0));
		}
		if (m_Window->isKeyPressed(GLFW_KEY_UP)){
			entity->move(maths::vec3(+0.000, 0.0, +0.001));
			entity2->move(maths::vec3(+0.000, 0.0, +0.001));
		}
		if (m_Window->isKeyPressed(GLFW_KEY_DOWN)){
			entity->move(maths::vec3(+0.000, 0.0, -0.001));
			entity2->move(maths::vec3(+0.000, 0.0, -0.001));
		}
		entity->rotate();
		camera->update();
		double x, y;
		m_Window->getMousePosition(x, y);
		//shader->enable();
		//shader->setUniform2f("light", vec2((float)(x * 32.0f / m_Window->getWidth() -16.0f), (float)(9.0f - y * 18.0f / m_Window->getHeight())));
		//shader->disable();
		//layer->render();
		//renderer->submit(entity);
		renderer->submit(entity2);
		renderer->flush();
	}

	void tick() override{
		//fps->text = std::to_string(getFPS()) + " FPS";
		//std::cout << "FPS: " << getFPS() << " | UPS: " << getUPS() << std::endl;
	}

};

int main(){
	Game game;
	game.start();
	return 0;
}