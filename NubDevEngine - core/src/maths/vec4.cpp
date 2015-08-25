#include "vec4.h"

namespace engine{
	namespace maths{

		vec4::vec4(const float& x, const float& y, const float& z, const float& w)
			: x(x), y(y), z(z), w(w){	}

		vec4& vec4::add(const vec4& other){
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}

		vec4& vec4::subtract(const vec4& other){
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
		}

		vec4& vec4::multiply(const vec4& other){
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;

			return *this;
		}

		vec4& vec4::divide(const vec4& other){
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;

			return *this;
		}

		vec4 operator+(vec4& left, const vec4 right){
			return left.add(right);
		}

		vec4 operator-(vec4& left, const vec4 right){
			return left.subtract(right);
		}

		vec4 operator*(vec4& left, const vec4 right){
			return left.multiply(right);
		}

		vec4 operator/(vec4& left, const vec4 right){
			return left.divide(right);
		}

		vec4& vec4::operator+=(const vec4& right){
			return add(right);
		}

		vec4& vec4::operator-=(const vec4& right){
			return subtract(right);
		}

		vec4& vec4::operator*=(const vec4& right){
			return multiply(right);
		}

		vec4& vec4::operator/=(const vec4& right){
			return divide(right);
		}

		bool vec4::operator==(const vec4& right){
			return (x == right.x && y == right.y && z == right.z && w == right.w);
		}

		bool vec4::operator!=(const vec4& right){
			return !(*this == right);
		}

		std::ostream& operator<<(std::ostream& stream, const vec4& vector){
			return stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		}
	}
}