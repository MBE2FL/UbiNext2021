#include "stdafx.h"
#include "Tower.h"
#include "ComponentManager.h"
#include "Transform.h"
#include "CircleCollider2D.h"
#include "Sprite.h"




Tower::Tower()
	: GameObject()
{
	transform->setLocalPosition(vec3(200.0f, 50.0f, 0.0f));
	transform->setScale(vec3(0.5f, 0.5f, 0.1f));
	transform->setTag("Tower");


	//CircleCollider2D* collider = new CircleCollider2D(this, _transform, vec2(_transform->getWorldPosition()), 80.0f);

	//Sprite* sprite = new Sprite(this, _transform, ".\\TestData\\Ships.bmp", 2, 12);
	//sprite->SetFrame(2);


	//ComponentManager* compManager = ComponentManager::getInstance();
	//compManager->addComponent<Collider2D>(_entity, collider);
	//compManager->addComponent<Sprite>(_entity, sprite);



	CircleCollider2D* collider = addComponent<CircleCollider2D>(vec2(transform->getWorldPosition()), 300.0f);
	collider->setIsTrigger(true);
	collider->onTriggerEnter = std::bind(&Tower::onTriggerEnter, this, std::placeholders::_1);
	collider->onTriggerExit = std::bind(&Tower::onTriggerExit, this, std::placeholders::_1);

	_sprite = addComponent<Sprite>(".\\TestData\\Ships.bmp", 2, 12);
	_sprite->SetFrame(2);
}

Tower::~Tower()
{
}

void Tower::start()
{
}

void Tower::update(float deltaTime)
{
}

void Tower::fixedUpdate(float fixedDeltaTime)
{
}

void Tower::setTexture(const char* fileName, size_t numColumns, size_t numRows)
{
	_sprite->setTexture(fileName, numColumns, numRows);
}

void Tower::onTriggerEnter(Collider2D* other)
{
	if (onEnterRadius)
	{
		onEnterRadius(other);
	}
}

void Tower::onTriggerExit(Collider2D* other)
{
	if (onExitRadius)
	{
		onExitRadius(other);
	}
}
