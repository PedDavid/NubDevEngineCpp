#pragma once

#include "../maths/maths.h"
#include "Mesh.h"

namespace engine{
	namespace entities{

		class Entity{

		private:

			Mesh *m_Mesh;

			maths::vec3 m_Position;
			maths::vec3 m_Rotation;
			float m_Scale;

		public:

			Entity(Mesh *mesh, maths::vec3 position, maths::vec3 rotation, float scale)
				: m_Mesh(mesh), m_Position(position), m_Rotation(rotation), m_Scale(scale) {
			}

			void move(maths::vec3 move){
				m_Position += move;
			}

			maths::mat4 &ProjectionMatrix(){

				maths::mat4 m_ProjM = maths::mat4::identity();

				m_ProjM *= maths::mat4::translation(m_Position);

				m_ProjM *= maths::mat4::rotation(m_Rotation.x, maths::vec3(1, 0, 0));
				m_ProjM *= maths::mat4::rotation(m_Rotation.y, maths::vec3(0, 1, 0));
				m_ProjM *= maths::mat4::rotation(m_Rotation.z, maths::vec3(0, 0, 1));

				maths::mat4 scale_matrix = maths::mat4(m_Scale);
				scale_matrix.elements[3 + 3 * 4] = 1.0f;

				m_ProjM *= scale_matrix;
				return m_ProjM;
			}

			void rotate(){
				m_Rotation += maths::vec3(0.01f, 0.01f, 0.00f);
			}

			inline Mesh &getMesh(){
				return *m_Mesh;
			}
		};

	}
}