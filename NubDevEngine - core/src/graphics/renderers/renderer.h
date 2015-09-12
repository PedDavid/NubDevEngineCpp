#pragma once

#include <vector>

#include "../../maths/maths.h"
#include "../../entities/Entity.h"
#include "../shader.h"
#include "../../entities/Camera.h"

namespace engine{
	namespace graphics{

		class Renderer{

		private:
			maths::mat4 m_ProjectionMatrix;
			std::vector<entities::Entity*> entities;
			Shader *m_Shader;
			entities::Camera *m_Camera;

		public:
			Renderer(maths::mat4 projectionMatrix, Shader *shader, entities::Camera *camera) 
				: m_ProjectionMatrix(projectionMatrix), m_Shader(shader), m_Camera(camera) {
				m_Shader->enable();
				m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
				m_Shader->disable();
			}

			void submit(entities::Entity *entity){
				entities.push_back(entity);
			}

			void flush(){
				m_Shader->enable();
				maths::mat4 view_matrix = m_Camera->getViewMatrix();
				m_Shader->setUniformMat4("vw_matrix", view_matrix);
				for (entities::Entity *entity : entities){
					maths::mat4 model_matrix = entity->ProjectionMatrix();
					m_Shader->setUniformMat4("ml_matrix", model_matrix);
					int vaoId = entity->getMesh().getVaoID();
					GlCheck(glBindVertexArray(vaoId));
					entity->getMesh().getIBO().bind();
					int count = entity->getMesh().getCount();
					GlCheck(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0));
					entity->getMesh().getIBO().unbind();
					GlCheck(glBindVertexArray(0));
				}
				m_Shader->disable();
				entities.clear();
			}

		};

	}
}