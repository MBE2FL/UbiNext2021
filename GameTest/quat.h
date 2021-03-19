#pragma once
#include "vec3.h"
#include "vec4.h"



class mat4;



class quat
{
public:
	/// <summary>
	/// Initializes W to 1, and XYZ to 0.
	/// </summary>
	quat();
	/// <summary>
	/// Initializes each component.
	/// </summary>
	/// <param name="w">W Component</param>
	/// <param name="x">X Component</param>
	/// <param name="y">Y Component</param>
	/// <param name="z">Z Component</param>
	quat(float w, float x, float y, float z);
	/// <summary>
	/// W, X, Y, and Z will be initialized by the XYZW components of the vec4.
	/// </summary>
	/// <param name="quatVec">The X, Y, Z, and W components.</param>
	quat(const vec4& quatVec);
	/// <summary>
	/// Creates a pure quaternion from a vec3.
	/// </summary>
	/// <param name="pureVec">The X, Y, and Z components.</param>
	quat(const vec3& pureVec);
	/// <summary>
	/// Creates a quaternion from the given the angle of rotation around the specified axis.
	/// </summary>
	/// <param name="angle">The angle of rotation around the specified axis.</param>
	/// <param name="axis">The axis to rotate around.</param>
	quat(float angle, const vec3& axis);
	/// <summary>
	/// Creates a quaternion from a rotation matrix.
	/// </summary>
	/// <param name="rotation"></param>
	quat(const mat4& rotation);
	/// <summary>
	/// Creates a quaternion from the specified euler angles.
	/// </summary>
	/// <param name="pitch">Degrees around the X axis.</param>
	/// <param name="yaw">Degrees around the Y axis.</param>
	/// <param name="roll">Degrees around the Z axis.</param>
	quat(float pitch, float yaw, float roll);
	/// <summary>
	/// Copy Constructor.
	/// </summary>
	/// <param name="other">The other quaternion to copy.</param>
	quat(const quat& other);


	// ************ Operator Overloads ************
	quat operator*(const quat& rhs) const;
	quat& operator=(const quat& rhs);
	quat& operator*=(const quat& rhs);
	friend std::ostream& operator<<(std::ostream& stream, const quat& quaternion);


	// ************ Utility Functions ************
	/// <summary>
	/// Negates/inverses this quaternion.
	/// </summary>
	void conjugate();
	/// <summary>
	/// Returns a conjugated copy of this quaternion.
	/// </summary>
	/// <returns></returns>
	quat getConjugate() const;
	/// <summary>
	/// Rotates a vector around the given axis by the specified angle.
	/// </summary>
	/// <param name="angle">The angle of rotation around the specified axis.</param>
	/// <param name="axis">The axis to rotate around.</param>
	/// <param name="vec">The vector to rotate.</param>
	static void rotate(float angle, const vec3& axis, vec3& vec);
	/// <summary>
	/// </summary>
	/// <returns>Returns the length of this quaternion.</returns>
	float length() const;
	/// <summary>
	/// Normalizes this quaternion.
	/// </summary>
	void normalize();
	/// <summary>
	/// </summary>
	/// <returns>A normalized copy of this quaternion.</returns>
	quat getNormalized() const;
	/// <summary>
	/// </summary>
	/// <returns>A rotation matrix generated from this quaternion.</returns>
	mat4 getRotationMatrix() const;
	/// <summary>
	/// </summary>
	/// <returns>Euler angles calculated from this quaternion.</returns>
	vec3 getEuler() const;
	/// <summary>
	/// Performs a spherical linear interpolation from start to end based on t.
	/// </summary>
	/// <param name="start">The starting starting rotation.</param>
	/// <param name="end">The ending rotation.</param>
	/// <param name="t">The amount to interpolate by.</param>
	/// <returns>A quaternion representing a rotation between start and end.</returns>
	static quat slerp(const quat& start, const quat& end, float t);
	/// <summary>
	/// Performs a normalized linear interpolation from start to end based on t.
	/// </summary>
	/// <param name="start">The starting starting rotation.</param>
	/// <param name="end">The ending rotation.</param>
	/// <param name="t">The amount to interpolate by.</param>
	/// <returns>A quaternion representing a rotation between start and end.</returns>
	static quat nLerp(const quat& start, const quat& end, float t);
	/// <summary>
	/// </summary>
	/// <returns>The string representation of this quaternion.</returns>
	std::string toString() const;


	static quat identity;


	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			vec3 vecComp;
			float scalarComp;
		};
		vec4 _data;
	};
};