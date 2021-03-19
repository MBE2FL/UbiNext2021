// https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix


#include "stdafx.h"
#include "mat4.h"
#include "vec3.h"
#include "MathUtils.h"
#include "quat.h"


mat4 mat4::identity = mat4();


mat4::mat4()
{
    _columns[0] = vec4(1.0f, 0.0f, 0.0f, 0.0f);
    _columns[1] = vec4(0.0f, 1.0f, 0.0f, 0.0f);
    _columns[2] = vec4(0.0f, 0.0f, 1.0f, 0.0f);
    _columns[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

mat4::mat4(const vec3& position, const vec3& eulerAngles, const vec3& scale)
{
    *this = identity;


    // Calculate scale matrix.
    mat4 scaleMat = mat4::scale(scale);


    // Calculate rotation matrix.
    mat4 rotMat = getRotationFromEuler(eulerAngles);


    // Calculate translation matrix.
    mat4 translationMat = translate(position);


    // Result = TRS
    *this = translationMat * rotMat * scaleMat;
}

mat4::mat4(const vec3& position, const quat& rotation, const vec3& scale)
{
    *this = identity;


    // Calculate scale matrix.
    mat4 scaleMat = mat4::scale(scale);


    // Calculate rotation matrix.
    mat4 rotMat = rotation.getRotationMatrix();


    // Calculate translation matrix.
    mat4 translationMat = translate(position);


    // Result = TRS
    *this = translationMat * rotMat * scaleMat;
}

mat4::mat4(const mat4& other)
{
    memcpy(_columns, other._columns, sizeof(mat4));
}

mat4 mat4::operator+(const mat4& rhs) const
{
    mat4 result = *this;
    result[0] = result[0] + rhs[0];
    result[1] = result[1] + rhs[1];
    result[2] = result[2] + rhs[2];
    result[3] = result[3] + rhs[3];

    return result;
}

mat4 mat4::operator-(const mat4& rhs) const
{
    mat4 result = *this;
    result[0] = result[0] - rhs[0];
    result[1] = result[1] - rhs[1];
    result[2] = result[2] - rhs[2];
    result[3] = result[3] - rhs[3];

    return result;
}

mat4 mat4::operator*(const mat4& rhs) const
{
    mat4 result;

    //result[0][0] = (_data[0][0] * rhs[0][0]) + (_data[1][0] * rhs[0][1]) + (_data[2][0] * rhs[0][2]) + (_data[3][0] * rhs[0][3]);

    // First row of lhs * every column of rhs.
    result.m00 = (m00 * rhs.m00) + (m01 * rhs.m10) + (m02 * rhs.m20) + (m03 * rhs.m30);
    result.m01 = (m00 * rhs.m01) + (m01 * rhs.m11) + (m02 * rhs.m21) + (m03 * rhs.m31);
    result.m02 = (m00 * rhs.m02) + (m01 * rhs.m12) + (m02 * rhs.m22) + (m03 * rhs.m32);
    result.m03 = (m00 * rhs.m03) + (m01 * rhs.m13) + (m02 * rhs.m23) + (m03 * rhs.m33);

    // Second row of lhs * every column of rhs.
    result.m10 = (m10 * rhs.m00) + (m11 * rhs.m10) + (m12 * rhs.m20) + (m13 * rhs.m30);
    result.m11 = (m10 * rhs.m01) + (m11 * rhs.m11) + (m12 * rhs.m21) + (m13 * rhs.m31);
    result.m12 = (m10 * rhs.m02) + (m11 * rhs.m12) + (m12 * rhs.m22) + (m13 * rhs.m32);
    result.m13 = (m10 * rhs.m03) + (m11 * rhs.m13) + (m12 * rhs.m23) + (m13 * rhs.m33);

    // Third row of lhs * every column of rhs.
    result.m20 = (m20 * rhs.m00) + (m21 * rhs.m10) + (m22 * rhs.m20) + (m23 * rhs.m30);
    result.m21 = (m20 * rhs.m01) + (m21 * rhs.m11) + (m22 * rhs.m21) + (m23 * rhs.m31);
    result.m22 = (m20 * rhs.m02) + (m21 * rhs.m12) + (m22 * rhs.m22) + (m23 * rhs.m32);
    result.m23 = (m20 * rhs.m03) + (m21 * rhs.m13) + (m22 * rhs.m23) + (m23 * rhs.m33);

    // Fourth row of lhs * every column of rhs.
    result.m30 = (m30 * rhs.m00) + (m31 * rhs.m10) + (m32 * rhs.m20) + (m33 * rhs.m30);
    result.m31 = (m30 * rhs.m01) + (m31 * rhs.m11) + (m32 * rhs.m21) + (m33 * rhs.m31);
    result.m32 = (m30 * rhs.m02) + (m31 * rhs.m12) + (m32 * rhs.m22) + (m33 * rhs.m32);
    result.m33 = (m30 * rhs.m03) + (m31 * rhs.m13) + (m32 * rhs.m23) + (m33 * rhs.m33);

    return result;
}

mat4 mat4::operator*(float scalar) const
{
    mat4 result = *this;
    result[0] *= scalar;
    result[0] *= scalar;
    result[0] *= scalar;
    result[0] *= scalar;

    return result;
}

vec4 mat4::operator*(const vec4& rhs) const
{
    vec4 result;
    result.x = (m00 * rhs.x) + (m01 * rhs.y) + (m02 * rhs.z) + (m03 * rhs.w);
    result.y = (m10 * rhs.x) + (m11 * rhs.y) + (m12 * rhs.z) + (m13 * rhs.w);
    result.z = (m20 * rhs.x) + (m21 * rhs.y) + (m22 * rhs.z) + (m23 * rhs.w);
    result.w = (m30 * rhs.x) + (m31 * rhs.y) + (m32 * rhs.z) + (m33 * rhs.w);

    return result;
}

mat4 mat4::operator/(float scalar) const
{
    mat4 result = *this;
    result[0] /= scalar;
    result[0] /= scalar;
    result[0] /= scalar;
    result[0] /= scalar;

    return result;
}

mat4& mat4::operator=(const mat4& other)
{
    memcpy(_data, other._data, sizeof(float) * 16);

    return *this;
}

mat4& mat4::operator*=(const mat4& rhs)
{
    _columns[0] = vec4(_columns[0][0], _columns[1][0], _columns[2][0], _columns[3][0]) * rhs[0];
    _columns[1] = vec4(_columns[0][1], _columns[1][1], _columns[2][1], _columns[3][1]) * rhs[1];
    _columns[2] = vec4(_columns[0][2], _columns[1][2], _columns[2][2], _columns[3][2]) * rhs[2];
    _columns[3] = vec4(_columns[0][3], _columns[1][3], _columns[2][3], _columns[3][3]) * rhs[3];

    return *this;
}

vec4& mat4::operator[](size_t column)
{
    return _columns[column];
}

const vec4& mat4::operator[](size_t column) const
{
    return _columns[column];
}

std::ostream& operator<<(std::ostream& stream, const mat4& mat)
{
    stream << mat[0][0] << " | " << mat[1][0] << " | " << mat[2][0] << " | " << mat[3][0] << '\n' <<
        mat[0][1] << " | " << mat[1][1] << " | " << mat[2][1] << " | " << mat[3][1] << '\n' <<
        mat[0][2] << " | " << mat[1][2] << " | " << mat[2][2] << " | " << mat[3][2] << '\n' <<
        mat[0][3] << " | " << mat[1][3] << " | " << mat[2][3] << " | " << mat[3][3];

    return stream;
}

void mat4::invert()
{
    // -R^t * T

    // Inverse calculation trick ONLY for transformation matrices.
    /* Transformation = |  R  | t |
    *                   | 000 | 1 |
    * 
    *  Inverse Transformation = | R^T | -R^T * t |
    *                           | 000 |     1    |
    */ 

    mat4 result = *this;
    result[3] = vec4::zero;
    result.transpose();

    vec4 translation = -(result * _columns[3]);
    translation.w = 1.0f;
    
    result[3] = translation;

    *this = result;
}

mat4 mat4::getInverse() const
{
    mat4 result = *this;
    result.invert();

    return result;
}

void mat4::slowInvert()
{
    float det = determinant();

    // Determinant is less than or close to 0. The inverse cannot be calculated.
    if (fabs(det) < 0.0005f)
    {
        *this = mat4::identity;
    }
    // The inverse can be calculated.
    else
    {
        for (size_t row = 0; row < 4; ++row)
        {
            for (size_t col = 0; col < 4; ++col)
            {
                int32_t sign = 1 - (((row + col) % 2) * 2);

                mat4 subMat;
                getSubMat(*this, subMat, row, col);

                _data[row + (col * 4)] = (mat3Det(subMat) * sign) / det;
            }
        }
    }
}

mat4 mat4::getSlowInvert() const
{
    mat4 result = *this;
    result.slowInvert();

    return result;
}

void mat4::transpose()
{
    // Swap the first row with the first column.
    std::swap(m01, m10);
    std::swap(m02, m20);
    std::swap(m03, m30);

    // Swap the remaining second row with the remaining second column.
    std::swap(m12, m21);
    std::swap(m13, m31);

    // Swap the remaining third row with the remaining thrid column.
    std::swap(m32, m23);
}

mat4 mat4::getTranspose() const
{
    // Construct a copy of this matrix, and transpose it.
    mat4 result(*this);
    result.transpose();

    return result;
}

void mat4::getSubMat(const mat4& base, mat4& subMat, size_t row, size_t col)
{
    size_t targetRow, targetCol, rowDst, colDst;
    memset(subMat._data, 0, sizeof(float) * 16);    // Set all elements to 0.


    for (targetRow = 0; targetRow < 4; ++targetRow)
    {
        // Use target row as the row destination.
        if (targetRow < row)
        {
            rowDst = targetRow;
        }
        else
        {
            // Use target row - 1 as the row destination.
            // Essentially removes the designated row, and shifts all the following rows up.
            if (targetRow > row)
            {
                rowDst = targetRow - 1;
            }
        }

        for (targetCol = 0; targetCol < 4; ++targetCol)
        {
            // Use target column as the column destination.
            if (targetCol < col)
            {
                colDst = targetCol;
            }
            else
            {
                // Use target column - 1 as the column destination.
                // Essentially removes the designated column, and shifts all the following columns left.
                if (targetCol > col)
                {
                    colDst = targetCol - 1;
                }
            }

            // Only add elements not from the desginated row and column to the sub-matrix.
            if ((targetRow != row) && (targetCol != col))
            {
                subMat[colDst][rowDst] = base[targetCol][targetRow];
            }
        }
    }
}

float mat4::mat3Det(const mat4& subMat)
{
    float det;

    det = subMat.m00 * ((subMat.m11 * subMat.m22) - (subMat.m12 * subMat.m21))
        - subMat.m01 * ((subMat.m10 * subMat.m22) - (subMat.m12 * subMat.m20))
        + subMat.m02 * ((subMat.m10 * subMat.m21) - (subMat.m11 * subMat.m20));

    return det;
}

float mat4::determinant() const
{
    float det = 0.0f;
    float result = 0.0f;
    float i = 1.0f;

    for (size_t col = 0; col < 4; ++col, i *= -1)
    {
        mat4 subMat;
        getSubMat(*this, subMat, 0, col);

        det = mat3Det(subMat);
        
        result += _columns[0][col] * det * i;
    }

    //float detM00 = (m11 * ((m22 * m33) - (m23 * m32))) - (m01 * ((m11 * m22) - (m13 * m21)));


    return result;
}

float mat4::trace() const
{
    return m00 + m11 + m22 + m33;
}

mat4 mat4::perspective(float fovY, float aspect, float zNear, float zFar)
{
    mat4 result;

    result.m00 = 1.0f / (aspect * tanf(MathUtils::toRadians((fovY * 0.5f))));
    result.m11 = 1.0f / tanf(MathUtils::toRadians((fovY * 0.5f)));
    result.m22 = -(zFar / (zFar - zNear));
    result.m23 = -1.0f;
    result.m32 = -((zFar * zNear) * (zFar - zNear));

    result.m33 = 0.0f;

    return result;
}

mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
    mat4 result;

    result.m00 = 2.0f / (right - left);
    result.m11 = 2.0f / (top - bottom);
    result.m22 = -2.0f / (far - near);
    result.m30 = -((right + left) / (right - left));
    result.m31 = -((top + bottom) / (top - bottom));
    result.m32 = -((far + near) / (far - near));

    return result;
}

vec3 mat4::getTranslation() const
{
    return static_cast<vec3>(_columns[3]);
}

vec3 mat4::getUp() const
{
    return static_cast<vec3>(_columns[1]);
}

vec3 mat4::getRight() const
{
    return static_cast<vec3>(_columns[0]);
}

vec3 mat4::getForward() const
{
    return static_cast<vec3>(_columns[2]);
}

mat4 mat4::translate(const vec3& translation)
{
    mat4 result;
    result[3] = vec4(translation, 1.0f);

    return result;
}

void mat4::translate(float x, float y, float z)
{
    mat4 translation = translate(vec3(x, y, z));
    *this *= translation;

    //_columns[3] += vec4(x, y, z, 0.0f);
}

mat4 mat4::rotate(const vec3& axis, float angle)
{
    mat4 result;

    quat q = quat(angle, axis);

    return q.getRotationMatrix();
}

void mat4::rotate(float x, float y, float z, float angle)
{
    mat4 rotMat = quat(angle, vec3(x, y, z)).getRotationMatrix();
    *this *= rotMat;
}

mat4 mat4::rotateX(float angle)
{
    mat4 result;

    angle = MathUtils::toRadians(angle);

    result.m11 = cosf(angle);
    result.m12 = -sinf(angle);
    result.m21 = sinf(angle);
    result.m22 = cosf(angle);

    return result;
}

void mat4::rotateX(mat4& mat, float angle)
{
    mat *= rotateX(angle);
}

mat4 mat4::rotateY(float angle)
{
    mat4 result;

    angle = MathUtils::toRadians(angle);

    result.m00 = cosf(angle);
    result.m02 = sinf(angle);
    result.m20 = -sinf(angle);
    result.m22 = cosf(angle);

    return result;
}

void mat4::rotateY(mat4& mat, float angle)
{
    mat *= rotateY(angle);
}

mat4 mat4::rotateZ(float angle)
{
    mat4 result;

    angle = MathUtils::toRadians(angle);

    result.m00 = cosf(angle);
    result.m01 = -sinf(angle);
    result.m10 = sinf(angle);
    result.m11 = cosf(angle);

    return result;
}

void mat4::rotateZ(mat4& mat, float angle)
{
    mat *= rotateZ(angle);
}

mat4 mat4::scale(const vec3& scale)
{
    mat4 result;
    result.m00 = scale.x;
    result.m11 = scale.y;
    result.m22 = scale.z;

    return result;
}

void mat4::scale(float x, float y, float z)
{
    mat4 scaleMat = scale(vec3(x, y, z));
    *this *= scaleMat;

    //m00 *= x;
    //m11 *= y;
    //m22 *= z;
}

mat4 mat4::getRotationFromEuler(const vec3& eulerAngles)
{
    mat4 result;

    vec3 angleInRads;
    angleInRads.x = MathUtils::toRadians(eulerAngles.x);
    angleInRads.y = MathUtils::toRadians(eulerAngles.y);
    angleInRads.z = MathUtils::toRadians(eulerAngles.z);

    float a = cosf(angleInRads.x);
    float b = sinf(angleInRads.x);
    float c = cosf(angleInRads.y);
    float d = sinf(angleInRads.y);
    float e = cosf(angleInRads.z);
    float f = sinf(angleInRads.z);

    float ad = a * d;
    float bd = b * d;

    result.m00 = c * e;
    result.m01 = -c * f;
    result.m02 = -d;

    result.m10 = (-bd * e) + (a * f);
    result.m11 = (bd * f) + (a * e);
    result.m12 = -b * c;

    result.m20 = (ad * e) + (b * f);
    result.m21 = (-ad * f) + (b * e);
    result.m22 = a * c;

    result.m03 = result.m13 = result.m23 = result.m30 = result.m31 = result.m32 = 0.0f;
    result.m33 = 1.0f;

    return result;
}

vec3 mat4::getEuler() const
{
    float angleX, angleY, angleZ = 0.0f;
    float d;


    // Y-axis angle.
    angleY = d = -asinf(m02);
    float c = cosf(angleY);

    angleY *= MathUtils::toDegrees(angleY);


    // Gimbal lock has not occurred.
    if (fabs(c) > 0.005f)
    {
        // X-axis angle.
        float x = m22 / c;
        float y = -m12 / c;

        //angleX = atan2f(y, x) * RADIANS;
        angleX = MathUtils::toDegrees(atan2f(y, x));

        // Z-axis angle.
        x = m00 / c;
        y = -m01 / c;

        //angleZ = atan2f(y, x) * RADIANS;
        angleZ = MathUtils::toDegrees(atan2f(y, x));
    }
    // Gimbal lock has occurred
    else
    {
        // X-axis angle.
        angleX = 0.0f;

        // Z-axis angle.
        float x = m11;
        float y = m10;

        //angleZ = atan2(y, x) * RADIANS;
        angleZ = MathUtils::toDegrees(atan2(y, x));
    }

    // Clamp all angles.
    angleX = MathUtils::clamp(angleX, 0.0f, 360.0f);
    angleY = MathUtils::clamp(angleY, 0.0f, 360.0f);
    angleZ = MathUtils::clamp(angleZ, 0.0f, 360.0f);


    return vec3(angleX, angleY, angleZ);
}

quat mat4::getQuaternion() const
{
    quat result;
    float t = trace();

    // Trace is greater than 0.
    if (t > 0.0f)
    {
        float s = 0.5f / sqrt(t);

        result.w = 0.25f / s;
        result.x = (m21 - m12) * s;
        result.y = (m02 - m20) * s;
        result.z = (m10 - m01) * s;
    }
    // Trace is less or equal to 0.
    else
    {
        // Find which major diagonal element has the greatest value.
        
        // Column 0
        if ((m00 >= m11) && (m00 >= m22))
        {
            float s = sqrt(1.0f + m00 - m11 - m22) * 2.0f;

            result.w = (m12 + m21) / s;
            result.x = 0.5f / s;
            result.y = (m01 + m10) / s;
            result.z = (m02 + m20) / s;
        }
        // Column 1
        else if (m11 >= m22)
        {
            float s = sqrt(1.0f + m11 - m00 - m22) * 2.0f;

            result.w = (m02 + m02) / s;
            result.x = (m01 + m10) / s;
            result.y = 0.5f / s;
            result.z = (m12 + m21) / s;
        }
        // Column 2
        else
        {
            float s = sqrt(1.0f + m22 - m00 - m11) * 2.0f;

            result.w = (m01 + m10) / s;
            result.x = (m02 + m20) / s;
            result.y = (m12 + m21) / s;
            result.z = 0.5f / s;
        }
    }

    return result;
}
