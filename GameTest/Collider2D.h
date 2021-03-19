#pragma once
//https://stackoverflow.com/questions/22899363/advice-on-class-structure-in-a-collision-detection-system
#include "stdafx.h"
#include "vec2.h"
#include "Component.h"
#include <functional>



class GameObject;
class Transform;
class Rigidbody2D;
class Collider2D;
class BoxCollider2D;
class CircleCollider2D;


enum class Collider2DType : uint8_t		// TO-DO Assign type in constructors.	TO-DO: Apply offset.
{
	NONE = 0,
	AABB = 1,
	CIRCLE = 2,
};




struct CollisionInfo2D
{
	Collider2D* collider;
	Collider2D* otherCollider;
	vec2 impactNormal;
	float penetrationDepth;
};




// Function callbacks
//typedef void (*onCollisionEnterSignature)(Collider&);				// Function pointer
//typedef void (Collider::* onCollisionEnterSignature)(Collider&);	// Member function pointer
typedef std::function<void(const CollisionInfo2D&)> OnCollisionEnter2DSignature;
typedef std::function<void(const CollisionInfo2D&)> OnCollisionStay2DSignature;
typedef std::function<void(const CollisionInfo2D&)> OnCollisionExit2DSignature;

typedef std::function<void(Collider2D*)> OnTriggerEnter2DSignature;
typedef std::function<void(Collider2D*)> OnTriggerStay2DSignature;
typedef std::function<void(Collider2D*)> OnTriggerExit2DSignature;




struct Bounds2D
{
	Bounds2D(const vec2& _centre = vec2::zero, const vec2& _size = vec2::one)
	{
		centre = _centre;
		size = _size;
		extends = size * 0.5f;
		min = centre - extends;
		max = centre + extends;
	}

	Bounds2D(const Bounds2D& other)
	{
		centre = other.centre;
		size = other.size;
		extends = other.extends;
		min = other.min;
		max = other.max;
	}

	Bounds2D& operator=(const Bounds2D& rhs)
	{
		centre = rhs.centre;
		size = rhs.size;
		extends = rhs.extends;
		min = rhs.min;
		max = rhs.max;

		return *this;
	}

	void recalculateBounds(const vec2& _min, const vec2& _max)
	{
		min = _min;
		max = _max;
		size = max - min;
		extends = size * 0.5f;
		centre = min + extends;
	}


	vec2 min;
	vec2 max;
	vec2 centre;
	vec2 extends;
	vec2 size;
};


class Collider2D : public Component
{
public:
	Collider2D() = delete;
	Collider2D(GameObject* gameObject, Transform* transform, Collider2DType colliderType)
		: Component(gameObject, transform), _colliderType(colliderType), _rigidbody(nullptr)
	{
	}
	virtual ~Collider2D() = default;


	inline Collider2DType getColliderType() const
	{
		return _colliderType;
	}

	inline bool getIsTrigger() const
	{
		return _isTrigger;
	}

	inline void setIsTrigger(bool isTrigger)
	{
		_isTrigger = isTrigger;
	}

	inline vec2 getOffset() const
	{
		return _offset;
	}

	inline void setOffset(const vec2& newOffset)
	{
		_offset = newOffset;
	}

	inline Rigidbody2D* getRigidbody() const
	{
		return _rigidbody;
	}

	inline void attachRigidbody(Rigidbody2D* rigidbody)
	{
		_rigidbody = rigidbody;
	}


	virtual void debugDraw() const = 0;


	bool operator==(const Collider2D& rhs) const
	{
		return (_colliderType == rhs._colliderType) &&
			(_isTrigger == rhs._isTrigger) &&
			(transform == rhs.transform);
	}

	virtual void updateBounds() = 0;

	virtual bool checkForCollision(Collider2D* other, CollisionInfo2D& info) = 0;
	virtual bool checkForCollision(BoxCollider2D* other, CollisionInfo2D& info) = 0;
	virtual bool checkForCollision(CircleCollider2D* other, CollisionInfo2D& info) = 0;


	OnCollisionEnter2DSignature onCollisionEnter;
	OnCollisionStay2DSignature onCollisionStay;
	OnCollisionExit2DSignature onCollisionExit;

	OnTriggerEnter2DSignature onTriggerEnter;
	OnTriggerStay2DSignature onTriggerStay;
	OnTriggerExit2DSignature onTriggerExit;


protected:
	Collider2DType _colliderType;
	bool _isTrigger = false;
	vec2 _offset;
	Rigidbody2D* _rigidbody;
};
