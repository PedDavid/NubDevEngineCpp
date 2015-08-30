#include "NubDevEngine.h"

using namespace engine;
using namespace graphics;
using namespace audio;
using namespace maths;

class Game : public NubDevEngine{

private:
	Layer *layer;
	Label *fps;
	Shader *shader;

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

		shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");

		mat4 ortho = mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);
		layer = new Layer(new BatchRenderer2D(), shader, ortho);

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
		g->add(new Sprite(0, 0, 5, 1.5f, maths::vec4(0.3f, 0.3f, 0.3f, 0.9f)));
		g->add(fps);
			
		layer->add(g);
	}

	void render() override{
		double x, y;
		m_Window->getMousePosition(x, y);
		shader->enable();
		shader->setUniform2f("light", vec2((float)(x * 32.0f / m_Window->getWidth() -16.0f), (float)(9.0f - y * 18.0f / m_Window->getHeight())));
		shader->disable();
		layer->render();
	}

	void tick() override{
		fps->text = std::to_string(getFPS()) + " FPS";
	}

};

int main(){
	Game game;
	game.start();
	return 0;
}