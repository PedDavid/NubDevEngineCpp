#include "group.h"

namespace engine{
	namespace graphics{

		Group::Group(const maths::mat4 &transform)
			: m_TransformationMatrix(transform){

		}

		Group::~Group(){
			for (Renderable2D *renderable : m_Renderables){
				delete renderable;
			}
		}

		void Group::add(Renderable2D *renderable){
			m_Renderables.push_back(renderable);
		}

		void Group::submit(Renderer2D* renderer) const{
			renderer->push(m_TransformationMatrix);
			for (Renderable2D* renderable : m_Renderables){
				renderable->submit(renderer);
			}
			renderer->pop();
		}

	}
}