#include "stdafx.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include <math.h>


vec2 vec2::zero = vec2();
vec2 vec2::one = vec2(1.0f, 1.0f);
vec2 vec2::up = vec2(0.0f, 1.0f);
vec2 vec2::right = vec2(1.0f, 0.0f);


vec2::vec2()
	: x(0.0f), y(0.0f)
{
}

vec2::vec2(float x, float y)
	: x(x), y(y)
{
}

vec2::vec2(const vec3& xy)
	: x(xy.x), y(xy.y)
{
}

vec2::vec2(const vec4& xy)
	: x(xy.x), y(xy.y)
{
}

vec2::vec2(const vec2& other)
	: x(other.x), y(other.y)
{
}

vec2 vec2::operator+(const vec2& rhs) const
{
	return vec2(x + rhs.x, y + rhs.y);
}

vec2 vec2::operator-(const vec2& rhs) const
{
	return vec2(x - rhs.x, y - rhs.y);
}

vec2 vec2::operator-() const
{
	return vec2(-x, -y);
}

vec2 vec2::operator*(float scalar) const
{
	return vec2(x * scalar, y * scalar);
}

vec2 operator*(float scalar, const vec2& rhs)
{
	return rhs * scalar;
}

vec2 vec2::operator*(const vec2& rhs) const
{
	return vec2(x * rhs.x, y * rhs.y);
}

vec2 vec2::operator/(float scalar) const
{
	return vec2(x / scalar, y / scalar);
}

vec2 vec2::operator/(const vec2& rhs) const
{
	return vec2(x / rhs.x, y / rhs.y);
}

vec2& vec2::operator=(const vec2& other)
{
	x = other.x;
	y = other.y;

	return *this;
}

vec2& vec2::operator+=(const vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

vec2& vec2::operator-=(const vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

vec2& vec2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

vec2& vec2::operator*=(const vec2& other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

vec2& vec2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

vec2& vec2::operator/=(const vec2& other)
{
	x /= other.x;
	y /= other.y;

	return *this;
}

bool vec2::operator==(const vec2& rhs) const
{
	return (x == rhs.x) && (y == rhs.y);
}

vec2::operator vec3() const
{
	return vec3(*this);
}

vec2::operator vec4() const
{
	return vec4(*this);
}

float& vec2::operator[](size_t row)
{
	return data[row];
}

const float& vec2::operator[](size_t row) const
{
	return data[row];
}

float vec2::length() const
{
	return sqrtf((x * x) + (y * y));
}

float vec2::sqrLength() const
{
	return (x * x) + (y * y);
}

std::ostream& operator<<(std::ostream& stream, const vec2& vec)
{
	stream << '(' << vec.x << ", " << vec.y << ')';

	return stream;
}

void vec2::normalize()
{
	*this / length();
}

vec2 vec2::getNormalized() const
{
	vec2 result = *this;
	result.normalize();
	return result;
}

float vec2::dot(const vec2& rhs) const
{
	return (x * rhs.x) + (y * rhs.y);
}

std::string vec2::toString() const
{
	return std::string();
}
