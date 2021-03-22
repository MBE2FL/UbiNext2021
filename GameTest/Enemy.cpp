#include "stdafx.h"
#include "Enemy.h"
#include "Transform.h"
#include "Sprite.h"
#include "CircleCollider2D.h"
#include "BoxCollider2D.h"
#include "MathUtils.h"


Enemy::Enemy()
	: GameObject()
{
	transform->setTag("Enemy");
	vec3 pos = transform->getWorldPosition();
	pos.z = -20.0f;
	transform->setWorldPosition(pos);

	_sprite = addComponent<Sprite>(".\\TestData\\Enemy.bmp", 1, 1);
	//_sprite->setTexture(".\\TestData\\Ships.bmp", 2, 12);
	//_sprite->SetFrame(4);


	//CircleCollider2D* collider = addComponent<CircleCollider2D>(vec2(transform->getWorldPosition()), 80.0f);
	BoxCollider2D* collider = addComponent<BoxCollider2D>(vec2(transform->getWorldPosition()), vec2(64.0f, 64.0f));
	collider->setIsTrigger(true);
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
}

void Enemy::update(float deltaTime)
{
}

void Enemy::fixedUpdate(float fixedDeltaTime)
{
	vec3 currentPos = transform->getWorldPosition();
	vec3 targetPos = currentPos;
	targetPos.x = APP_VIRTUAL_WIDTH + 150.0f;
	vec3 pos = MathUtils::lerp<vec3>(currentPos, targetPos, 0.5f * fixedDeltaTime);
	transform->setWorldPosition(pos);

	// Recycle if off screen.
	if (pos.x >= APP_VIRTUAL_WIDTH + 150.0f)
	{
		if (onRecycle)
		{
			onRecycle(this);
		}
	}
}

void Enemy::reset()
{
	_health = 100;
}

void Enemy::applyDamage(size_t amount)
{
	_health -= amount;

	if (_health <= 0)
	{
		if (onRecycle)
		{
			onRecycle(this);
		}
	}
}
