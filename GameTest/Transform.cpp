#include "stdafx.h"
#include "Transform.h"
#include "App/app.h"
#include "App/AppSettings.h"


TransformFlags Transform::SHOULD_UPDATE = static_cast<TransformFlags>(TransformFlagBits::HAS_CHANGED | TransformFlagBits::IS_ROOT);



//Transform::Transform(const std::string& name)
//    : _name(name), 
//    _flags(static_cast<TransformFlags>(TransformFlagBits::HAS_CHANGED)), 
//    _localPosition(vec3::zero), 
//    _localRotation(vec3::zero),
//    _scale(vec3::one)
//{
//}

Transform::Transform(GameObject* _gameObject, 
    const size_t eid, 
    const std::string& name, 
    const vec3& position, 
    const vec3& rotation, 
    const vec3& scale, 
    Transform* parent)
    : Component(_gameObject, this), 
    _eid(eid), 
    _name(name), 
    _flags(static_cast<TransformFlags>(TransformFlagBits::HAS_CHANGED | TransformFlagBits::IS_ROOT)), 
    _localPosition(position), 
    _localRotation(rotation), 
    _scale(scale)
{
    _rootComponent = this;
    setParent(parent);
}

Transform::Transform(const Transform& other)
    : Component(other)
{
    _name = other._name;
    _flags = other._flags;
    _localPosition = other._localPosition;
    _localRotation = other._localRotation;
    _orbitRotation = other._orbitRotation;
    _scale = other._scale;
    _orbitRotationMatrix = other._orbitRotationMatrix;
    _localRotationMatrix = other._localRotationMatrix;
    _localTransformMatrix = other._localTransformMatrix;
    _localToWorldMatrix = other._localToWorldMatrix;
    _rootComponent = other._rootComponent;
    setParent(other._parent);
}

Transform::Transform(Transform&& other) noexcept
    : Component(std::move(other))
{
    _name = std::move(other._name);
    _flags = other._flags | TransformFlagBits::IS_ROOT;
    _localPosition = other._localPosition;
    _localRotation = other._localRotation;
    _orbitRotation = other._orbitRotation;
    _scale = other._scale;
    _orbitRotationMatrix = std::move(other._orbitRotationMatrix);
    _localRotationMatrix = std::move(other._localRotationMatrix);
    _localTransformMatrix = std::move(other._localTransformMatrix);
    _localToWorldMatrix = std::move(other._localToWorldMatrix);
    _parent = std::move(other._parent);
    _children = std::move(other._children);
    _rootComponent = std::move(other._rootComponent);
    
    other._parent = nullptr;
    other._children.clear();
    other._rootComponent = nullptr;
}

Transform::~Transform()
{
    //delete _parent;
    _parent = nullptr;

    _children.clear();
}

void Transform::update()
{
    //// Check if this transform has changed and is not static.
    //if (((_rootComponent->_flags & TransformFlagBits::HAS_CHANGED) == TransformFlagBits::HAS_CHANGED) &&
    //    ((_flags & TransformFlagBits::IS_STATIC) != TransformFlagBits::IS_STATIC))
    //{

        //// Calculate translation matrix.
        //mat4 trans = mat4::translate(_localPosition);

        //// Calculate local rotation matrix. Rotation order: XYZ
        //mat4 rotX = mat4::rotateX(_localRotation.pitch);
        //mat4 rotY = mat4::rotateY(_localRotation.yaw);
        //mat4 rotZ = mat4::rotateZ(_localRotation.roll);
        //mat4 localRot = rotZ * rotY * rotX;

        //// Calculate scale matrix.
        //mat4 scale = mat4::scale(_scale);

        //// Calculate local transform matrix. T*R*S
        //_localTransformMatrix = trans * localRot * scale;


        //// Combine local transform with parent's transform to compute global transform.
        //if (_parent)
        //{
        //    _localToWorldMatrix = _parent->_localToWorldMatrix * _localTransformMatrix;
        //}
        //// Global transform is the same as the local transform.
        //else
        //{
        //    _localToWorldMatrix = _localTransformMatrix;
        //}


        //// Update all children of this transform.
        //for (Transform* child : _children)
        //{
        //    child->update(deltaTime);
        //}


        //// Update flags.
        //_rootComponent->_flags &= ~TransformFlagBits::HAS_CHANGED;


        //// Notify any listeners.
        //if (onTransformUpdated)
        //{
        //    onTransformUpdated();
        //}
    //}



    // Check if this transform has changed and is not static.
    if ((_flags & TransformFlagBits::IS_STATIC) != TransformFlagBits::IS_STATIC)
    {
        // Update all children of this transform.
        for (Transform* child : _children)
        {
            child->update();
        }


        // Notify any listeners.
        if (onTransformUpdated)
        {
            onTransformUpdated();
        }
    }
}

Transform& Transform::operator=(const Transform& other)
{
    _name = other._name;
    _flags = other._flags;
    _localPosition = other._localPosition;
    _localRotation = other._localRotation;
    _orbitRotation = other._orbitRotation;
    _scale = other._scale;
    _orbitRotationMatrix = other._orbitRotationMatrix;
    _localRotationMatrix = other._localRotationMatrix;
    _localTransformMatrix = other._localTransformMatrix;
    _localToWorldMatrix = other._localToWorldMatrix;
    _rootComponent = other._rootComponent;
    setParent(other._parent);

    return *this;
}

Transform& Transform::operator=(Transform&& other) noexcept
{
    _name = std::move(other._name);
    _flags = other._flags;
    _localPosition = other._localPosition;
    _localRotation = other._localRotation;
    _orbitRotation = other._orbitRotation;
    _scale = other._scale;
    _orbitRotationMatrix = std::move(other._orbitRotationMatrix);
    _localRotationMatrix = std::move(other._localRotationMatrix);
    _localTransformMatrix = std::move(other._localTransformMatrix);
    _localToWorldMatrix = std::move(other._localToWorldMatrix);
    _parent = std::move(other._parent);
    _children = std::move(other._children);
    _rootComponent = std::move(other._rootComponent);

    other._parent = nullptr;
    other._children.clear();
    other._rootComponent = nullptr;

    return *this;
}

void Transform::setParent(Transform* parent)
{
    if (parent)
    {
        vec3 worldPos = getWorldPosition();

        // Update parent and root component.
        _parent = parent;
        _rootComponent = parent->_rootComponent;


        _rootComponent->_flags |= TransformFlagBits::HAS_CHANGED;
        _flags &= ~TransformFlagBits::HAS_CHANGED;
        _flags &= ~TransformFlagBits::IS_ROOT;


        // Update this transform component.
        setWorldPosition(worldPos);
    }
}

void Transform::removeParent()
{
    vec3 worldPos = getWorldPosition();


    _parent = nullptr;
    _flags |= TransformFlagBits::HAS_CHANGED & TransformFlagBits::IS_ROOT;
    _rootComponent = this;


    // Update this transform component.
    setLocalPosition(worldPos);
}

void Transform::unparent()
{
    _parent->removeChild(this);
}

void Transform::addChild(Transform* child)
{
    _children.push_back(child);
    child->setParent(this);
}

void Transform::addChildren(const std::vector<Transform*>& children)
{
    _parent = nullptr;
    _rootComponent->_flags |= TransformFlagBits::HAS_CHANGED;
}

void Transform::removeChild(size_t index)
{
    // Remove the child at the given index.
    if (index >= _children.size())
    {
        // Swap the child at the given index with the one at the end of the vector to speed up removal.
        Transform* temp = _children.back();
        _children[index]->removeParent();
        _children[index] = temp;
        _children.pop_back();
    }
}

void Transform::removeChild(Transform* child)
{
    std::vector<Transform*>::iterator it = _children.begin();

    for (; it != _children.end(); ++it)
    {
        if ((*it)->_eid == child->_eid)
        {
            child->removeParent();
            _children.erase(it);
            return;
        }
    }
}

void Transform::removeAllChildren()
{
    std::vector<Transform*>::iterator it = _children.begin();

    for (; it != _children.end();)
    {
        (*it)->_parent->removeParent();
        _children.erase(it);
    }
}

Transform* Transform::getChild(size_t index) const
{
    if (index >= _children.size())
    {
        return _children[index];
    }
    else
    {
        return nullptr;
    }
}

Transform* Transform::getChild(const std::string& name) const
{
    std::vector<Transform*>::const_iterator it = _children.cbegin();

    for (; it != _children.end();)
    {
        Transform* currChild = *it;

        if (currChild->getName() == name)
        {
            return currChild;
        }
        else
        {
            ++it;
        }
    }

    return nullptr;
}

std::vector<Transform*>& Transform::getAllChidren()
{
    return _children;
}

std::string Transform::getName() const
{
    return _name;
}

void Transform::setName(const std::string& name)
{
    _name = name;
}

void Transform::setIsStatic(bool isStatic)
{
    if (isStatic)
    {
        _flags |= TransformFlagBits::IS_STATIC;
    }
    else
    {
        _flags &= ~TransformFlagBits::IS_STATIC;
    }
}

bool Transform::isRoot() const
{
    return (_flags & TransformFlagBits::IS_ROOT) == TransformFlagBits::IS_ROOT;
}

vec3 Transform::getWorldPosition() const
{
    return _localToWorldMatrix.getTranslation();
}

void Transform::setWorldPosition(const vec3& position)
{
    //if ((_flags & TransformFlagBits::IS_STATIC) != TransformFlagBits::IS_STATIC)
    //{
    //    if (_parent)
    //    {
    //        vec3 localPosition = vec3(_parent->_localToWorldMatrix.getInverse() * vec4(position));  // TO-DO Check the order of operations.
    //        setLocalPosition(localPosition);
    //    }
    //    else
    //    {
    //        setLocalPosition(position);
    //    }
    //}



    if ((_flags & TransformFlagBits::IS_STATIC) != TransformFlagBits::IS_STATIC)
    {
        _localToWorldMatrix.m03 = position.x;
        _localToWorldMatrix.m13 = position.y;
        _localToWorldMatrix.m23 = position.z;

        if (_parent)
        {
            _localPosition = vec3(_parent->getLocalToWorldMatrix().getInverse() * vec4(position, 1.0f));  // TO-DO Check the order of operations.
            //setLocalPosition(localPosition);

            _localTransformMatrix.m03 = _localPosition.x;
            _localTransformMatrix.m13 = _localPosition.y;
            _localTransformMatrix.m23 = _localPosition.z;
        }
        else
        {
            _localTransformMatrix.m03 = position.x;
            _localTransformMatrix.m13 = position.y;
            _localTransformMatrix.m23 = position.z;

            _localPosition = position;
        }


        // Update this transform component.
        update();
    }
}

vec3 Transform::getLocalPosition() const
{
    return _localPosition;
}

void Transform::setLocalPosition(const vec3& position)
{
    //if ((_flags & TransformFlagBits::IS_STATIC) != TransformFlagBits::IS_STATIC)
    //{
    //    _localPosition = position;
    //    _rootComponent->_flags |= TransformFlagBits::HAS_CHANGED;
    //}



    if ((_flags & TransformFlagBits::IS_STATIC) != TransformFlagBits::IS_STATIC)
    {
            //_localToWorldMatrix * _localPosition;

        _localTransformMatrix.m03 = position.x;
        _localTransformMatrix.m13 = position.y;
        _localTransformMatrix.m23 = position.z;

        if (_parent)
        {
            _localToWorldMatrix = _parent->getLocalToWorldMatrix() * _localTransformMatrix;
        }
        else
        {
            _localToWorldMatrix.m03 = position.x;
            _localToWorldMatrix.m13 = position.y;
            _localToWorldMatrix.m23 = position.z;
        }
        
        _localPosition = position;
        _rootComponent->_flags |= TransformFlagBits::HAS_CHANGED;


        // Update this transform component.
        update();
    }
}

vec3 Transform::getWorldRotation() const
{
    return _localToWorldMatrix.getEuler();
}

void Transform::setWorldRotation(const vec3& rotation)
{
    if ((_flags & TransformFlagBits::IS_STATIC) != TransformFlagBits::IS_STATIC)
    {
        if (_parent)
        {
            //_localRotation = (_parent->getLocalToWorldMatrix().getInverse() * mat4::getRotationFromEuler(rotation)).getEuler();
            //setLocalPosition(localRotation);


            //// Calculate translation matrix.
            //mat4 trans = mat4::translate(_localPosition);

            //// Calculate local rotation matrix. Rotation order: XYZ
            //mat4 rotX = mat4::rotateX(_localRotation.pitch);
            //mat4 rotY = mat4::rotateY(_localRotation.yaw);
            //mat4 rotZ = mat4::rotateZ(_localRotation.roll);
            //mat4 localRot = rotZ * rotY * rotX;

            //// Calculate scale matrix.
            //mat4 scale = mat4::scale(_scale);

            // Calculate local transform matrix. T*R*S
            //_localTransformMatrix = trans * localRot * scale;

            //_localToWorldMatrix = _parent->getLocalToWorldMatrix() * _localTransformMatrix;
        }
        else
        {
            _localRotation = rotation;

            // Calculate translation matrix.
            mat4 trans = mat4::translate(_localPosition);

            // Calculate local rotation matrix. Rotation order: XYZ
            mat4 rotX = mat4::rotateX(_localRotation.pitch);
            mat4 rotY = mat4::rotateY(_localRotation.yaw);
            mat4 rotZ = mat4::rotateZ(_localRotation.roll);
            mat4 localRot = rotZ * rotY * rotX;

            // Calculate scale matrix.
            mat4 scale = mat4::scale(_scale);

            // Calculate local transform matrix. T*R*S
            _localTransformMatrix = trans * localRot * scale;

            _localToWorldMatrix = _localTransformMatrix;
        }


        // Update this transform component.
        update();
    }
}

vec3 Transform::getLocalRotation() const
{
    return _localRotation;
}

void Transform::setLocalRotation(const vec3& rotation)
{
    if ((_flags & TransformFlagBits::IS_STATIC) != TransformFlagBits::IS_STATIC)
    {
        _localRotation = rotation;
        _rootComponent->_flags |= TransformFlagBits::HAS_CHANGED;


        // Calculate translation matrix.
        mat4 trans = mat4::translate(_localPosition);

        // Calculate local rotation matrix. Rotation order: XYZ
        mat4 rotX = mat4::rotateX(_localRotation.pitch);
        mat4 rotY = mat4::rotateY(_localRotation.yaw);
        mat4 rotZ = mat4::rotateZ(_localRotation.roll);
        mat4 localRot = rotZ * rotY * rotX;

        // Calculate scale matrix.
        mat4 scale = mat4::scale(_scale);

        // Calculate local transform matrix. T*R*S
        _localTransformMatrix = trans * localRot * scale;


        if (_parent)
        {
            _localToWorldMatrix = _parent->getLocalToWorldMatrix() * _localTransformMatrix;
        }
        else
        {
            _localToWorldMatrix = _localTransformMatrix;
        }



        // Update this transform component.
        update();
    }
}

vec3 Transform::getScale() const
{
    return _scale;
}

void Transform::setScale(const vec3& scale)
{
    if ((_flags & TransformFlagBits::IS_STATIC) != TransformFlagBits::IS_STATIC)
    {
        _scale = scale;
        _rootComponent->_flags |= TransformFlagBits::HAS_CHANGED;


        // Calculate translation matrix.
        mat4 trans = mat4::translate(_localPosition);

        // Calculate local rotation matrix. Rotation order: XYZ
        mat4 rotX = mat4::rotateX(_localRotation.pitch);
        mat4 rotY = mat4::rotateY(_localRotation.yaw);
        mat4 rotZ = mat4::rotateZ(_localRotation.roll);
        mat4 localRot = rotZ * rotY * rotX;

        // Calculate scale matrix.
        mat4 scale = mat4::scale(_scale);

        // Calculate local transform matrix. T*R*S
        _localTransformMatrix = trans * localRot * scale;


        if (_parent)
        {
            _localToWorldMatrix = _parent->getLocalToWorldMatrix() * _localTransformMatrix;
        }
        else
        {
            _localToWorldMatrix = _localTransformMatrix;
        }


        // Update this transform component.
        update();
    }
}

mat4 Transform::getLocalToWorldMatrix() const
{
    return _localToWorldMatrix;
}

mat4 Transform::getLocalTransformMatrix() const
{
    return _localTransformMatrix;
}

mat4 Transform::getLocalRotationMatrix() const
{
    return _localRotationMatrix;
}

mat4 Transform::getOrbitRotationMatrix() const
{
    return _orbitRotationMatrix;
}

vec3 Transform::getTranslation() const
{
    return _localToWorldMatrix.getTranslation();
}

vec3 Transform::getUp() const
{
    return _localToWorldMatrix.getUp();
}

vec3 Transform::getRight() const
{
    return _localToWorldMatrix.getRight();
}

vec3 Transform::getForward() const
{
    return _localToWorldMatrix.getForward();
}
