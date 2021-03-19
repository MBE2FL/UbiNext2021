#include "stdafx.h"
#include "Bullet.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "Transform.h"
#include "CircleCollider2D.h"
#include "Rigidbody2D.h"
#include "Sprite.h"



Bullet::Bullet()
	: GameObject()
{
	_transform->setLocalPosition(vec3(10.0f, 256.0f, 0.0f));

	CircleCollider2D* collider = new CircleCollider2D(this, _transform, vec2(_transform->getWorldPosition()), 80.0f);
	collider->onCollisionEnter = std::bind(&Bullet::onCollisionEnter, this, std::placeholders::_1);

	Rigidbody2D* rb = new Rigidbody2D(this, _transform, 10.0f, 1.0f, 0.0f, false);
	collider->attachRigidbody(rb);

	Sprite* sprite = new Sprite(this, _transform, ".\\TestData\\Test.bmp", 8, 4);


	ComponentManager* compManager = ComponentManager::getInstance();
	compManager->addComponent(_entity, _transform);
	compManager->addComponent<Collider2D>(_entity, collider);
	compManager->addComponent<Rigidbody2D>(_entity, rb);
	compManager->addComponent<Sprite>(_entity, sprite);
}

Bullet::~Bullet()
{
	//delete _transform;	// TO-DO make ECS delete component.
}

void Bullet::start()
{
}

void Bullet::update(float deltaTime)
{
}

void Bullet::fixedUpdate(float fixedDeltaTime)
{
}

void Bullet::resetObject()
{
	_transform->setLocalPosition(vec3(10.0f, 450.0f, 0.0f));

	//CircleCollider2D* collider = new CircleCollider2D(_transform, vec2(_transform->getWorldPosition()), 80.0f);	// TO-DO make sure to update physics system.

	//Rigidbody2D* rb = new Rigidbody2D(_transform, 10.0f, 1.0f, 0.0f, false);	// TO-DO Expose and reset rb.
}

void Bullet::onCollisionEnter(const CollisionInfo2D&)
{
	// Call object pool recycle callback.
	if (onRecycle)
	{
		onRecycle(this);
	}
}
