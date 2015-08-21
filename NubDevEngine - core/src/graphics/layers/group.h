#pragma once

#include "..\renderers\renderable2d.h"

namespace engine{
	namespace graphics{

		class Group : public Renderable2D{

		private:
			std::vector<Renderable2D*> m_Renderables;
			maths::mat4 m_TransformationMatrix;

		public:
			Group();
			void submit(Renderer2D *renderer) const override;

		};

	}
}