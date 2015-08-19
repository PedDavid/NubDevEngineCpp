#pragma once

#include "../renderers/batchrenderer2d.h"

namespace engine{
	namespace graphics{

		class Layer{

		protected:
			Renderer2D *m_Renderer;
			std::vector<Renderable2D*> m_Renderables;
			Shader *m_Shader;
			maths::mat4 m_ProjectionMatrix;

			Layer(Renderer2D *renderer, Shader *shader, maths::mat4 projectionMatrix);

		public:
			virtual ~Layer();
			virtual void add(Renderable2D *renderable);
			virtual void render();
		};

	}
}