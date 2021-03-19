#pragma once


class vec3;
class vec4;


class vec2
{
public:
	/// <summary>
	/// All components are intialized to 0.
	/// </summary>
	vec2();
	/// <summary>
	/// Initializes each component.
	/// </summary>
	/// <param name="_x">X Component</param>
	/// <param name="_y">Y Component</param>
	vec2(float _x, float _y);
	/// <summary>
	/// X and Y will be initialized by the XY components of the vec3.
	/// </summary>
	/// <param name="xy">The X and Y components.</param>
	explicit vec2(const vec3& xy);
	/// <summary>
	/// X and Y will be initialized by the XY components of the vec4.
	/// </summary>
	/// <param name="xy">The X and Y components.</param>
	explicit vec2(const vec4& xy);
	/// <summary>
	/// Copy Constructor.
	/// </summary>
	/// <param name="other"></param>
	vec2(const vec2& other);


	// ************ Operator Overloads ************
	vec2 operator+(const vec2& rhs) const;
	vec2 operator-(const vec2& rhs) const;
	vec2 operator-() const;
	vec2 operator*(float scalar) const;
	friend vec2 operator*(float scalar, const vec2& rhs);
	vec2 operator*(const vec2& rhs) const;
	vec2 operator/(float scalar) const;
	vec2 operator/(const vec2& rhs) const;
	vec2& operator=(const vec2& other);
	vec2& operator+=(const vec2& rhs);
	vec2& operator-=(const vec2& rhs);
	vec2& operator*=(float scalar);
	vec2& operator*=(const vec2& other);
	vec2& operator/=(float scalar);
	vec2& operator/=(const vec2& other);
	bool operator==(const vec2& rhs) const;
	explicit operator vec3() const;
	explicit operator vec4() const;
	friend std::ostream& operator<<(std::ostream& stream, const vec2& vec);
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
	vec2 getNormalized() const;
	/// <summary>
	/// Calculates the dot product of this vector and rhs.
	/// </summary>
	/// <param name="rhs">The other vector to perform the dot product with.</param>
	/// <returns>The dot product between two vectors.</returns>
	float dot(const vec2& rhs) const;
	/// <summary>
	/// </summary>
	/// <returns>The string representation of this vector.</returns>
	std::string toString() const;


	static vec2 zero;
	static vec2 one;
	static vec2 up;
	static vec2 right;


	union
	{
		struct
		{
			float u, v;
		};
		struct
		{
			float x, y;
		};
		float data[2];
	};
};