#pragma once
#include "Collider2D.h"



class BoxCollider2D;




class CircleCollider2D : public Collider2D
{
public:
	CircleCollider2D() = delete;
	CircleCollider2D(GameObject* gameObject, Transform* transform, const vec2& _centre, const float _radius);
	~CircleCollider2D() = default;

	virtual void debugDraw() const override;

	virtual void updateBounds() override;

	virtual bool checkForCollision(Collider2D* other, CollisionInfo2D& info) override;
	virtual bool checkForCollision(BoxCollider2D* other, CollisionInfo2D& info) override;
	virtual bool checkForCollision(CircleCollider2D* other, CollisionInfo2D& info) override;



	vec2 centre;
	float radius;
	float scaledRadius;
};