#pragma once

#include <vector>
#include "../maths/maths.h"

namespace engine{
	namespace entities{

		class Triangle{

		public:

			Triangle(maths::vec3 vector1, maths::vec3 vector2, maths::vec3 vector3, int tesselation){


				int ibo_count = 3 * pow(4.0f, tesselation);
				int complexity = pow(2.0f, tesselation);



				subdivide(vector1, vector2, vector3, tesselation);

			}

			void subdivide(maths::vec3 v1, maths::vec3 v2, maths::vec3 v3, int tesselation){
				if (tesselation == 0){
					std::cout << "v1: " << v1 << " | v2: " << v2 << " | v3: " << v3 << std::endl;
					return;
				}

				maths::vec3 v12 = maths::vec3((v1.x + v2.x) / 2, (v1.y + v2.y) / 2, (v1.z + v2.z) / 2);
				maths::vec3 v13 = maths::vec3((v1.x + v3.x) / 2, (v1.y + v3.y) / 2, (v1.z + v3.z) / 2);
				maths::vec3 v23 = maths::vec3((v2.x + v3.x) / 2, (v2.y + v2.y) / 2, (v2.z + v3.z) / 2);

				subdivide(v1, v12, v13, tesselation-1);
				subdivide(v12, v23, v13, tesselation - 1);
				subdivide(v12, v2, v23, tesselation - 1);
				subdivide(v13, v23, v3, tesselation - 1);
			}

		};

	}
}