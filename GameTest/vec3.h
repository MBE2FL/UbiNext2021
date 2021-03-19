#pragma once
#include <iostream>


class vec2;
class vec4;


class vec3
{
public:
	/// <summary>
	/// All components are intialized to 0.
	/// </summary>
	vec3();
	/// <summary>
	/// Initializes each component.
	/// </summary>
	/// <param name="_x">X Component</param>
	/// <param name="_y">Y Component</param>
	/// <param name="_z">Z Component</param>
	vec3(float _x, float _y, float _z);
	/// <summary>
	/// X and Y will be initialized by the XY components of the vec2, while z will be initialized to 0.
	/// </summary>
	/// <param name="xy">The X and Y components.</param>
	explicit vec3(const vec2& xy);
	/// <summary>
	/// X, Y and Z will be initalized by the XYZ components of the vec4.
	/// </summary>
	/// <param name="xyz">The X, Y, and Z components</param>
	explicit vec3(const vec4& xyz);
	/// <summary>
	/// Copy Constructor.
	/// </summary>
	/// <param name="other">The other vector to copy.</param>
	vec3(const vec3& other);


	// ************ Operator Overloads ************
	vec3 operator+(const vec3& rhs) const;
	vec3 operator-(const vec3& rhs) const;
	vec3 operator-() const;
	vec3 operator*(float scalar) const;
	friend vec3 operator*(float scalar, const vec3& rhs);
	vec3 operator*(const vec3& rhs) const;
	vec3 operator/(float scalar) const;
	vec3 operator/(const vec3& rhs) const;
	vec3& operator=(const vec3& rhs);
	vec3& operator+=(const vec3& rhs);
	vec3& operator-=(const vec3& rhs);
	vec3& operator*=(float scalar);
	vec3& operator*=(const vec3& other);
	vec3& operator/=(float scalar);
	vec3& operator/=(const vec3& other);
	bool operator==(const vec3& rhs) const;
	explicit operator vec2() const;
	explicit operator vec4() const;
	friend std::ostream& operator<<(std::ostream& stream, const vec3& vec);
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
	vec3 getNormalized() const;
	/// <summary>
	/// Calculates the dot product of this vector and rhs.
	/// </summary>
	/// <param name="rhs">The other vector to perform the cross product with.</param>
	/// <returns></returns>
	float dot(const vec3& rhs) const;
	/// <summary>
	/// Calculates the cross product of this vector and rhs.
	/// </summary>
	/// <param name="rhs">The other vector to perform the cross product with.</param>
	/// <returns>The cross product between two vectors.</returns>
	vec3 cross(const vec3& rhs) const;
	/// <summary>
	/// </summary>
	/// <returns>The string representation of this vector.</returns>
	std::string toString() const;


	static vec3 zero;
	static vec3 one;
	static vec3 up;
	static vec3 right;
	static vec3 forward;

	
	union
	{
		struct
		{
			float pitch, yaw, roll;
		};
		struct
		{
			float r, g, b;
		};
		struct
		{
			float x, y, z;
		};
		float data[3];
	};

};