#include "NubDevEngine.h"
#include <iostream>
#include <map>

#include "graphics\renderers\renderer.h"

using namespace engine;
using namespace graphics;
using namespace audio;
using namespace maths;

class Game : public NubDevEngine{

private:
	Window *m_Window2;
	Layer *layer;
	Label *fps;
	Shader *shader;
	Shader *shader2;
	Renderer *renderer;
	entities::Entity *entity;
	entities::Entity *entity2;
	entities::Camera *camera = new entities::Camera(vec3(0.0f, 0.0f, 0.0f));
	std::vector<entities::Entity*> entities;
	float displayIdentities = 0;
	int cd = 0;
	std::map<maths::vec3*, int> map;
	int index = 0;
	std::vector<int> indices;

public:
	Game(){

	}

	~Game(){
		delete layer;
		delete shader;
	}

	void init() override{
		m_Window = createWindow("Test Game", 960, 540);

		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		FontManager::get()->setScale(m_Window->getWidth() / 32.0f, m_Window->getHeight() / 18.0f);
		Font *font = new Font("comic", "comic.ttf");

		Sound *sound = new Sound("swag", "test.wav");

		shader = new Shader("res/shaders/basic1.vert", "res/shaders/basic1.frag");
		shader2 = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");

		//std::vector<vec3> positions;
		//std::vector<unsigned int> indices;
		//read_obj("res/objects/dragon.obj", positions, indices);

		mat4 proj = mat4::prespective(80.0f, 16.0f/9.0f, 0.1f, 100.0f);
		mat4 ortho = mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, 0.0f, 1.0f);

		renderer = new Renderer(proj, shader, camera);
		entities::Mesh *mesh = new entities::Mesh(1, 2);
		//entities::Mesh *mesh2 = new entities::Mesh(positions, indices);
		entity = new entities::Entity(mesh, maths::vec3(0, 0, 0), maths::vec3(0, 0, 0), 0.01f);
		entity2 = new entities::Entity(mesh, maths::vec3(0, -1, -3), maths::vec3(0, 0, 0), 1.0f);

		layer = new Layer(new BatchRenderer2D(), shader2, ortho);

		Texture *texture = new Texture("res/textures/test.png");
		Texture *texture2 = new Texture("res/textures/crate.png");
		Texture *texture3 = new Texture("res/textures/dirt.png");

		int i = 0;
		for (float y = -9.0f; y < 9.0f; y+=1){
			for (float x = -16.0f; x < 16.0f; x+=1){
				int r = rand() % 4;
		
				int color = 0xffff0000 | rand() % 256;
				if (r == 0)
					layer->add(new Sprite(x, y, 0.9f, 0.9f, texture));
				else if (r == 1)
					layer->add(new Sprite(x, y, 0.9f, 0.9f, texture2));
				else if (r == 2)
					layer->add(new Sprite(x, y, 0.9f, 0.9f, texture3));
				else if (r == 3){
					layer->add(new Sprite(x, y, 0.9f, 0.9f, color));
				}
				i++;
			}
		}
		std::cout << "Sprite Amount : " << i << std::endl;

		Group* g = new Group(maths::mat4::translation(maths::vec3(-15.8f, 7.0f, 0.0f)));
		fps = new Label("", 0.4f, 0.4f, 0xffff00ff);
		g->add(new Sprite(0, 0, 1, 1, maths::vec4(1.0f, 0.0f, 1.0f, 1.0f)));
		g->add(new Sprite(0, 0, 5, 1.5f, 0xff555555));
		g->add(fps);
			
		layer->add(g);

		m_Window2 = new Window("Secondary Window", 500, 300, m_Window);
		createCircle();
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

		//if (m_Window->isKeyPressed(GLFW_KEY_W)){
		//	for (int i = 0; i < triangles; i++){
		//		entities[i]->sheer += 0.001;
		//	}
		//}
		//if (m_Window->isKeyPressed(GLFW_KEY_S)){
		//	for (int i = 0; i < triangles; i++){
		//		entities[i]->sheer -= 0.001;
		//	}
		//}

		if (m_Window->isKeyPressed(GLFW_KEY_R)){
			for (int i = 0; i < entities.size(); i++){
				entities[i]->rotate(maths::vec3(0.2f, 0.2f, 0.2f));
			}
		}

		entity->rotate(maths::vec3(0.2f, 0.2f, 0.2f));
		camera->update();
		double x, y;
		m_Window->getMousePosition(x, y);
		shader2->enable();
		shader2->setUniform2f("light", vec2((float)(x * 32.0f / m_Window->getWidth() -16.0f), (float)(9.0f - y * 18.0f / m_Window->getHeight())));
		shader2->disable();
		//layer->render();
		//renderer->submit(entity);
		m_Window->setCurrent();
		//for (int i = 0; i < entities.size(); i++){
		//	renderer->submit(entities[i]);
		//}
		//renderer->flush();
		m_Window2->setCurrent();
		for (int i = 0; i < entities.size(); i++){
			renderer->submit(entities[i]);
		}
		renderer->flush();
		m_Window2->update();
	}

	void tick() override{
		fps->text = std::to_string(getFPS()) + " FPS";
		std::cout << "FPS: " << getFPS() << " | UPS: " << getUPS() << std::endl;
	}

	void update() override{

	}

	void createCircle(){
		subdivide(maths::vec3(0.0, sqrt(0.5f), 0.0), maths::vec3(-0.5, 0.0, -0.5), maths::vec3(-0.5, 0.0, 0.5), 4); // 9 IMPOSSIBRU
		subdivide(maths::vec3(0.0, sqrt(0.5f), 0.0), maths::vec3(-0.5, 0.0, -0.5), maths::vec3(0.5, 0.0, -0.5), 4);
		subdivide(maths::vec3(0.0, sqrt(0.5f), 0.0), maths::vec3(0.5, 0.0, -0.5), maths::vec3(0.5, 0.0, 0.5), 4);
		subdivide(maths::vec3(0.0, sqrt(0.5f), 0.0), maths::vec3(-0.5, 0.0, 0.5), maths::vec3(0.5, 0.0, 0.5), 4);
		subdivide(maths::vec3(0.0, -sqrt(0.5f), 0.0), maths::vec3(-0.5, 0.0, -0.5), maths::vec3(-0.5, 0.0, 0.5), 4);
		subdivide(maths::vec3(0.0, -sqrt(0.5f), 0.0), maths::vec3(-0.5, 0.0, -0.5), maths::vec3(0.5, 0.0, -0.5), 4);
		subdivide(maths::vec3(0.0, -sqrt(0.5f), 0.0), maths::vec3(0.5, 0.0, -0.5), maths::vec3(0.5, 0.0, 0.5), 4);
		subdivide(maths::vec3(0.0, -sqrt(0.5f), 0.0), maths::vec3(-0.5, 0.0, 0.5), maths::vec3(0.5, 0.0, 0.5), 4);
	}

	void subdivide(maths::vec3 &v1, maths::vec3 &v2, maths::vec3 &v3, int tesselation){
		if (tesselation == 0){
			std::map<maths::vec3*, int>::const_iterator got = map.find(&v1);
			if (got == map.end()){
				map.insert(std::pair<maths::vec3*, int>(&v1, index));
				indices.push_back(index++);
			}
			else{
				indices.push_back(got->second);
			}
			got = map.find(&v2);
			if (got == map.end()){
				map.insert(std::pair<maths::vec3*, int>(&v2, index));
				indices.push_back(index++);
			}
			else{
				indices.push_back(got->second);
			}
			got = map.find(&v3);
			if (got == map.end()){
				map.insert(std::pair<maths::vec3*, int>(&v3, index));
				indices.push_back(index++);
			}
			else{
				indices.push_back(got->second);
			}
			entities.push_back(new entities::Entity(new entities::Mesh(v1, v2, v3, 0), maths::vec3(0, 0, -5), maths::vec3(0, 0, 0), 2.0f));
			return;
		}

		float s = 1.0f / v1.getMagnitude();
		v1 *= s;

		s = 1.0f / v2.getMagnitude();
		v2 *= s;

		s = 1.0f / v3.getMagnitude();
		v3 *= s;

		maths::vec3 v12 = maths::vec3((v1.x + v2.x) / 2.0f, (v1.y + v2.y) / 2.0f, (v1.z + v2.z) / 2.0f);
		s = 1.0f / v12.getMagnitude();
		v12 *= s;
		maths::vec3 v13 = maths::vec3((v1.x + v3.x) / 2.0f, (v1.y + v3.y) / 2.0f, (v1.z + v3.z) / 2.0f);
		s = 1.0f / v13.getMagnitude();
		v13 *= s;
		maths::vec3 v23 = maths::vec3((v2.x + v3.x) / 2.0f, (v2.y + v3.y) / 2.0f, (v2.z + v3.z) / 2.0f);
		s = 1.0f / v23.getMagnitude();
		v23 *= s;

		subdivide(v1, v12, v13, tesselation - 1);
		subdivide(v12, v23, v13, tesselation - 1);
		subdivide(v12, v2, v23, tesselation - 1);
		subdivide(v13, v23, v3, tesselation - 1);
	}

};

int main(){
	Game game;
	game.start();
	return 0;
}