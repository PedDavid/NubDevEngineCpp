#pragma once

#include "../maths/maths.h"

namespace engine{
	namespace entities{

		class Camera{

		private:
			maths::mat4 m_ViewMatrix = maths::mat4::identity();
			maths::vec3 m_Pos = maths::vec3(0, 0, 0);
			float m_Yaw = 0.0f;
			float m_Pitch = 0.0f;
			float m_Roll = 0.0f;

		public:
			Camera(maths::vec3 position) : m_Pos(position) {

			}

			void update(){
				maths::mat4 newMatrix = maths::mat4::identity();
				newMatrix *= maths::mat4::rotation(m_Pitch, maths::vec3(1, 0, 0));
				newMatrix *= maths::mat4::rotation(m_Yaw, maths::vec3(0, 1, 0));
				newMatrix *= maths::mat4::translation(maths::vec3(-m_Pos.x, -m_Pos.y, -m_Pos.z));
				m_ViewMatrix = newMatrix;
			}

			void move(maths::vec3 pos){
				m_Pos += pos;
			}

			void setPosition(maths::vec3 pos){
				m_Pos = pos;
			}

			void setPitch(float pitch){
				m_Pitch = pitch;
			}

			void setYaw(float yaw){
				m_Yaw = yaw;
			}

			void setRoll(float roll){
				m_Roll = roll;
			}

			inline float getPitch()	{ return m_Pitch; }
			inline float getYaw()	{ return m_Yaw; }
			inline float getRoll()	{ return m_Roll; }

			inline maths::mat4 getViewMatrix()	{ return m_ViewMatrix; }
		};

	}
}