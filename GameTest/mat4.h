#pragma once
#include <iostream>
#include "vec4.h"



class vec3;
class quat;


class mat4
{
public:
	/// <summary>
	/// Initializes this matrix to the identity matrix.
	/// </summary>
	mat4();
	/// <summary>
	/// Constructs a matrix from the specified position, rotation, and scale.
	/// </summary>
	/// <param name="position">The translation component.</param>
	/// <param name="eulerAngles">The rotation component.</param>
	/// <param name="scale">The scale component.</param>
	mat4(const vec3& position, const vec3& eulerAngles, const vec3& scale);
	/// <summary>
	/// Constructs a matrix from the specified position, rotation, and scale.
	/// </summary>
	/// <param name="position">The translation component.</param>
	/// <param name="rotation">The rotation component.</param>
	/// <param name="scale">The scale component.</param>
	mat4(const vec3& position, const quat& rotation, const vec3& scale);
	/// <summary>
	/// Copy Constructor.
	/// </summary>
	/// <param name="other">The other matrix to copy.</param>
	mat4(const mat4& other);


	// ************ Operator Overloads ************
	mat4 operator+(const mat4& rhs) const;
	mat4 operator-(const mat4& rhs) const;
	mat4 operator*(const mat4& rhs) const;
	mat4 operator*(float scalar) const;
	vec4 operator*(const vec4& rhs) const;
	mat4 operator/(float scalar) const;
	mat4& operator=(const mat4& other);
	mat4& operator*=(const mat4& rhs);
	friend std::ostream& operator<<(std::ostream& stream, const mat4& mat);
	vec4& operator[](size_t column);
	const vec4& operator[](size_t column) const;


	void setRows(const vec4& firstRow, const vec4& secondRow, const vec4& thirdRow, const vec4& fourthRow);
	void getRows(vec4& firstRow, vec4& secondRow, vec4& thirdRow, vec4& fourthRow);
	vec4& getRow(size_t row);
	void setColumns(const vec4& firstColumn, const vec4& secondColumn, const vec4& thirdColumn, const vec4& fourthColumn);
	void getColumns(vec4& firstColumn, vec4& secondColumn, vec4& thirdColumn, vec4& fourthColumn);
	vec4& getColumn(size_t column);

	// ************ Utility Functions ************
	/// <summary>
	/// Calculates the inverse of this matrix.
	/// ONLY works on a homogeneous transformation matrix.
	/// For a regular matrix use slowInvert() instead.
	/// </summary>
	void invert();
	/// <summary>
	/// ONLY works on a homogeneous transformation matrix.
	/// For a regular matrix use getSlowInvert() instead.
	/// </summary>
	/// <returns>An inversed copy of this matrix.</returns>
	mat4 getInverse() const;
	/// <summary>
	/// Calculates the inverse of this matrix.
	/// </summary>
	void slowInvert();
	/// <summary>
	/// </summary>
	/// <returns>An inversed copy of this matrix.</returns>
	mat4 getSlowInvert() const;
	/// <summary>
	/// Transposes this matrix.
	/// </summary>
	void transpose();
	/// <summary>
	/// </summary>
	/// <returns>A transposed copy of this matrix.</returns>
	mat4 getTranspose() const;
	/// <summary>
	/// Generates a 3x3 matrix from a 4x4 matrix, ignoring the designated row and column.
	/// </summary>
	/// <param name="base">The original 4x4 matrix.</param>
	/// <param name="subMat">The 3x3 sub-matrix, after ignoring the designated row and column.</param>
	/// <param name="row">The row to ignore.</param>
	/// <param name="col">The column to ignore.</param>
	static void getSubMat(const mat4& base, mat4& subMat, size_t row, size_t col);
	/// <summary>
	/// Calculates the determinant of a 3x3 matrix.
	/// </summary>
	/// <param name="subMat">The sub-matrix to use. The last row and column of the 4x4 matrix are ignored.</param>
	/// <returns>The determinant of the 3x3 sub-matrix.</returns>
	static float mat3Det(const mat4& subMat);
	/// <summary>
	/// </summary>
	/// <returns>The determinant of this matrix.</returns>
	float determinant() const;
	/// <summary>
	/// </summary>
	/// <returns>The trace of this matrix.</returns>
	float trace() const;
	/// <summary>
	/// </summary>
	/// <param name="fovY">Vertical field of view.</param>
	/// <param name="aspect">Aspect ratio.</param>
	/// <param name="zNear">Near plane distance.</param>
	/// <param name="zFar">Far plane distance.</param>
	/// <returns>A perspective projection matrix.</returns>
	static mat4 perspective(float fovY, float aspect, float zNear, float zFar);
	/// <summary>
	/// </summary>
	/// <param name="left"></param>
	/// <param name="right"></param>
	/// <param name="bottom"></param>
	/// <param name="top"></param>
	/// <param name="near">Near plane distance.</param>
	/// <param name="far">Far plane distance.</param>
	/// <returns>An orthographic projection matrix.</returns>
	static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
	/// <summary>
	/// </summary>
	/// <returns>The translation component of this matrix.</returns>
	vec3 getTranslation() const;
	/// <summary>
	/// </summary>
	/// <returns>The up (Y-axis) of this matrix.</returns>
	vec3 getUp() const;
	/// <summary>
	/// </summary>
	/// <returns>The right (X-axis) of this matrix.</returns>
	vec3 getRight() const;
	/// <summary>
	/// </summary>
	/// <returns>The forward (Z-axis) of this matrix.</returns>
	vec3 getForward() const;


	// ************ Transformation functions ************
	/// <summary>
	/// Constructs a translation matrix.
	/// </summary>
	/// <param name="translation">The amount to translate the matrix by.</param>
	/// <returns></returns>
	static mat4 translate(const vec3& translation);
	/// <summary>
	/// Translates this matrix by the XYZ translation vector.
	/// </summary>
	/// <param name="x">The X component of the translation.</param>
	/// <param name="y">The Y component of the translation.</param>
	/// <param name="z">The Z component of the translation.</param>
	void translate(float x, float y, float z);
	/// <summary>
	/// Creates a rotation matrix, which represents a rotation around the specified axis by the given angle.
	/// </summary>
	/// <param name="axis">The axis to rotate around.</param>
	/// <param name="angle">The angle of rotation around the specified axis.</param>
	/// <returns>A rotation matrix representing the specified rotation.</returns>
	static mat4 rotate(const vec3& axis, float angle);
	/// <summary>
	/// Rotates this matrix around the specified axis by the given angle.
	/// </summary>
	/// <param name="x">The X component of the axis to rotate around.</param>
	/// <param name="y">The Y component of the axis to rotate around.</param>
	/// <param name="z">The Z component of the axis to rotate around.</param>
	/// <param name="angle">The angle of rotation around the specified axis.</param>
	void rotate(float x, float y, float z, float angle);
	/// <summary>
	/// Creates a rotation matrix around the X-axis by the given angle.
	/// </summary>
	/// <param name="angle">The angle of rotation around the X-axis.</param>
	/// <returns>A rotation matrix representing the specified rotation around the X-axis.</returns>
	static mat4 rotateX(float angle);
	/// <summary>
	/// Rotates a matrix around the X-axis by the given angle.
	/// </summary>
	/// <param name="mat">The matrix to rotate.</param>
	/// <param name="angle">The angle of rotation around the X-axis.</param>
	static void rotateX(mat4& mat, float angle);
	/// <summary>
	/// Creates a rotation matrix around the Y-axis by the given angle.
	/// </summary>
	/// <param name="angle">The angle of rotation around the Y-axis.</param>
	/// <returns>A rotation matrix representing the specified rotation around the Y-axis.</returns>
	static mat4 rotateY(float angle);
	/// <summary>
	/// Rotates a matrix around the Y-axis by the given angle.
	/// </summary>
	/// <param name="mat">The matrix to rotate.</param>
	/// <param name="angle">The angle of rotation around the Y-axis.</param>
	static void rotateY(mat4& mat, float angle);
	/// <summary>
	/// Creates a rotation matrix around the Z-axis by the given angle.
	/// </summary>
	/// <param name="angle">The angle of rotation around the Z-axis.</param>
	/// <returns>A rotation matrix representing the specified rotation around the Z-axis.</returns>
	static mat4 rotateZ(float angle);
	/// <summary>
	/// Rotates a matrix around the Z-axis by the given angle.
	/// </summary>
	/// <param name="mat">The matrix to rotate.</param>
	/// <param name="angle">The angle of rotation around the Z-axis.</param>
	static void rotateZ(mat4& mat, float angle);
	/// <summary>
	/// Creates a scale matrix based on the specified scale in the desired axes.
	/// </summary>
	/// <param name="scale">The scale in X, Y, and Z axes</param>
	/// <returns>A scale matrix representing the specified scale.</returns>
	static mat4 scale(const vec3& scale);
	/// <summary>
	/// Scales this matrix by the specified scale in the desired axes.
	/// </summary>
	/// <param name="x">The scale in the X-Axis.</param>
	/// <param name="y">The scale in the Y-Axis.</param>
	/// <param name="z">The scale in the Z-Axis.</param>
	void scale(float x, float y, float z);

	/// <summary>
	/// Creates a rotation matrix based on the given euler angles.
	/// </summary>
	/// <param name="eulerAngles">The angle of rotation around each axis.</param>
	/// <returns></returns>
	static mat4 getRotationFromEuler(const vec3& eulerAngles);
	/// <summary>
	/// </summary>
	/// <returns>The euler angles which represent the rotation of this matrix.</returns>
	vec3 getEuler() const;
	/// <summary>
	/// </summary>
	/// <returns>The quaternion which represent the rotation of this matrix.</returns>
	quat getQuaternion() const;


	static mat4 identity;

	union
	{
		struct
		{
			float m00, m10, m20, m30,
				m01, m11, m21, m31,
				m02, m12, m22, m32,
				m03, m13, m23, m33;
		};
		vec4 _columns[4];
		float _data[16];
	};
};