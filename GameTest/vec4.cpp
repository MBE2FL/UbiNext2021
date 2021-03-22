#include "stdafx.h"
#include "vec4.h"
#include "vec2.h"
#include "vec3.h"


vec4 vec4::zero = vec4();


vec4::vec4()
    : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
}

vec4::vec4(float _x, float _y, float _z, float _w)
    : x(_x), y(_y), z(_z), w(_w)
{
}

vec4::vec4(const vec2& xy, float _z, float _w)
    : x(xy.x), y(xy.y), z(_z), w(_w)
{
}

vec4::vec4(const vec3& xyz, float _w)
    : x(xyz.x), y(xyz.y), z(xyz.z), w(_w)
{
}

vec4::vec4(const vec4& other)
    : x(other.x), y(other.y), z(other.z), w(other.w)
{
}

vec4 vec4::operator+(const vec4& rhs) const
{
    return vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

vec4 vec4::operator-(const vec4& rhs) const
{
    return vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

vec4 vec4::operator-() const
{
    return vec4(-x, -y, -z, -w);
}

vec4 vec4::operator*(float scalar) const
{
    return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

vec4 operator*(float scalar, const vec4& rhs)
{
    return rhs * scalar;
}

vec4 vec4::operator*(const vec4& rhs) const
{
    return vec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

vec4 vec4::operator/(float scalar) const
{
    return vec4(x / scalar, y / scalar, z / scalar, w / scalar);
}

vec4 vec4::operator/(const vec4& rhs) const
{
    return vec4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
}

vec4& vec4::operator=(const vec4& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;

    return *this;
}

vec4& vec4::operator+=(const vec4& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;

    return *this;
}

vec4& vec4::operator-=(const vec4& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;

    return *this;
}

vec4& vec4::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

vec4& vec4::operator*=(const vec4& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;

    return *this;
}

vec4& vec4::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;

    return *this;
}

vec4& vec4::operator/=(const vec4& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;

    return *this;
}

bool vec4::operator==(const vec4& rhs) const
{
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
}

vec4::operator vec2() const
{
    return vec2(*this);
}

vec4::operator vec3() const
{
    return vec3(*this);
}

float& vec4::operator[](size_t row)
{
    //return reinterpret_cast<float*>(this)[row];
    return data[row];
}

const float& vec4::operator[](size_t row) const
{
    //return reinterpret_cast<const float*>(this)[row];
    return data[row];
}

float vec4::length() const
{
    return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

float vec4::sqrLength() const
{
    return (x * x) + (y * y) + (z * z) + (w * w);
}

std::ostream& operator<<(std::ostream& stream, const vec4& vec)
{
    stream << '(' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ')';

    return stream;
}

void vec4::normalize()
{
    *this /= length();
}

vec4 vec4::getNormalized() const
{
    vec4 result = *this;
    result.normalize();
    return result;
}

float vec4::dot(const vec4& rhs) const
{
    return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
}

std::string vec4::toString() const
{
    return '(' + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ')';
}
