#include "stdafx.h"
#include "vec3.h"
#include "vec2.h"
#include "vec4.h"
#include <math.h>


vec3 vec3::zero = vec3();
vec3 vec3::one = vec3(1.0f, 1.0f, 1.0f);
vec3 vec3::up = vec3(0.0f, 1.0f, 0.0f);
vec3 vec3::right = vec3(1.0f, 0.0f, 0.0f);
vec3 vec3::forward = vec3(0.0f, 0.0f, 1.0f);


vec3::vec3()
	: x(0.0f), y(0.0f), z(0.0f)
{
}

vec3::vec3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
}

vec3::vec3(const vec2& xy)
	: x(xy.x), y(xy.y), z(0.0f)
{
}

vec3::vec3(const vec4& xyz)
	: x(xyz.x), y(xyz.y), z(xyz.z)
{
}

vec3::vec3(const vec3& other)
	: x(other.x), y(other.y), z(other.z)
{
}

vec3 vec3::operator+(const vec3& rhs) const
{
	vec3 result = vec3(*this);
	result.x += rhs.x;
	result.y += rhs.y;
	result.z += rhs.z;

	return result;
}

vec3 vec3::operator-(const vec3& rhs) const
{
	vec3 result = vec3(*this);
	result.x -= rhs.x;
	result.y -= rhs.y;
	result.z -= rhs.z;

	return result;
}

vec3 vec3::operator-() const
{
	return vec3(-x, -y, -z);
}

vec3 vec3::operator*(float scalar) const
{
	return vec3(x * scalar, y * scalar, z * scalar);
}

vec3 operator*(float scalar, const vec3& rhs)
{
	return rhs * scalar;
}

vec3 vec3::operator*(const vec3& rhs) const
{
	return vec3(x * rhs.x, y * rhs.y, z * rhs.z);
}

vec3 vec3::operator/(float scalar) const
{
	return vec3(x / scalar, y / scalar, z / scalar);
}

vec3 vec3::operator/(const vec3& rhs) const
{
	return vec3(x / rhs.x, y / rhs.y, z / rhs.z);
}

vec3& vec3::operator=(const vec3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

vec3& vec3::operator+=(const vec3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

vec3& vec3::operator-=(const vec3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

vec3& vec3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

vec3& vec3::operator*=(const vec3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

vec3& vec3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

vec3& vec3::operator/=(const vec3& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;

	return *this;
}

bool vec3::operator==(const vec3& rhs) const
{
	return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

vec3::operator vec2() const
{
	return vec2(*this);
}

vec3::operator vec4() const
{
	return vec4(*this);
}

float& vec3::operator[](size_t row)
{
	return data[row];
}

const float& vec3::operator[](size_t row) const
{
	return data[row];
}

float vec3::length() const
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

float vec3::sqrLength() const
{
	return (x * x) + (y * y) + (z * z);
}

std::ostream& operator<<(std::ostream& stream, const vec3& vec)
{
	stream << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';

	return stream;
}

void vec3::normalize()
{
	*this /= length();
}

vec3 vec3::getNormalized() const
{
	vec3 result = *this;
	result.normalize();
	return result;
}

float vec3::dot(const vec3& rhs) const
{
	return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}

vec3 vec3::cross(const vec3& rhs) const
{
	vec3 result;
	result.x = (y * rhs.z) - (z * rhs.y);
	result.y = (z * rhs.x) - (x * rhs.z);
	result.z = (x * rhs.y) - (y * rhs.x);

	return result;
}

std::string vec3::toString() const
{
	return '(' + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ')';
}
