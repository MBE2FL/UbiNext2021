#pragma once
#include "stdafx.h"
#include "System.h"

#include <unordered_set>


class Collider2D;
struct CollisionInfo2D;


struct Collision2D
{
	//Collision2D(Collision2D&& other) noexcept
	//{
	//	colliderOne = std::move(other.colliderOne);
	//	colliderTwo = std::move(other.colliderTwo);
	//}

	Collider2D* colliderOne;
	Collider2D* colliderTwo;
	
	bool operator==(const Collision2D& rhs);

	//size_t operator()(const Collision2D& collision) const noexcept
	//{
	//	size_t eidOne = colliderOne->getTransform()->getEid();
	//	size_t eidTwo = colliderTwo->getTransform()->getEid();

	//	// eidOne and eidTwo are unsigned and are therefore guaranteed to be >= 0.
	//	// Szudzik's pairing function. http://szudzik.com/ElegantPairing.pdf
	//	// Uniquely maps two N-bit numbers to a 2N-bit number.
	//	// Unsigned integer overflow will result in the number wrapping starting at 0. Should still have an extremely low chance of resulting in a hash collision.
	//	size_t hash = eidOne >= eidTwo ? (eidOne * eidOne) + eidOne + eidTwo : eidOne + (eidTwo * eidTwo);

	//	return hash;
	//}

	size_t operator()(const Collision2D* collision) const noexcept;
};

namespace std
{
	template<>
	struct std::hash<Collision2D>
	{
		size_t operator()(const Collision2D* collision) const noexcept
		{
			return collision->operator()(collision);
		}
	};
}

struct KeyHasher
{
	size_t operator()(const Collision2D* collision) const noexcept;
};

struct KeyEquals
{
	bool operator()(const Collision2D* lhs, const Collision2D* rhs) const;
};



class Physics2DSystem : public System
{
public:
	Physics2DSystem();
	~Physics2DSystem();


	void update(float deltaTime);
	void debugDraw() const;


private:
	std::unordered_set<Collision2D*, std::hash<Collision2D>, KeyEquals> _collisions;
	std::unordered_set<Collision2D*, std::hash<Collision2D>, KeyEquals> _prevFrameCollisions;


	void resolveCollision(Collider2D* currentCollider, Collider2D* otherCollider, CollisionInfo2D& info);
	void verifyCollisions(Collider2D* colliderOne, Collider2D* colliderTwo);
};
