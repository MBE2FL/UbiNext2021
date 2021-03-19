#include "stdafx.h"
#include "BoxCollider2D.h"
#include "Transform.h"
#include "vec3.h"
#include "mat4.h"
#include "MathUtils.h"
#include "CircleCollider2D.h"
#include <math.h>

#include "App/app.h"
#include "App/AppSettings.h"
#include "../glut/include/GL/freeglut.h"


BoxCollider2D::BoxCollider2D(GameObject* gameObject, Transform* transform, const Bounds2D& bounds)
    : Collider2D(gameObject, transform, Collider2DType::AABB), _bounds(bounds)
{
    // Bottom Left
    _vertices[0] = _bounds.min;

    // Bottom Right
    _vertices[1] = _bounds.max;
    _vertices[1].y = _bounds.min.y;

    // Top Right
    _vertices[2] = _bounds.max;

    // Top Left
    _vertices[3] = _bounds.min;
    _vertices[3].y = _bounds.max.y;


    transform->onTransformUpdated = std::bind(&BoxCollider2D::updateBounds, this); // TO-DO make onTransformUpdate an event system.
}

BoxCollider2D::BoxCollider2D(GameObject* gameObject, Transform* transform, const vec2& centre, const vec2& size)
    : Collider2D(gameObject, transform, Collider2DType::AABB), _bounds(Bounds2D(centre, size))
{
    // Bottom Left
    _vertices[0] = _bounds.min;

    // Bottom Right
    _vertices[1] = _bounds.max;
    _vertices[1].y = _bounds.min.y;

    // Top Right
    _vertices[2] = _bounds.max;

    // Top Left
    _vertices[3] = _bounds.min;
    _vertices[3].y = _bounds.max.y;


    transform->onTransformUpdated = std::bind(&BoxCollider2D::updateBounds, this); // TO-DO make onTransformUpdate an event system.

    //// Top Left
    //_vertices[0] = _bounds.min;
    //_vertices[0].y = _bounds.max.y;

    //// Top Right
    //_vertices[1] = _bounds.max;

    //// Bottom Left
    //_vertices[2] = _bounds.min;

    //// Bottom Right
    //_vertices[3] = _bounds.max;
    //_vertices[3].y = _bounds.min.y;
}

void BoxCollider2D::debugDraw() const
{
    mat4 localToWorld = transform->getLocalToWorldMatrix();

#if APP_USE_VIRTUAL_RES
    //scale.x /= APP_VIRTUAL_WIDTH;
    //scale.y /= APP_VIRTUAL_HEIGHT;

    //localToWorld.m00 /= APP_VIRTUAL_WIDTH * 0.5f;
    ////localToWorld.m00 /= APP_VIRTUAL_WIDTH * 0.5f;
    ////localToWorld.m00 *= (2.0f / APP_VIRTUAL_WIDTH);
    //localToWorld.m01 /= APP_VIRTUAL_WIDTH;
    //localToWorld.m02 /= APP_VIRTUAL_WIDTH;
    //localToWorld.m10 /= APP_VIRTUAL_HEIGHT;
    //localToWorld.m11 /= APP_VIRTUAL_HEIGHT;
    //localToWorld.m12 /= APP_VIRTUAL_HEIGHT;
#endif

#if APP_USE_VIRTUAL_RES
    //APP_VIRTUAL_TO_NATIVE_COORDS(localToWorld.m03, localToWorld.m13);
#endif




    vec2 transformedVertices[4];
    for (size_t i = 0; i < 4; ++i)
    {
        transformedVertices[i] = vec2(localToWorld * vec4(_vertices[i], 0.0f, 1.0f));
    }

    vec2 min = transformedVertices[0];
    vec2 max = transformedVertices[0];

    for (size_t i = 0; i < 4; ++i)
    {
        // New min x found.
        if (transformedVertices[i].x < min.x)
        {
            min.x = transformedVertices[i].x;
        }
        // New max x found.
        else if (transformedVertices[i].x > max.x)
        {
            max.x = transformedVertices[i].x;
        }

        // New min y found.
        if (transformedVertices[i].y < min.y)
        {
            min.y = transformedVertices[i].y;
        }
        // New max y found.
        else if (transformedVertices[i].y > max.y)
        {
            max.y = transformedVertices[i].y;
        }
    }

    vec2 vertices[4];
    // Bottom Left
    vertices[0] = min;

    // Bottom Right
    vertices[1] = max;
    vertices[1].y = min.y;

    // Top Right
    vertices[2] = max;

    // Top Left
    vertices[3] = min;
    vertices[3].y = max.y;


    //mat4 getMat;

    glPushMatrix();
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glMultMatrixf(localToWorld._data);
    //glLoadMatrixf(localToWorld._data);
    //glTranslatef(translation.x, translation.y, 0.0f);
    //glScalef(scale.x, scale.y, 0.1f);
    //glRotatef(_transform->getLocalRotation().x, 1.0f, 0.0f, 0.0f);
    //glRotatef(_transform->getLocalRotation().y, 0.0f, 1.0f, 0.0f);
    //glRotatef(_transform->getLocalRotation().z, 0.0f, 0.0f, 1.0f);
    //glGetFloatv(GL_MODELVIEW_MATRIX, getMat._data);
#if APP_USE_VIRTUAL_RES
    glOrtho(0.0f, APP_VIRTUAL_WIDTH, 0.0f, APP_VIRTUAL_HEIGHT, 0.0f, 1.0f);
#else
    glOrtho(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
#endif
    glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
    for (size_t i = 0; i < 4; ++i)
    {
        //glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
        glVertex2f(vertices[i].x, vertices[i].y);
        //glVertex2f(_vertices[i].x, _vertices[i].y);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);









    //vec3 altPosition = _transform->getLocalPosition();
    //APP_VIRTUAL_TO_NATIVE_COORDS(altPosition.x, altPosition.y);
    //mat4 translation = mat4::translate(altPosition);

    //mat4 rotX = mat4::rotateX(_transform->getLocalRotation().x);
    //mat4 rotY = mat4::rotateY(_transform->getLocalRotation().y);
    //mat4 rotZ = mat4::rotateZ(_transform->getLocalRotation().z);
    //mat4 localRot = rotZ * rotY * rotX;

    //// Calculate scale matrix.
    //vec3 altScale = _transform->getScale();
    //altScale.x /= APP_VIRTUAL_WIDTH;
    //altScale.y /= APP_VIRTUAL_HEIGHT;
    //mat4 scale = mat4::scale(altScale);

    //// Calculate local transform matrix. T*R*S
    //mat4 localTransformMatrix = translation * localRot * scale;




    //for (size_t i = 0; i < 4; ++i)
    //{
    //    transformedVertices[i] = vec2(localTransformMatrix * vec4(_vertices[i], 0.0f, 1.0f));
    //}

    //min = transformedVertices[0];
    //max = transformedVertices[0];

    //for (size_t i = 0; i < 4; ++i)
    //{
    //    // New min x found.
    //    if (transformedVertices[i].x < min.x)
    //    {
    //        min.x = transformedVertices[i].x;
    //    }
    //    // New max x found.
    //    else if (transformedVertices[i].x > max.x)
    //    {
    //        max.x = transformedVertices[i].x;
    //    }

    //    // New min y found.
    //    if (transformedVertices[i].y < min.y)
    //    {
    //        min.y = transformedVertices[i].y;
    //    }
    //    // New max y found.
    //    else if (transformedVertices[i].y > max.y)
    //    {
    //        max.y = transformedVertices[i].y;
    //    }
    //}

    //// Bottom Left
    //vertices[0] = min;

    //// Bottom Right
    //vertices[1] = max;
    //vertices[1].y = min.y;

    //// Top Right
    //vertices[2] = max;

    //// Top Left
    //vertices[3] = min;
    //vertices[3].y = max.y;


    ////mat4 getMat;

    //glPushMatrix();
    ////glMatrixMode(GL_MODELVIEW);
    ////glLoadIdentity();
    ////glMultMatrixf(localToWorld._data);
    ////glLoadMatrixf(localTransformMatrix._data);
    ////glTranslatef(translation.x, translation.y, 0.0f);
    ////glScalef(scale.x, scale.y, 0.1f);
    ////glRotatef(_transform->getLocalRotation().x, 1.0f, 0.0f, 0.0f);
    ////glRotatef(_transform->getLocalRotation().y, 0.0f, 1.0f, 0.0f);
    ////glRotatef(_transform->getLocalRotation().z, 0.0f, 0.0f, 1.0f);
    ////glGetFloatv(GL_MODELVIEW_MATRIX, getMat._data);
    //glColor4f(0.0f, 0.0f, 1.0f, 0.7f);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glBegin(GL_QUADS);
    //for (size_t i = 0; i < 4; ++i)
    //{
    //    //glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    //    glVertex2f(vertices[i].x, vertices[i].y);
    //    //glVertex2f(_vertices[i].x, _vertices[i].y);
    //}
    //glEnd();
    //glPopMatrix();
    //glDisable(GL_BLEND);
}

void BoxCollider2D::updateBounds()
{
//    mat4 localToWorld = _transform->getLocalToWorldMatrix();
//
//#if APP_USE_VIRTUAL_RES
//    //scale.x /= APP_VIRTUAL_WIDTH;
//    //scale.y /= APP_VIRTUAL_HEIGHT;
//
//    localToWorld.m00 /= APP_VIRTUAL_WIDTH;
//    localToWorld.m01 /= APP_VIRTUAL_WIDTH;
//    localToWorld.m02 /= APP_VIRTUAL_WIDTH;
//    localToWorld.m10 /= APP_VIRTUAL_HEIGHT;
//    localToWorld.m11 /= APP_VIRTUAL_HEIGHT;
//    localToWorld.m12 /= APP_VIRTUAL_HEIGHT;
//#endif
//
//#if APP_USE_VIRTUAL_RES
//    APP_VIRTUAL_TO_NATIVE_COORDS(localToWorld.m03, localToWorld.m13);
//#endif


    // Transform the vertices of this collider by the transform of the object it is attached to.
    vec2 transformedVertices[4];
    for (size_t i = 0; i < 4; ++i)
    {
        transformedVertices[i] = vec2(transform->getLocalToWorldMatrix() * vec4(_vertices[i], 0.0f, 1.0f));
    }

    vec2 min = transformedVertices[0];
    vec2 max = transformedVertices[0];

    for (size_t i = 0; i < 4; ++i)
    {
        // New min x found.
        if (transformedVertices[i].x < min.x)
        {
            min.x = transformedVertices[i].x;
        }
        // New max x found.
        else if (transformedVertices[i].x > max.x)
        {
            max.x = transformedVertices[i].x;
        }

        // New min y found.
        if (transformedVertices[i].y < min.y)
        {
            min.y = transformedVertices[i].y;
        }
        // New max y found.
        else if (transformedVertices[i].y > max.y)
        {
            max.y = transformedVertices[i].y;
        }
    }


    // Recalculate bounds.
    _bounds.recalculateBounds(min, max);
}

bool BoxCollider2D::checkForCollision(Collider2D* other, CollisionInfo2D& info)
{
    return other->checkForCollision(this, info);
}

bool BoxCollider2D::checkForCollision(BoxCollider2D* other, CollisionInfo2D& info)
{
    
    //return ((_bounds.min.x < other->_bounds.max.x) && (_bounds.max.x > other->_bounds.min.x) &&
    //    (_bounds.min.y < other->_bounds.max.y) && (_bounds.max.y > other->_bounds.min.y));



    bool isColliding = ((_bounds.min.x < other->_bounds.max.x) && (_bounds.max.x > other->_bounds.min.x) &&
                        (_bounds.min.y < other->_bounds.max.y) && (_bounds.max.y > other->_bounds.min.y));

    //if (isColliding)
    //{
    //    const Bounds2D& otherBounds = other->_bounds;

    //    // Calculate the difference vector between both AABB's centres.
    //    vec2 otherToThis = otherBounds.centre - _bounds.centre;

    //    // Calculate the overlap in the X-axis.
    //    float xOverlap = _bounds.extends.x + otherBounds.extends.x - fabs(otherToThis.x);

    //    if (xOverlap > 0.0f)
    //    {
    //        // Calculate the overlap in the Y-axis.
    //        float yOverlap = _bounds.extends.y + otherBounds.extends.y - fabs(otherToThis.y);

    //        if (yOverlap > 0.0f)
    //        {
    //            // Find the axis of least penetration.
    //            if (xOverlap < yOverlap)
    //            {
    //                info->impactNormal = (otherToThis.x < 0.0f) ? -vec2::right : vec2::right;
    //                info->penetrationDepth = xOverlap;
    //                return true;
    //            }
    //            else
    //            {
    //                info->impactNormal = (otherToThis.y < 0.0f) ? -vec2::up : vec2::up;
    //                info->penetrationDepth = yOverlap;
    //                return true;
    //            }
    //        }
    //    }
    //}


    //// Return default values.
    //info->impactNormal = vec2::up;
    //info->penetrationDepth = _bounds.extends.y;
    //return false;



    if (isColliding)
    {
        const Bounds2D& otherBounds = other->_bounds;

        // Calculate the difference vector between both AABB's centres.
        vec2 aTOb = _bounds.centre - otherBounds.centre;

        // Calculate the overlap in the X-axis.
        float xOverlap = otherBounds.extends.x + _bounds.extends.x - fabs(aTOb.x);

        if (xOverlap > 0.0f)
        {
            // Calculate the overlap in the Y-axis.
            float yOverlap = otherBounds.extends.y + _bounds.extends.y - fabs(aTOb.y);

            if (yOverlap > 0.0f)
            {
                // Find the axis of least penetration.
                if (xOverlap < yOverlap)
                {
                    info.impactNormal = (aTOb.x < 0.0f) ? -vec2::right : vec2::right;
                    info.penetrationDepth = xOverlap;
                    return true;
                }
                else
                {
                    info.impactNormal = (aTOb.y < 0.0f) ? -vec2::up : vec2::up;
                    info.penetrationDepth = yOverlap;
                    return true;
                }
            }
        }
    }


    // Return default values.
    info.impactNormal = vec2::up;
    info.penetrationDepth = other->_bounds.extends.y;
    return false;

}

bool BoxCollider2D::checkForCollision(CircleCollider2D* other, CollisionInfo2D& info)
{
    //float dist = MathUtils::distSqrPointToAABB2D(other->centre, _bounds);
    //return dist <= (other->scaledRadius * other->scaledRadius);

    //float dist = MathUtils::distPointToAABB2D(other->centre, _bounds);
    //return dist <= other->scaledRadius;



    float dist = MathUtils::distPointToAABB2D(other->centre, _bounds);
    bool isColliding = dist <= other->scaledRadius;

    if (isColliding)
    {
        // Calculate the nearest point on this AABB.
        if (dist <= other->scaledRadius)
        {
            // Get the difference vector between the centre of the circle and this AABB.
            //vec2 otherToThis = _bounds.centre - other->centre;
            vec2 aTOb = _bounds.centre - other->centre;
            vec2 closestPoint;

            // Clamp the difference vector within the confines of this AABB.
            closestPoint.x = MathUtils::clamp(aTOb.x, -_bounds.extends.x, _bounds.extends.x);
            closestPoint.y = MathUtils::clamp(aTOb.y, -_bounds.extends.y, _bounds.extends.y);

            // Add the difference vector to this AABB's centre to calculate the nearest point in world space.
            //closestPoint += _bounds.centre;


            bool isInside = false;

            // The circle is inside this AABB. Clamp the circle's centre to the closest edge.
            if (aTOb == closestPoint)
            {
                isInside = true;

                // Find the closest axis.
                // X-axis is closer.
                if (fabs(aTOb.x) > fabs(aTOb.y))
                {
                    // Clamp to the closest extend.
                    closestPoint.x > 0.0f ? _bounds.extends.x : -_bounds.extends.x;
                }
                // Y-axis is closer.
                else
                {
                    closestPoint.y > 0.0f ? _bounds.extends.y : -_bounds.extends.y;
                }
            }


            vec2 normal = aTOb - closestPoint;
            float sqrDist = normal.sqrLength();
            float radius = other->scaledRadius;


            // Radius is shorter than the distance to the closest point, and the circle is not inside of this AABB.
            // Return default values.
            if ((sqrDist > (radius * radius)) && !isInside)
            {
                info.impactNormal = vec2::up;
                info.penetrationDepth = radius;
                return false;
            }


            dist = sqrtf(sqrDist);
            normal /= dist;

            // Collision normal needs to be flipped to point outside if the circle was inside of this AABB.
            info.impactNormal = isInside ? -normal : normal;
            info.penetrationDepth = radius - dist;

            return true;
        }
    }


    // Return default values.
    info.impactNormal = vec2::up;
    info.penetrationDepth = other->radius;
    return false;
}
