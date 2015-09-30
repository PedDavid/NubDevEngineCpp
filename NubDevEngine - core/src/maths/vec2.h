#pragma once

#include <iostream>

namespace engine {
	namespace maths{
		struct vec2{

			float x, y;

			vec2() = default;
			vec2(float x, float y);

			vec2 &add(const vec2 &other);
			vec2 &subtract(const vec2 &other);
			vec2 &multiply(const vec2 &other);
			vec2 &divide(const vec2 &other);
			vec2 &scale(const float &scalar);

			friend vec2 operator+(vec2 left, const vec2 &right);
			friend vec2 operator-(vec2 left, const vec2 &right);
			friend vec2 operator*(vec2 left, const vec2 &right);
			friend vec2 operator/(vec2 left, const vec2 &right);

			vec2 &operator+=(const vec2 &right);
			vec2 &operator-=(const vec2 &right);
			vec2 &operator*=(const vec2 &right);
			vec2 &operator*=(const float &scalar);
			vec2 &operator/=(const vec2 &right);

			bool operator==(const vec2 &right);
			bool operator!=(const vec2 &right);

			float getMagnitude();

			friend std::ostream &operator<<(std::ostream &stream, const vec2 &vector);
		};
	}
}