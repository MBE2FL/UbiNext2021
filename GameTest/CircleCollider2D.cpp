#include "stdafx.h"
#include "CircleCollider2D.h"
#include "Transform.h"
#include "vec3.h"
#include "MathUtils.h"
#include "BoxCollider2D.h"

#include "App/app.h"
#include "App/AppSettings.h"
#include "../glut/include/GL/freeglut.h"




CircleCollider2D::CircleCollider2D(GameObject* gameObject, Transform* transform, const vec2& _centre, const float _radius)
    : Collider2D(gameObject, transform, Collider2DType::CIRCLE), centre(_centre), radius(_radius), scaledRadius(_radius)
{
    transform->onTransformUpdated = std::bind(&CircleCollider2D::updateBounds, this); // TO-DO make onTransformUpdate an event system.
}

void CircleCollider2D::debugDraw() const
{
    mat4 localToWorld = transform->getLocalToWorldMatrix();
    vec2 visualCentre = vec2::zero;
    //visualCentre = vec2(_transform->getWorldPosition());

    //vec2 scale = vec2(_transform->getScale());

#if APP_USE_VIRTUAL_RES
    //scale.x /= APP_VIRTUAL_WIDTH;
    //scale.y /= APP_VIRTUAL_HEIGHT;

    //localToWorld.m00 /= APP_VIRTUAL_WIDTH;
    //localToWorld.m01 /= APP_VIRTUAL_WIDTH;
    //localToWorld.m02 /= APP_VIRTUAL_WIDTH;
    //localToWorld.m10 /= APP_VIRTUAL_HEIGHT;
    //localToWorld.m11 /= APP_VIRTUAL_HEIGHT;
    //localToWorld.m12 /= APP_VIRTUAL_HEIGHT;
#endif

#if APP_USE_VIRTUAL_RES
    //APP_VIRTUAL_TO_NATIVE_COORDS(localToWorld.m03, localToWorld.m13);
#endif


    size_t numTriangles = 20;
    float twicePI = 2.0f * PI;

    glPushMatrix();
    glOrtho(0.0f, APP_VIRTUAL_WIDTH, 0.0f, APP_VIRTUAL_HEIGHT, 0.0f, 1.0f);
    glMultMatrixf(localToWorld._data);
    //glLoadMatrixf(localToWorld._data);
    //glTranslatef(localToWorld.m03, localToWorld.m13, 0.0f);
    //glScalef(scale.x, scale.y, 0.1f);
    glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(visualCentre.x, visualCentre.y);

    for (size_t i = 0; i <= numTriangles; ++i)
    {
        float angle = i * twicePI / numTriangles;

        //vec2 test = vec2(visualCentre.x + (radius * cosf(angle)), visualCentre.y + (radius * sinf(angle)));
        //float lengthTest = test.length();

        glVertex2f(visualCentre.x + (radius * cosf(angle)),
            visualCentre.y + (radius * sinf(angle)));
    }

    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}

void CircleCollider2D::updateBounds()
{
    vec3 scale = transform->getScale();

    float maxScale = scale.x > scale.y ? scale.x : scale.y;

    scaledRadius = radius * maxScale;


    centre = vec2(transform->getWorldPosition());
}

bool CircleCollider2D::checkForCollision(Collider2D* other, CollisionInfo2D& info)
{

    return other->checkForCollision(this, info);
}

bool CircleCollider2D::checkForCollision(BoxCollider2D* other, CollisionInfo2D& info)
{
    //float dist = MathUtils::distSqrPointToAABB2D(centre, other->_bounds);
    //return dist <= (scaledRadius * scaledRadius);

    //float dist = MathUtils::distPointToAABB2D(centre, other->_bounds);
    //return dist <= scaledRadius;




    float dist = MathUtils::distPointToAABB2D(centre, other->_bounds);
    bool isColliding = dist <= scaledRadius;

    if (isColliding)
    {
        // Calculate the nearest point on the AABB.
        if (dist <= scaledRadius)
        {
            // Get the difference vector between the centre of this circle and the AABB.
            //vec2 otherToThis = _bounds.centre - other->centre;
            vec2 aTOb = centre - other->_bounds.centre;
            vec2 closestPoint;

            // Clamp the difference vector within the confines of the AABB.
            closestPoint.x = MathUtils::clamp(aTOb.x, -other->_bounds.extends.x, other->_bounds.extends.x);
            closestPoint.y = MathUtils::clamp(aTOb.y, -other->_bounds.extends.y, other->_bounds.extends.y);

            // Add the difference vector to the AABB's centre to calculate the nearest point in world space.
            //closestPoint += other->_bounds.centre;


            bool isInside = false;

            // This circle is inside the AABB. Clamp this circle's centre to the closest edge.
            //if ((closestPoint - aTOb).sqrLength() <= 0.25f)
            if (aTOb == closestPoint)
            {
                isInside = true;

                // Find the closest axis.
                // X-axis is closer.
                if (fabs(aTOb.x) > fabs(aTOb.y))
                {
                    // Clamp to the closest extend.
                   closestPoint.x = closestPoint.x > 0.0f ? other->_bounds.extends.x : -other->_bounds.extends.x;
                }
                // Y-axis is closer.
                else
                {
                    closestPoint.y = closestPoint.y > 0.0f ? other->_bounds.extends.y : -other->_bounds.extends.y;
                }
            }


            vec2 normal = aTOb - closestPoint;
            float sqrDist = normal.sqrLength();
            float radius = scaledRadius;


            // Radius is shorter than the distance to the closest point, and this circle is not inside of the AABB.
            // Return default values.
            if ((sqrDist > (radius * radius)) && !isInside)
            {
                info.impactNormal = vec2::up;
                info.penetrationDepth = radius;
                return false;
            }


            dist = sqrtf(sqrDist);
            normal /= dist;

            // Collision normal needs to be flipped to point outside if this circle was inside of the AABB.
            info.impactNormal = isInside ? -normal : normal;
            info.penetrationDepth = radius - dist;

            return true;
        }
    }


    // Return default values.
    info.impactNormal = vec2::up;
    info.penetrationDepth = radius;
    return false;
}

bool CircleCollider2D::checkForCollision(CircleCollider2D* other, CollisionInfo2D& info)
{
    //float radiiSum = scaledRadius + other->scaledRadius;
    //return (centre - other->centre).sqrLength() <= (radiiSum * radiiSum);


    //float radiiSum = scaledRadius + other->scaledRadius;
    //float sqrLength = (other->centre - centre).sqrLength();

    //// Collision has occured.
    //if (sqrLength <= (radiiSum * radiiSum))
    //{
    //    if (sqrLength > 0.0f)
    //    {
    //        // Calculate the normal and penetration depth of the collision.
    //        float length = sqrtf(sqrLength);

    //        info->impactNormal  = (other->centre - centre) / length;
    //        info->penetrationDepth = radiiSum - length;

    //        return true;
    //    }

    //    return false;
    //}
    //// Return default values.
    //else
    //{
    //    info->impactNormal = vec2::up;
    //    info->penetrationDepth = radius;
    //    return false;
    //}



    float radiiSum = other->scaledRadius + scaledRadius;
    float sqrLength = (centre - other->centre).sqrLength();

    // Collision has occured.
    if (sqrLength <= (radiiSum * radiiSum))
    {
        if (sqrLength > 0.0f)
        {
            // Calculate the normal and penetration depth of the collision.
            float length = sqrtf(sqrLength);

            info.impactNormal = (centre - other->centre) / length;
            info.penetrationDepth = radiiSum - length;

            return true;
        }

        return false;
    }
    // Return default values.
    else
    {
        info.impactNormal = vec2::up;
        info.penetrationDepth = radius;
        return false;
    }
}
