// https://cxc.cfa.harvard.edu/mta/ASPECT/matrix_quat_faq/#Q55
// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
// https://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm
// https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm


#include "stdafx.h"
#include "quat.h"
#include "MathUtils.h"
#include "mat4.h"


quat quat::identity = quat();


quat::quat()
    : w(1.0f), x(0.0f), y(0.0f), z(0.0f)
{
}

quat::quat(float w, float x, float y, float z)
    : w(w), x(x), y(y), z(z)
{
    normalize();
}

quat::quat(const vec4& quatVec)
    : _data(quatVec)
{
    normalize();
}

quat::quat(const vec3& pureVec)
    : w(0.0f), x(pureVec.x), y(pureVec.y), z(pureVec.z)
{
}

quat::quat(float angle, const vec3& axis)
{
    // q = (cos(theta / 2), sin(theta / 2) * axis)

    float angleRads = MathUtils::toRadians(angle);
    scalarComp = cosf(angleRads * 0.5f);
    vecComp = sinf(angleRads * 0.5f) * axis;

    normalize();
}

quat::quat(const mat4& rotation)
{
    *this = rotation.getQuaternion();

    normalize();
}

quat::quat(float pitch, float yaw, float roll)
{
    //vec3 x = vec3::right;
    //vec3 y = vec3::up;
    //vec3 z = vec3::forward;

    //quat qx, qy, qz, result;

    //qx = quat(pitch, x);
    //qy = quat(yaw, y);
    //qz = quat(roll, z);

    //result = qx * qy;
    //*this = result * qz;



    float cosP = cosf(pitch * 0.5f);
    float cosY = cosf(yaw * 0.5f);
    float cosR = cosf(roll * 0.5f);
    float sinP = sinf(pitch * 0.5f);
    float sinY = sinf(yaw * 0.5f);
    float sinR = sinf(roll * 0.5f);

    w = (cosP * cosY * cosR) - (sinP * sinY * sinR);
    x = (sinY * sinR * cosP) + (cosY * cosR * sinP);
    y = (sinY * cosP * cosR) + (cosY * sinP * sinR);
    z = (cosY * sinR * cosP) - (sinY * cosR * sinP);

    normalize();
}

quat::quat(const quat& other)
    : _data(other._data)
{
}

quat quat::operator*(const quat& rhs) const
{
    quat result;
    result.w = (w * rhs.w) - vecComp.dot(rhs.vecComp);
    result.vecComp = (w * rhs.vecComp) + (rhs.w * vecComp) + vecComp.cross(rhs.vecComp);

    result.normalize();

    return result;
}

quat& quat::operator=(const quat& rhs)
{
    _data = rhs._data;

    return *this;
}

quat& quat::operator*=(const quat& rhs)
{
    w = (w * rhs.w) - vecComp.dot(rhs.vecComp);
    vecComp = (w * rhs.vecComp) + (rhs.w * vecComp) + vecComp.cross(rhs.vecComp);

    normalize();

    return *this;
}

std::ostream& operator<<(std::ostream& stream, const quat& quaternion)
{
    stream << "(W: " << quaternion.w << ", X: " << quaternion.x << ", Y: " << quaternion.y << ", Z: " << quaternion.z << ')';

    return stream;
}

void quat::conjugate()
{
    vecComp *= -1.0f;
}

quat quat::getConjugate() const
{
    quat result = *this;
    result.conjugate();

    return result;
}

void quat::rotate(float angle, const vec3& axis, vec3& vec)
{
    quat q = quat(angle, axis);
    quat v = quat(vec);
    quat qc = q.getConjugate();

    quat result = q * v * qc;
    result.normalize();

    vec = result.vecComp;
}

float quat::length() const
{
    return sqrt((w * w) + (x * x) + (y * y) + (z * z));
}

void quat::normalize()
{
    if ((w + x + y + z) == 0.0f)
    {
        return;
    }

    _data /= length();
}

quat quat::getNormalized() const
{
    quat result = *this;
    result.normalize();

    return result;
}

mat4 quat::getRotationMatrix() const
{
    mat4 result;

    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float xw = x * w;

    float yy = y * y;
    float yz = y * z;
    float yw = y * w;

    float zz = z * z;
    float zw = z * w;


    result.m00 = 1.0f - (2.0f * (yy + zz));
    result.m01 = 2.0f * (xy - zw);
    result.m02 = 2.0f * (xz + yw);

    result.m10 = 2.0f * (xy + zw);
    result.m11 = 1.0f - (2.0f * (xx + zz));
    result.m12 = 2.0f * (yz - xw);

    result.m20 = 2.0f * (xz - yw);
    result.m21 = 2.0f * (yz + xw);
    result.m22 = 1.0f - (2.0f * (xx + yy));

    result.m03 = result.m13 = result.m23 = result.m30 = result.m31 = result.m32 = 0.0f;
    result.m33 = 1.0f;

    return result;
}

vec3 quat::getEuler() const
{
    vec3 result;

    // Pitch (X-Axis)
    float sinP = 2.0f * ((w * y) - (z * x));
    if (abs(sinP) >= 1)
    {
        result.pitch = copysign(PI * 0.5f, sinP);
    }
    else
    {
        result.pitch = asin(sinP);
    }


    // Yaw (Y-Axis)
    float sinY_cosP = 2.0f * ((w * z) + (x * y));
    float cosY_cosP = 1.0f - 2.0f * ((y * y) + (z * z));
    result.yaw = atan2(sinY_cosP, cosY_cosP);


    // Roll (Z-Axis)
    float sinR_cosP = 2.0f * ((w * x) + (y * z));
    float cosR_cosP = 1.0f - 2.0f * ((x * x) + (y * y));
    result.roll = atan2(sinR_cosP, cosR_cosP);

    return result;
}

quat quat::slerp(const quat& start, const quat& end, float t)
{
    quat result;

    MathUtils::clamp(t, 0.0f, 1.0f);

    // Calculate the angle between the start and end quaternions.
    float cosHalfTheta = (start.w * end.w) + (start.x * end.x) + (start.y * end.y) + (start.z * end.z);

    // If start = end or start = -end then theta = 0, and result is the start quaternion.
    if (fabs(cosHalfTheta) >= 1.0f)
    {
        result = start;

        return result;
    }

    // Calculate temporary values.
    float halfTheta = acosf(cosHalfTheta);
    float sinHalfTheta = sqrtf(1.0f - (cosHalfTheta * cosHalfTheta));

    // If theta = 180 degrees then result is not fully defined.
    // Could rotate around any axis normal to start or end.
    if (fabs(sinHalfTheta) < 0.001f)
    {
        result.w = (start.w * 0.5f) + (end.w * 0.5f);
        result.x = (start.x * 0.5f) + (end.x * 0.5f);
        result.y = (start.y * 0.5f) + (end.y * 0.5f);
        result.z = (start.z * 0.5f) + (end.z * 0.5f);

        result.normalize();

        return result;
    }

    // Calculate quaternion.
    float ratioA = sinf((1.0f - t) * halfTheta) / sinHalfTheta;
    float ratioB = sinf(t * halfTheta) / sinHalfTheta;

    result.w = (start.w * ratioA) + (end.w * ratioB);
    result.x = (start.x * ratioA) + (end.x * ratioB);
    result.y = (start.y * ratioA) + (end.y * ratioB);
    result.z = (start.z * ratioA) + (end.z * ratioB);

    result.normalize();

    return result;
}

quat quat::nLerp(const quat& start, const quat& end, float t)
{
    quat result;

    result._data = MathUtils::lerp(start._data, end._data, t);
    result.normalize();

    return result;
}

std::string quat::toString() const
{
    return "(W: " + std::to_string(w) + ", X: " + std::to_string(x) + ", Y: " + std::to_string(y) + ", Z: " + std::to_string(z) + ')';;
}
