#pragma once
#include <iostream>


class vec2;
class vec3;


class vec4
{
public:
	/// <summary>
	/// All components are intialized to 0.
	/// </summary>
	vec4();
	/// <summary>
	/// Initializes each component.
	/// </summary>
	/// <param name="_x">X Component</param>
	/// <param name="_y">Y Component</param>
	/// <param name="_z">Z Component</param>
	/// <param name="_w">W Component</param>
	vec4(float _x, float _y, float _z, float _w);
	/// <summary>
	///  X and Y will be initialized by the XY components of the vec2, while Z and W will be initialized to z and w.
	/// </summary>
	/// <param name="xy">The X and Y components.</param>
	/// <param name="_z">The Z component.</param>
	/// <param name="_w">The W component.</param>
	explicit vec4(const vec2& xy, float _z = 0.0f, float _w = 0.0f);
	/// <summary>
	/// X, Y and Z will be initialized by the XYZ components of the vec3, while W will be initialized to w.
	/// </summary>
	/// <param name="xyz">The X, Y, and Z components.</param>
	/// <param name="_w">The W component.</param>
	explicit vec4(const vec3& xyz, float _w = 0.0f);
	/// <summary>
	/// Copy Constructor.
	/// </summary>
	/// <param name="other">The other vector to copy.</param>
	vec4(const vec4& other);


	// ************ Operator Overloads ************
	vec4 operator+(const vec4& rhs) const;
	vec4 operator-(const vec4& rhs) const;
	vec4 operator-() const;
	vec4 operator*(float scalar) const;
	friend vec4 operator*(float scalar, const vec4& rhs);
	vec4 operator*(const vec4& rhs) const;
	vec4 operator/(float scalar) const;
	vec4 operator/(const vec4& rhs) const;
	vec4& operator=(const vec4& other);
	vec4& operator+=(const vec4& rhs);
	vec4& operator-=(const vec4& rhs);
	vec4& operator*=(float scalar);
	vec4& operator*=(const vec4& other);
	vec4& operator/=(float scalar);
	vec4& operator/=(const vec4& other);
	bool operator==(const vec4& rhs) const;
	explicit operator vec2() const;
	explicit operator vec3() const;
	friend std::ostream& operator<<(std::ostream& stream, const vec4& vec);
	float& operator[](size_t row);
	const float& operator[](size_t row) const;


	// ************ Utility Functions ************
	/// <summary>
	/// </summary>
	/// <returns>The length of this vector.</returns>
	float length() const;
	/// <summary>
	/// </summary>
	/// <returns>The squared length of this vector.</returns>
	float sqrLength() const;
	/// <summary>
	/// Normalizes this vector.
	/// </summary>
	void normalize();
	/// <summary>
	/// </summary>
	/// <returns>A normalized copy of this vector.</returns>
	vec4 getNormalized() const;
	/// <summary>
	///  Calculates the dot product of this vector and rhs.
	/// </summary>
	/// <param name="rhs">The other vector to perform the dot product with.</param>
	/// <returns>The dot product between two vectors.</returns>
	float dot(const vec4& rhs) const;
	/// <summary>
	/// </summary>
	/// <returns>The string representation of this vector.</returns>
	std::string toString() const;


	static vec4 zero;


	union
	{
		struct
		{
			float r, g, b, a;
		};
		struct
		{
			float x, y, z, w;
		};
		float data[4];
	};

};