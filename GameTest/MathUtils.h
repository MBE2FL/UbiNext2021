#pragma once
#include "App/AppSettings.h"

//#define PI 3.14159f

class vec2;
struct Bounds2D;

namespace MathUtils
{
	/// <summary>
	/// Converts degrees to radians.
	/// </summary>
	inline float toRadians(float degrees);
	/// <summary>
	/// Converts degrees to radians.
	/// </summary>
	inline float toDegrees(float radians);
	/// <summary>
	/// Clamps the specified value between the specified min and max values inclusively.
	/// </summary>
	/// <param name="value">The value to clamp.</param>
	/// <param name="min">The minimum value.</param>
	/// <param name="max">The maximum value.</param>
	/// <returns>The value clamped between min and max inclusively.</returns>
	inline float clamp(float value, float min, float max);

    /// <summary>
    /// Linearly interpolates between the start and end values by t.
    /// </summary>
    /// <typeparam name="T">Value Type</typeparam>
    /// <param name="start">The starting value.</param>
    /// <param name="end">The ending value.</param>
    /// <param name="t">The interpolation value. (0.0 - 1.0)</param>
    /// <returns>A value between start and end inclusively.</returns>
    template<typename T>
    T lerp(const T& start, const T& end, float t);
    /// <summary>
    /// Calculates the interpolation value needed to generate the specified value when interpolating from start to end.
    /// </summary>
    /// <typeparam name="T">Value Type</typeparam>
    /// <param name="value">The interpolated value between start and end inclusively.</param>
    /// <param name="start">The starting value.</param>
    /// <param name="end">The ending value.</param>
    /// <returns>The interpolation value needed to calculate the specified value.</returns>
    template<typename T>
    T invLerp(const T& value, const T& start, const T& end);


    float distPointToCircle2D(const vec2& point, const vec2& centre, const float radius);

    float distPointToAABB2D(const vec2& point, const Bounds2D& bounds);

    float distSqrPointToAABB2D(const vec2& point, const Bounds2D& bounds);
}


float MathUtils::toRadians(float degrees)
{
    return degrees * PI / 180.0f;
}

float MathUtils::toDegrees(float radians)
{
    return radians * 180.0f / PI;
}

float MathUtils::clamp(float value, float min, float max)
{
    value = value < min ? min : value;
    value = value > max ? max : value;

    return value;
}

template<typename T>
T MathUtils::lerp(const T& start, const T& end, float t)
{
    t = MathUtils::clamp(t, 0.0f, 1.0f);

    T result = ((1.0f - t) * start) + (t * end);

    return result;
}

template<typename T>
T MathUtils::invLerp(const T& value, const T& start, const T& end)
{
    if (start == end)
    {
        return 0.0f;
    }
    else
    {
        return ((value - start) / (end - start))
    }
}