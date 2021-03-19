#include "stdafx.h"
#include "Rigidbody2D.h"
#include "Transform.h"




Rigidbody2D::Rigidbody2D(GameObject* gameObject, Transform* transform, float mass, float restitution, float drag, bool useGravity, bool isKinematic)
	: Component(gameObject, transform), _mass(mass), _invMass(1.0f / mass), _restitution(restitution), _drag(drag), _useGravity(useGravity), _isKinematic(isKinematic)
{
}

void Rigidbody2D::addForce(const vec2& force, ForceType forceType)
{
	// Don't apply any forces to this rigidbody if it is kinematic.
	if (_isKinematic)
	{
		return;
	}

	switch (forceType)
	{
	case ForceType::CONTINUOUS:
		_force += force;
		break;
	case ForceType::IMPULSE:
		_velocity += _invMass * force;
		break;
	default:
		break;
	}
}

void Rigidbody2D::update(float deltaTime)
{
	if (_useGravity)
	{
		_force -= vec2(0.0f, 9.81f * 100.0f);
	}

	// f = ma => a = f/m
	vec2 acceleration = _invMass * _force;
	_velocity += acceleration * deltaTime;

	// p_t = p_t-1 + v * t + 0.5 *a * t^2
	vec3 dragForce = vec3(0.5f * _drag * _velocity * _velocity);	// TO-DO Fix drag.
	vec3 newPos = transform->getWorldPosition() + (vec3(_velocity) * deltaTime) + vec3(0.5f * acceleration * deltaTime * deltaTime);
	transform->setWorldPosition(newPos);

	_force = vec2::zero;
}
