#include "vec2.h"

namespace engine{
	namespace maths{

		vec2::vec2(float x, float y) 
			: x(x) , y(y){	}

		vec2& vec2::add(const vec2& other){
			x += other.x;
			y += other.y;

			return *this;
		}

		vec2& vec2::subtract(const vec2& other){
			x -= other.x;
			y -= other.y;

			return *this;
		}

		vec2& vec2::multiply(const vec2& other){
			x *= other.x;
			y *= other.y;

			return *this;
		}

		vec2& vec2::divide(const vec2& other){
			x /= other.x;
			y /= other.y;

			return *this;
		}

		vec2& vec2::scale(const float &scalar){
			x *= scalar;
			y *= scalar;

			return *this;
		}

		vec2 operator+(vec2& left, const vec2 right){
			return left.add(right);
		}

		vec2 operator-(vec2& left, const vec2 right){
			return left.subtract(right);
		}

		vec2 operator*(vec2& left, const vec2 right){
			return left.multiply(right);
		}

		vec2 operator/(vec2& left, const vec2 right){
			return left.divide(right);
		}

		vec2& vec2::operator+=(const vec2& right){
			return add(right);
		}

		vec2& vec2::operator-=(const vec2& right){
			return subtract(right);
		}

		vec2& vec2::operator*=(const vec2& right){
			return multiply(right);
		}

		vec2& vec2::operator*=(const float &scalar){
			return scale(scalar);
		}

		vec2& vec2::operator/=(const vec2& right){
			return divide(right);
		}

		bool vec2::operator==(const vec2& right){
			return (x == right.x && y == right.y);
		}

		bool vec2::operator!=(const vec2& right){
			return !(*this == right);
		}

		float vec2::getMagnitude(){
			return sqrt(x * x + y * y);
		}

		std::ostream& operator<<(std::ostream& stream, const vec2& vector){
			return stream << "(" << vector.x << ", " << vector.y << ")";
		}
	}
}