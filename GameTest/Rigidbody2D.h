#pragma once
#include "vec2.h"
#include "Component.h"
#include <stdint.h>



class GameObject;
class Transform;



enum class ForceType : uint8_t
{
	CONTINUOUS,
	IMPULSE
};



class Rigidbody2D : public Component
{
public:
	Rigidbody2D(GameObject* gameObject, Transform* transform, float mass = 1.0f, float restitution = 1.0f, float drag = 0.0f, bool useGravity = false, bool isKinematic = false);
	~Rigidbody2D() = default;


	void addForce(const vec2& force, ForceType forceType);
	void update(float deltaTime);

	
	inline float getInvMass() const
	{
		return _invMass;
	}

	inline float getRestitution() const
	{
		return _restitution;
	}

	inline vec2 getVelocity() const
	{
		return _velocity;
	}

	inline float getDrag() const
	{
		return _drag;
	}

	inline void setDrag(float drag)
	{
		_drag = drag;
	}

	inline bool getIsKinematic() const
	{
		return _isKinematic;
	}

	inline void setIsKinematic(bool isKinematic)
	{
		// Clear any stored forces when changing _isKinematic.
		if (_isKinematic != isKinematic)
		{
			_force = vec2::zero;
		}

		_isKinematic = isKinematic;
	}


private:
	float _mass;
	float _invMass;
	float _restitution;
	vec2 _force = vec2::zero;
	vec2 _velocity = vec2::zero;
	float _drag = 0.0f;
	bool _useGravity;
	bool _isActive = false;
	bool _isKinematic;
};