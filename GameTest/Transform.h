#pragma once
#include "stdafx.h"
#include "mat4.h"
#include "vec3.h"
#include "Component.h"
#include <functional>


class GameObject;


enum class TransformFlagBits : uint8_t
{
	NONE = 0,
	HAS_CHANGED = 1,
	IS_STATIC = 2,
	IS_ROOT = 4,
};
typedef uint8_t TransformFlags;

inline TransformFlagBits operator~(const TransformFlagBits& lhs)
{
	return static_cast<TransformFlagBits>(~static_cast<uint32_t>(lhs));
}

inline TransformFlagBits operator|(const TransformFlagBits& lhs, const TransformFlagBits& rhs)
{
	return static_cast<TransformFlagBits>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

inline TransformFlags operator|(const TransformFlags& lhs, const TransformFlagBits& rhs)
{
	return static_cast<TransformFlags>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

inline TransformFlagBits& operator|=(TransformFlagBits& lhs, const TransformFlagBits& rhs)
{
	lhs = static_cast<TransformFlagBits>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
	return lhs;
}

inline TransformFlags& operator|=(TransformFlags& lhs, const TransformFlagBits& rhs)
{
	lhs = static_cast<TransformFlags>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
	return lhs;
}

inline TransformFlagBits operator&(const TransformFlagBits& lhs, const TransformFlagBits& rhs)
{
	return static_cast<TransformFlagBits>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

inline TransformFlags operator&(const TransformFlags& lhs, const TransformFlagBits& rhs)
{
	return static_cast<TransformFlags>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

inline TransformFlagBits& operator&=(TransformFlagBits& lhs, const TransformFlagBits& rhs)
{
	lhs = static_cast<TransformFlagBits>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
	return lhs;
}

inline TransformFlags& operator&=(TransformFlags& lhs, const TransformFlagBits& rhs)
{
	lhs = static_cast<TransformFlags>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
	return lhs;
}

inline bool operator!=(const TransformFlags& lhs, const TransformFlagBits& rhs)
{
	return static_cast<uint8_t>(lhs) != static_cast<uint8_t>(rhs);
}

inline bool operator==(const TransformFlags& lhs, const TransformFlagBits& rhs)
{
	return static_cast<uint8_t>(lhs) == static_cast<uint8_t>(rhs);
}



typedef std::function<void()> OnTransformUpdatedSignature;



// TO-DO
/*
* Cache quaternion.
*/

class Transform : public Component
{
public:
	Transform() = delete;
	/// <summary>
	/// Creates a transform component with the specified name, position, rotation, scale, and parent.
	/// </summary>
	/// <param name="name">The name of this transform.</param>
	/// <param name="position">The position of this transform.</param>
	/// <param name="rotation">The rotation of this transform.</param>
	/// <param name="scale">The scale of this transform.</param>
	/// <param name="parent">The parent of this transform.</param>
	Transform(
		GameObject* _gameObject,
		const size_t eid,	// TO-DO: Look at copy and move stuff.
		const std::string& name, 
		const vec3& position = vec3::zero, 
		const vec3& rotation = vec3::zero, 
		const vec3& scale = vec3::one, 
		Transform* parent = nullptr);
	/// <summary>
	/// Copy Constructor.
	/// </summary>
	/// <param name="other">The other transform component to copy.</param>
	Transform(const Transform& other);
	/// <summary>
	/// Move Constructor.
	/// </summary>
	/// <param name="other">The other transform component to move.</param>
	Transform(Transform&& other) noexcept;
	
	~Transform();


	static inline const char* getBaseTypeName()
	{
		static const char* baseTypeName = "Transform";
		return baseTypeName;
	}


	/// <summary>
	/// Updates this transform component, iff it requires updating.
	/// </summary>
	/// <param name="deltaTime">The time since the last frame.</param>
	//void update(float deltaTime);

	void update();


	// ************ Operator Overloads ************
	Transform& operator=(const Transform& other);
	Transform& operator=(Transform&& other) noexcept;

	

	// ************ Parent/Child Functions ************
	/// <summary>
	/// Sets the parent of this transform component.
	/// </summary>
	/// <param name="parent">The parent to add this transfrom component as a child of.</param>
	void setParent(Transform* parent);
	/// <summary>
	/// Removes the parent of this transform component.
	/// </summary>
	void removeParent();
	/// <summary>
	/// Removes a child from this transform component.
	/// </summary>
	void unparent();
	/// <summary>
	/// Adds a child to this transform component.
	/// </summary>
	/// <param name="child">The child transform component.</param>
	void addChild(Transform* child);
	/// <summary>
	/// Adds a list of children to this transform component.
	/// </summary>
	/// <param name="children">The list of child transform components.</param>
	void addChildren(const std::vector<Transform*>& children);
	/// <summary>
	/// Removes a child from this transform component.
	/// </summary>
	/// <param name="index">The index of the child transform component.</param>
	void removeChild(size_t index);
	/// <summary>
	/// Removes a child from this transform component.
	/// </summary>
	/// <param name="child">The child transform component.</param>
	void removeChild(Transform* child);
	/// <summary>
	/// Removes all children from this transform component.
	/// </summary>
	void removeAllChildren();
	/// <summary>
	/// </summary>
	/// <param name="index">The index of the child transform component.</param>
	/// <returns>The child transform component at the specified index, or nullptr if the child does not exist.</returns>
	Transform* getChild(size_t index) const;
	/// <summary>
	/// </summary>
	/// <param name="name">The name of the child transform component.</param>
	/// <returns>The first child transform component with the specified name, or nullptr if the child does not exist.</returns>
	Transform* getChild(const std::string& name) const;
	/// <summary>
	/// </summary>
	/// <returns>All the children of this transform component.</returns>
	std::vector<Transform*>& getAllChidren();

	typedef std::vector<Transform*> vector_type;
	typedef vector_type::iterator child_iterator;
	typedef vector_type::const_iterator const_child_iterator;

	inline child_iterator begin() noexcept
	{
		return _children.begin();
	}

	inline const_child_iterator cbegin() noexcept
	{
		return _children.cbegin();
	}

	inline child_iterator end() noexcept
	{
		return _children.end();
	}

	inline const_child_iterator cend() noexcept
	{
		return _children.cend();
	}


	// ************ Utility Functions ************
	/// <summary>
	/// </summary>
	/// <returns>The name of this transform component.</returns>
	std::string getName() const;
	/// <summary>
	/// Set the name of this transform component.
	/// </summary>
	/// <param name="name">The new name.</param>
	void setName(const std::string& name);
	/// <summary>
	/// </summary>
	/// <returns>Whether or not this transform component is static.</returns>
	inline bool getIsStatic() const
	{
		return (_flags & TransformFlagBits::IS_STATIC) == TransformFlagBits::IS_STATIC;
	}
	/// <summary>
	/// Set this transform component to be static or not.
	/// </summary>
	/// <param name="isStatic">True for static, and false for not static.</param>
	void setIsStatic(bool isStatic);
	/// <summary>
	/// </summary>
	/// <returns>Whether this transform component is the root of it's parent/child hierarchy or not.</returns>
	bool isRoot() const;
	/// <summary>
	/// </summary>
	/// <returns>The parent of this object, or nullptr if this transform component has no parent.</returns>
	inline Transform* getParent() const
	{
		return _parent;
	}


	// ************ Transformation Functions ************
	/// <summary>
	/// </summary>
	/// <returns>The world space position of this transform component.</returns>
	vec3 getWorldPosition() const;
	/// <summary>
	/// Sets the world space position of this transform component.
	/// </summary>
	/// <param name="position">The new world space position.</param>
	void setWorldPosition(const vec3& position);
	/// <summary>
	/// </summary>
	/// <returns>The local space position of this transform component.</returns>
	vec3 getLocalPosition() const;
	/// <summary>
	/// Sets the local space position of this transform component.
	/// </summary>
	/// <param name="position">The new local space position.</param>
	void setLocalPosition(const vec3& position);

	/// <summary>
	/// </summary>
	/// <returns>The world space rotation of this transform component.</returns>
	vec3 getWorldRotation() const;
	/// <summary>
	/// Sets the world space rotation of this transform component.
	/// </summary>
	/// <param name="rotation">The new world space rotation.</param>
	void setWorldRotation(const vec3& rotation);
	/// <summary>
	/// </summary>
	/// <returns>The local space rotation of this transform component.</returns>
	vec3 getLocalRotation() const;
	/// <summary>
	/// Sets the local space rotation of this transform component.
	/// </summary>
	/// <param name="rotation">The new local space rotation.</param>
	void setLocalRotation(const vec3& rotation);

	/// <summary>
	/// </summary>
	/// <returns>The scale of this transform component.</returns>
	vec3 getScale() const;
	/// <summary>
	/// Sets the scale of this transform component.
	/// </summary>
	/// <param name="scale">The new scale.</param>
	void setScale(const vec3& scale);

	/// <summary>
	/// </summary>
	/// <returns>The local to world matrix of this transform component.</returns>
	mat4 getLocalToWorldMatrix() const;
	/// <summary>
	/// </summary>
	/// <returns>The local transformation matrix of this transform component.</returns>
	mat4 getLocalTransformMatrix() const;
	/// <summary>
	/// </summary>
	/// <returns>The local rotation matrix of this transform component.</returns>
	mat4 getLocalRotationMatrix() const;
	/// <summary>
	/// </summary>
	/// <returns>The orbit rotation matrix of this transform component.</returns>
	mat4 getOrbitRotationMatrix() const;

	/// <summary>
	/// </summary>
	/// <returns>The world space position of this transform component.</returns>
	vec3 getTranslation() const;
	/// <summary>
	/// </summary>
	/// <returns>The world space up (Y-axis) of this transform component.</returns>
	vec3 getUp() const;
	/// <summary>
	/// </summary>
	/// <returns>The world space right (X-axis) of this transform component.</returns>
	vec3 getRight() const;
	/// <summary>
	/// </summary>
	/// <returns>The world space forward (Z-axis) of this transform component.</returns>
	vec3 getForward() const;



	inline size_t getEid() const
	{
		return _eid;
	}


	OnTransformUpdatedSignature onTransformUpdated;


private:
	std::string _name;
	TransformFlags _flags;
	size_t _eid;

	vec3 _localPosition;
	vec3 _localRotation;
	vec3 _orbitRotation;
	vec3 _scale;
	mat4 _orbitRotationMatrix;
	mat4 _localRotationMatrix;
	mat4 _localTransformMatrix;
	mat4 _localToWorldMatrix;



	Transform* _parent = nullptr;
	std::vector<Transform*> _children;
	Transform* _rootComponent;


	static TransformFlags SHOULD_UPDATE;
};