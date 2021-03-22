#include "stdafx.h"
#include "Ship.h"
#include "ComponentManager.h"
#include "Transform.h"
#include "CircleCollider2D.h"
#include "Rigidbody2D.h"
#include "Sprite.h"




Ship::Ship()
	: GameObject()
{
	transform->setLocalPosition(vec3(500.0f, 450.0f, 0.0f));
	transform->setScale(vec3(0.5f, 0.5f, 0.1f));

	////BoxCollider2D* colliderTwo = new BoxCollider2D(transformTwo, vec2(transformTwo->getWorldPosition()), vec2(100.0f, 100.0f));
	//CircleCollider2D* collider = new CircleCollider2D(this, _transform, vec2(_transform->getWorldPosition()), 80.0f);
	////BoxCollider2D* colliderTwo = new BoxCollider2D(transformTwo, vec2(transformTwo->getWorldPosition()), vec2(100.0f, 100.0f));

	//Rigidbody2D* rigidbody = new Rigidbody2D(this, _transform, 10.0f, 1.0f, .5f, false);
	//collider->attachRigidbody(rigidbody);

	//Sprite* sprite = new Sprite(this, _transform, ".\\TestData\\Ships.bmp", 2, 12);
	//sprite->SetFrame(2);


	//ComponentManager* compManager = ComponentManager::getInstance();
	//compManager->addComponent<Collider2D>(_entity, collider);
	//compManager->addComponent<Rigidbody2D>(_entity, rigidbody);
	//compManager->addComponent<Sprite>(_entity, sprite);



	CircleCollider2D* collider = addComponent<CircleCollider2D>(vec2(transform->getWorldPosition()), 80.0f);

	Rigidbody2D* rigidbody = addComponent<Rigidbody2D>(10.0f, 1.0f, .5f, false);
	collider->attachRigidbody(rigidbody);

	Sprite* sprite = addComponent<Sprite>(".\\TestData\\Ships.bmp", 2, 12);
	sprite->SetFrame(2);
}

Ship::~Ship()
{
}

void Ship::start()
{
}

void Ship::update(float deltaTime)
{
}

void Ship::fixedUpdate(float fixedDeltaTime)
{
}
