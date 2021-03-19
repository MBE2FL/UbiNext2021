#include "stdafx.h"
#include "MathUtils.h"
#include "vec2.h"
#include "Collider2D.h"



float MathUtils::distPointToCircle2D(const vec2& point, const vec2& centre, const float radius)
{
    vec2 result = point - centre;
    return result.length() - radius;
}

float MathUtils::distPointToAABB2D(const vec2& point, const Bounds2D& bounds)
{
    float distX = std::max(0.0f, std::max(bounds.min.x - point.x, point.x - bounds.max.x));

    float distY = std::max(0.0f, std::max(bounds.min.y - point.y, point.y - bounds.max.y));

    return sqrtf((distX * distX) + (distY * distY));
}

float MathUtils::distSqrPointToAABB2D(const vec2& point, const Bounds2D& bounds)
{
    float distX = std::max(0.0f, std::max(bounds.min.x - point.x, point.x - bounds.max.x));

    float distY = std::max(0.0f, std::max(bounds.min.y - point.y, point.y - bounds.max.y));

    return (distX * distX) + (distY * distY);
}
