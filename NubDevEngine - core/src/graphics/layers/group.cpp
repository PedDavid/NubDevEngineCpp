#include "group.h"

namespace engine{
	namespace graphics{

		void Group::submit(Renderer2D* renderer) const{
			renderer->push(m_TransformationMatrix);
			for (Renderable2D* renderable : m_Renderables){
				renderable->submit(renderer);
			}
			renderer->pop();
		}

	}
}