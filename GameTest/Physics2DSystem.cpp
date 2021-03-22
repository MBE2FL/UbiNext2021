#include "stdafx.h"
#include "Physics2DSystem.h"
#include "ComponentManager.h"
#include "Collider2D.h"
#include "Transform.h"
#include "Rigidbody2D.h"
#include "GameObject.h"



Physics2DSystem::Physics2DSystem()
{
}

Physics2DSystem::~Physics2DSystem()
{
}

void Physics2DSystem::update(float deltaTime)
{
	// Save the previous frames collisions.
	_prevFrameCollisions = _collisions;
	_collisions.clear();



	ComponentManager* compManager = ComponentManager::getInstance();

	ComponentArray<Collider2D>* colliders = nullptr;
	if (!compManager->getAllComponentsOfType<Collider2D>(&colliders))
	{
		return;
	}



	// Compare every collider against every collider that comes after it in the component array.
	ComponentArray<Collider2D>::iterator currentIt;
	for (currentIt = colliders->begin(); currentIt != colliders->end(); ++currentIt)
	{
		Collider2D* currentCollider = *currentIt;


		// Skip checking for collisions on static objects.
		if (currentCollider->transform->getIsStatic())
		{
			continue;
		}


		// Get the next collider.
		ComponentArray<Collider2D>::iterator otherIt = currentIt;
		//++otherIt;

		for (otherIt = currentIt + 1; otherIt != colliders->end(); ++otherIt)
		{
			Collider2D* otherCollider = *otherIt;



			// TO-DO: Check if either collider is marked for removal.
			// TO-DO: mass ratio and positional correction.


			// Skip checking for collisions on static objects.
			if (otherCollider->transform->getIsStatic())
			{
				continue;
			}

			if (!currentCollider->gameObject->getIsActive() || !otherCollider->gameObject->getIsActive())
			{
				continue;
			}


			// Check for collision between the two colliders.
			CollisionInfo2D info;
			if (currentCollider->checkForCollision(otherCollider, info))
			{
				resolveCollision(currentCollider, otherCollider, info);
			}
		}
	}



	// Check for any collisions which may have stopped this frame.
	std::unordered_set<Collision2D*>::iterator prevColIt;
	for (prevColIt = _prevFrameCollisions.begin(); prevColIt != _prevFrameCollisions.end(); ++prevColIt)
	{
		Collision2D* prevCol = *prevColIt;

		if (_collisions.count(prevCol) == 0)
		{
			verifyCollisions(prevCol->colliderOne, prevCol->colliderTwo);

			delete prevCol;
			prevCol = nullptr;
		}
	}



	// Update all rigidbodies.
	ComponentArray<Rigidbody2D>* rigidbodies = nullptr;
	if (!compManager->getAllComponentsOfType<Rigidbody2D>(&rigidbodies))
	{
		return;
	}

	ComponentArray<Rigidbody2D>::iterator rbIt;
	for (rbIt = rigidbodies->begin(); rbIt != rigidbodies->end(); ++rbIt)
	{
		Rigidbody2D* rb = *rbIt;

		if (!rb->gameObject->getIsActive())
		{
			continue;
		}

		// Don't apply any forces to a kinematic rigidbody.
		if (rb->getIsKinematic())
		{
			continue;
		}

		rb->update(deltaTime);
	}
}

void Physics2DSystem::debugDraw() const
{
	ComponentManager* compManager = ComponentManager::getInstance();

	ComponentArray<Collider2D>* colliders = nullptr;
	if (!compManager->getAllComponentsOfType<Collider2D>(&colliders))
	{
		return;
	}

	for (const Collider2D* collider : *colliders)
	{
		if (collider->gameObject->getIsActive())
		{
			collider->debugDraw();
		}
	}
}

void Physics2DSystem::resolveCollision(Collider2D* currentCollider, Collider2D* otherCollider, CollisionInfo2D& info)
{
	Collision2D* collision2D = new Collision2D();
	collision2D->colliderOne = currentCollider;
	collision2D->colliderTwo = otherCollider;

	_collisions.insert(collision2D);
	//_collisions.insert(std::move(*collision2D));
	//std::pair<std::unordered_set<Collision2D*>::iterator, bool> result = _prevFrameCollisions.insert(collision2D);
	bool result = _prevFrameCollisions.count(collision2D) == 0;

	// First frame the collision occured.
	if (result)
	{
		// Current collider is a trigger.
		if (currentCollider->getIsTrigger())
		{
			if (currentCollider->onTriggerEnter)
			{
				currentCollider->onTriggerEnter(otherCollider);
			}

			// Both colliders are triggers.
			if (otherCollider->getIsTrigger())
			{
				if (otherCollider->onTriggerEnter)
				{
					otherCollider->onTriggerEnter(currentCollider);
				}
			}
		}
		// Current collider is not a trigger.
		else
		{
			// Only the other collider is a trigger.
			if (otherCollider->getIsTrigger())
			{
				if (otherCollider->onTriggerEnter)
				{
					otherCollider->onTriggerEnter(currentCollider);
				}
			}
			// Both colliders are not triggers.
			else
			{
				// Calculate impulse resolution force.
				Rigidbody2D* currentRB = currentCollider->getRigidbody();
				Rigidbody2D* otherRB = otherCollider->getRigidbody();


				// Both objects must have rigidbodies in order to collide.
				if (!currentRB || !otherRB)
					return;


				// Calculate relative velocity from the other object to the current object.
				// Calculate relative velocity along the collision normal's direction.
				float relVel = (otherRB->getVelocity() - currentRB->getVelocity()).dot(info.impactNormal);

				// Do not resolve if the velocities are separating.
				if (relVel > 0.0f)
				{
					//continue;
					return;
				}

				// Use lowest restitution(elasticity or bounciness) of the two objects
				float e = std::min(currentRB->getRestitution(), otherRB->getRestitution());

				relVel *= -e;


				// Calculate impulse scalar.
				float impulseScalar = (-(1 + e) * relVel) / (currentRB->getInvMass() + otherRB->getInvMass());

				// Apply impulse.
				vec2 impulse = impulseScalar * info.impactNormal;
				//currentRB->addForce(-impulse, ForceType::IMPULSE);
				//otherRB->addForce(impulse, ForceType::IMPULSE);

				currentRB->addForce(impulse, ForceType::IMPULSE);
				otherRB->addForce(-impulse, ForceType::IMPULSE);



				// Positional correction.
				const float percent = 0.2f;	// Usually 20% - 80%.
				const float slop = 0.01f;	// Usually 0.01 - 0.1.
				vec2 correction = std::max(info.penetrationDepth - slop, 0.0f) / (currentRB->getInvMass() + otherRB->getInvMass()) * percent * info.impactNormal;
				//vec2 correction = info.penetrationDepth / (currentRB->getInvMass() + otherRB->getInvMass()) * percent * info.impactNormal;
				Transform* currentTransform = currentCollider->transform;
				Transform* otherTransform = otherCollider->transform;
				if (!currentRB->getIsKinematic())
				{
					//currentTransform->setWorldPosition(currentTransform->getWorldPosition() - vec3(currentRB->getInvMass() * correction));
					currentTransform->setLocalPosition(currentTransform->getLocalPosition() - vec3(currentRB->getInvMass() * correction));
				}
				if (!otherRB->getIsKinematic())
				{
					//otherTransform->setWorldPosition(otherTransform->getWorldPosition() + vec3(otherRB->getInvMass() * correction));
					otherTransform->setLocalPosition(otherTransform->getLocalPosition() + vec3(otherRB->getInvMass() * correction));
				}



				// Call any assigned collision callbacks.
				if (currentCollider->onCollisionEnter)
				{
					info.collider = currentCollider;
					info.otherCollider = otherCollider;

					currentCollider->onCollisionEnter(info);
				}

				if (otherCollider->onCollisionEnter)
				{
					info.collider = otherCollider;
					info.otherCollider = currentCollider;
					info.impactNormal = -info.impactNormal;

					otherCollider->onCollisionEnter(info);
				}
			}
		}
	}
	// Collision has occured for multiple frames consecutively.
	else
	{
		// Current collider is a trigger.
		if (currentCollider->getIsTrigger())
		{
			if (currentCollider->onTriggerStay)
			{
				currentCollider->onTriggerStay(otherCollider);
			}

			// Both colliders are triggers.
			if (otherCollider->getIsTrigger())
			{
				if (otherCollider->onTriggerStay)
				{
					otherCollider->onTriggerStay(currentCollider);
				}
			}
		}
		// Current collider is not a trigger.
		else
		{
			// Only the other collider is a trigger.
			if (otherCollider->getIsTrigger())
			{
				if (otherCollider->onTriggerStay)
				{
					otherCollider->onTriggerStay(currentCollider);
				}
			}
			// Both colliders are not triggers.
			else
			{
				//// Both objects must have rigidbodies in order to collide.
				//if (!currentCollider->getRigidbody() || !otherCollider->getRigidbody())
				//	return;


				// Calculate impulse resolution force.
				Rigidbody2D* currentRB = currentCollider->getRigidbody();
				Rigidbody2D* otherRB = otherCollider->getRigidbody();


				// Both objects must have rigidbodies in order to collide.
				if (!currentRB || !otherRB)
					return;


				// Calculate relative velocity from the other object to the current object.
				// Calculate relative velocity along the collision normal's direction.
				float relVel = (otherRB->getVelocity() - currentRB->getVelocity()).dot(info.impactNormal);

				// Do not resolve if the velocities are separating.
				if (relVel > 0.0f)
				{
					//continue;
					return;
				}

				// Use lowest restitution(elasticity or bounciness) of the two objects
				float e = std::min(currentRB->getRestitution(), otherRB->getRestitution());

				relVel *= -e;


				// Calculate impulse scalar.
				float impulseScalar = (-(1 + e) * relVel) / (currentRB->getInvMass() + otherRB->getInvMass());

				// Apply impulse.
				vec2 impulse = impulseScalar * info.impactNormal;
				//currentRB->addForce(-impulse, ForceType::IMPULSE);
				//otherRB->addForce(impulse, ForceType::IMPULSE);

				currentRB->addForce(impulse, ForceType::IMPULSE);
				otherRB->addForce(-impulse, ForceType::IMPULSE);



				// Positional correction.
				const float percent = 0.2f;	// Usually 20% - 80%.
				const float slop = 0.01f;	// Usually 0.01 - 0.1.
				vec2 correction = std::max(info.penetrationDepth - slop, 0.0f) / (currentRB->getInvMass() + otherRB->getInvMass()) * percent * info.impactNormal;
				//vec2 correction = info.penetrationDepth / (currentRB->getInvMass() + otherRB->getInvMass()) * percent * info.impactNormal;
				Transform* currentTransform = currentCollider->transform;
				Transform* otherTransform = otherCollider->transform;
				if (!currentRB->getIsKinematic())
				{
					//currentTransform->setWorldPosition(currentTransform->getWorldPosition() - vec3(currentRB->getInvMass() * correction));
					currentTransform->setLocalPosition(currentTransform->getLocalPosition() - vec3(currentRB->getInvMass() * correction));
				}
				if (!otherRB->getIsKinematic())
				{
					//otherTransform->setWorldPosition(otherTransform->getWorldPosition() + vec3(otherRB->getInvMass() * correction));
					otherTransform->setLocalPosition(otherTransform->getLocalPosition() + vec3(otherRB->getInvMass() * correction));
				}


				// Call any assigned collision callbacks.
				if (currentCollider->onCollisionStay)
				{
					info.collider = currentCollider;
					info.otherCollider = otherCollider;

					currentCollider->onCollisionStay(info);
				}

				if (otherCollider->onCollisionStay)
				{
					info.collider = otherCollider;
					info.otherCollider = currentCollider;
					info.impactNormal = -info.impactNormal;

					otherCollider->onCollisionStay(info);
				}
			}
		}
	}
}

void Physics2DSystem::verifyCollisions(Collider2D* colliderOne, Collider2D* colliderTwo)
{
	// Current collider is a trigger.
	if (colliderOne->getIsTrigger())
	{
		if (colliderOne->onTriggerExit)
		{
			colliderOne->onTriggerExit(colliderTwo);
		}

		// Other collider is a trigger.
		if (colliderTwo->getIsTrigger())
		{
			if (colliderTwo->onTriggerExit)
			{
				colliderTwo->onTriggerExit(colliderOne);
			}
		}
	}
	// Current collider is not a trigger.
	else
	{
		// Only the other collider is a trigger.
		if (colliderTwo->getIsTrigger())
		{
			if (colliderTwo->onTriggerExit)
			{
				colliderTwo->onTriggerExit(colliderOne);
			}
		}
		// Both colliders are not triggers.
		else
		{
			// Both objects must have rigidbodies in order to collide.
			if (!colliderOne->getRigidbody() || !colliderTwo->getRigidbody())
				return;


			CollisionInfo2D info;
			info.collider = colliderOne;
			info.otherCollider = colliderTwo;
			info.impactNormal = vec2::up;
			info.penetrationDepth = 0.0f;


			if (colliderOne->onCollisionExit)
			{
				colliderOne->onCollisionExit(info);
			}

			if (colliderTwo->onCollisionExit)
			{
				colliderTwo->onCollisionExit(info);
			}
		}
	}
}







bool Collision2D::operator==(const Collision2D& rhs)
{
	return (*colliderOne == *(rhs.colliderOne)) && (*colliderTwo == *(rhs.colliderTwo));
}

size_t Collision2D::operator()(const Collision2D* collision) const noexcept
{
		size_t eidOne = colliderOne->transform->getEid();
		size_t eidTwo = colliderTwo->transform->getEid();

		// eidOne and eidTwo are unsigned and are therefore guaranteed to be >= 0.
		// Szudzik's pairing function. http://szudzik.com/ElegantPairing.pdf
		// Uniquely maps two N-bit numbers to a 2N-bit number.
		// Unsigned integer overflow will result in the number wrapping starting at 0. Should still have an extremely low chance of resulting in a hash collision.
		size_t hash = eidOne >= eidTwo ? (eidOne * eidOne) + eidOne + eidTwo : eidOne + (eidTwo * eidTwo);

		return hash;
}

size_t KeyHasher::operator()(const Collision2D* collision) const noexcept
{
	size_t eidOne = collision->colliderOne->transform->getEid();
	size_t eidTwo = collision->colliderTwo->transform->getEid();

	// eidOne and eidTwo are unsigned and are therefore guaranteed to be >= 0.
	// Szudzik's pairing function. http://szudzik.com/ElegantPairing.pdf
	// Uniquely maps two N-bit numbers to a 2N-bit number.
	// Unsigned integer overflow will result in the number wrapping starting at 0. Should still have an extremely low chance of resulting in a hash collision.
	size_t hash = eidOne >= eidTwo ? (eidOne * eidOne) + eidOne + eidTwo : eidOne + (eidTwo * eidTwo);

	return hash;
}

bool KeyEquals::operator()(const Collision2D* lhs, const Collision2D* rhs) const
{
	return (*(lhs->colliderOne) == *(rhs->colliderOne)) && (*(lhs->colliderTwo) == *(rhs->colliderTwo));
}
