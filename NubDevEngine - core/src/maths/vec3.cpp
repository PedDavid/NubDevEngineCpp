#include "vec3.h"

namespace engine{
	namespace maths{

		vec3::vec3(const float& x, const float& y, const float& z)
			: x(x), y(y), z(z){	}

		vec3& vec3::add(const vec3& other){
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		vec3& vec3::subtract(const vec3& other){
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}

		vec3& vec3::multiply(const vec3& other){
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		vec3& vec3::divide(const vec3& other){
			x /= other.x;
			y /= other.y;
			z /= other.z;

			return *this;
		}

		vec3 operator+(vec3& left, const vec3 right){
			return left.add(right);
		}

		vec3 operator-(vec3& left, const vec3 right){
			return left.subtract(right);
		}

		vec3 operator*(vec3& left, const vec3 right){
			return left.multiply(right);
		}

		vec3 operator/(vec3& left, const vec3 right){
			return left.divide(right);
		}

		vec3& vec3::operator+=(const vec3& right){
			return add(right);
		}

		vec3& vec3::operator-=(const vec3& right){
			return subtract(right);
		}

		vec3& vec3::operator*=(const vec3& right){
			return multiply(right);
		}

		vec3& vec3::operator/=(const vec3& right){
			return divide(right);
		}

		bool vec3::operator==(const vec3& right){
			return (x == right.x && y == right.y && z == right.z);
		}

		bool vec3::operator!=(const vec3& right){
			return !(*this == right);
		}

		std::ostream& operator<<(std::ostream& stream, const vec3& vector){
			return stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		}
	}
}