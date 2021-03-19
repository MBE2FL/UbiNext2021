#pragma once
#include "Collider2D.h"
#include "vec2.h"




class BoxCollider2D : public Collider2D
{
public:
	BoxCollider2D() = delete;
	BoxCollider2D(GameObject* gameObject, Transform* transform, const Bounds2D& bounds);
	BoxCollider2D(GameObject* gameObject, Transform* transform, const vec2& centre, const vec2& size);
	~BoxCollider2D() = default;

	virtual void debugDraw() const override;

	virtual void updateBounds() override;

	virtual bool checkForCollision(Collider2D* other, CollisionInfo2D& info) override;
	virtual bool checkForCollision(BoxCollider2D* other, CollisionInfo2D& info) override;
	virtual bool checkForCollision(CircleCollider2D* other, CollisionInfo2D& info) override;



	Bounds2D _bounds;

	vec2 _vertices[4];
};