#include "stdafx.h"
#include "Bullet.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "Transform.h"
#include "CircleCollider2D.h"
#include "Rigidbody2D.h"
#include "Sprite.h"
#include "App/app.h"
#include "Enemy.h"
#include "BoxCollider2D.h"



Bullet::Bullet()
	: GameObject()
{
	//transform->setLocalPosition(vec3(10.0f, 256.0f, 0.0f));

	//CircleCollider2D* collider = new CircleCollider2D(this, _transform, vec2(_transform->getWorldPosition()), 80.0f);
	//collider->onCollisionEnter = std::bind(&Bullet::onCollisionEnter, this, std::placeholders::_1);

	//Rigidbody2D* rb = new Rigidbody2D(this, _transform, 10.0f, 1.0f, 0.0f, false);
	//collider->attachRigidbody(rb);

	//Sprite* sprite = new Sprite(this, _transform, ".\\TestData\\Test.bmp", 8, 4);


	//ComponentManager* compManager = ComponentManager::getInstance();
	//compManager->addComponent<Collider2D>(_entity, collider);
	//compManager->addComponent<Rigidbody2D>(_entity, rb);
	//compManager->addComponent<Sprite>(_entity, sprite);



	//CircleCollider2D* collider = addComponent<CircleCollider2D>(vec2(transform->getWorldPosition()), 32.0f);
	BoxCollider2D* collider = addComponent<BoxCollider2D>(vec2(transform->getWorldPosition()), vec2(64.0f, 64.0f));
	collider->setIsTrigger(true);
	//collider->onCollisionEnter = std::bind(&Bullet::onCollisionEnter, this, std::placeholders::_1);
	collider->onTriggerEnter = std::bind(&Bullet::onTriggerEnter, this, std::placeholders::_1);

	Rigidbody2D* rigidbody = addComponent<Rigidbody2D>(1.0f, 1.0f, 0.0f, false);
	collider->attachRigidbody(rigidbody);
	//rigidbody->setIsKinematic(true);
	//_rigidbody->addForce(vec2(0.0f, 1000.0f), ForceType::IMPULSE);

	Sprite* sprite = addComponent<Sprite>(".\\TestData\\Bullet.bmp", 1, 1);
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
	if ((transform->getWorldPosition().x < 0.0f) && (transform->getWorldPosition().x > APP_VIRTUAL_WIDTH) &&
		(transform->getWorldPosition().y < 0.0f) && (transform->getWorldPosition().y > APP_VIRTUAL_HEIGHT))
	{
		// Call object pool recycle callback.
		if (onRecycle)
		{
			onRecycle(this);
		}
	}
}

void Bullet::fixedUpdate(float fixedDeltaTime)
{
}

void Bullet::reset()
{
	transform->setLocalPosition(vec3(10.0f, 450.0f, 0.0f));

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

void Bullet::onTriggerEnter(Collider2D* collider)
{
	if (collider->transform->getTag() == "Enemy")
	{
		static_cast<Enemy*>(collider->gameObject)->applyDamage(_damage);

		// Call object pool recycle callback.
		if (onRecycle)
		{
			onRecycle(this);
		}
	}
}
