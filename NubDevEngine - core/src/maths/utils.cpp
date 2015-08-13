#include "utils.h"

namespace engine{
	namespace maths{

		const float PI = 3.1415927f;

		float toRadians(float degrees){
			return degrees * (PI / 180.0f);
		}
	}
}