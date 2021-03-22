#include "stdafx.h"
#include "BulletCannon.h"
#include "Transform.h"
#include "Collider2D.h"
#include "Tower.h"
#include "Enemy.h"
#include "MathUtils.h"
#include <exception>
#include "ObjectPool.h"
#include "Bullet.h"
#include "Rigidbody2D.h"



BulletCannon::BulletCannon(GameObject* gameObject, Transform* transform)
	: Component(gameObject, transform)
{
	// Only allow attachment to a tower game object.
	if (transform->getTag() != "Tower")
	{
		throw std::runtime_error("Cannot attach a bullet canon to a non-tower game object!");
	}

	// Setup callbacks for when enemies come in range of this canon's tower.
	Tower* tower = static_cast<Tower*>(gameObject);
	tower->onEnterRadius = std::bind(&BulletCannon::onEnterRadius, this, std::placeholders::_1);
	tower->onExitRadius = std::bind(&BulletCannon::onExitRadius, this, std::placeholders::_1);


	_bulletPool = new ObjectPool<Bullet>(30);
}

BulletCannon::~BulletCannon()
{
}

void BulletCannon::update(float deltaTime)
{
	_reloadTimer += deltaTime;
}

void BulletCannon::shoot()
{
	if (_reloadTimer >= _reloadTime)
	{
		// Shoot the maximum amount of bullets allowed per frame.
		for (size_t shotsFired = 0; shotsFired < _fireRate; ++shotsFired)
		{

			size_t numEnemies = _enemiesInRange.size();
			if (numEnemies > 0)
			{
				// Find an enemy to shoot at.
				size_t randomIndex = MathUtils::randInRange<size_t>(0, numEnemies - 1);

				Enemy* enemy = _enemiesInRange[randomIndex];


				// Shoot a bullet in that enemy's direction.
				vec3 dir = enemy->transform->getWorldPosition() - transform->getWorldPosition();
				dir.normalize();

				Bullet* bullet = _bulletPool->getObject();
				vec3 pos = transform->getWorldPosition();
				pos.z = -20.0f;
				bullet->transform->setWorldPosition(pos);

				bullet->getComponent<Rigidbody2D>()->addForce(vec2(dir) * 2500.0f, ForceType::IMPULSE);
			}
		}


		// Reset reload timer.
		_reloadTimer = 0.0f;
	}
}

void BulletCannon::onEnterRadius(Collider2D* collider)
{
	// Add the enemy to the list of enemies in range of this cannon.
	if (collider->transform->getTag() == "Enemy")
	{
		_enemiesInRange.emplace_back(static_cast<Enemy*>(collider->gameObject));
	}
}

void BulletCannon::onExitRadius(Collider2D* collider)
{
	// Remove the enemy from the list of enemies in range of this cannon.
	if (collider->transform->getTag() == "Enemy")
	{
		std::vector<Enemy*>::iterator it;
		for (it = _enemiesInRange.begin(); it != _enemiesInRange.end(); ++it)
		{
			if (*it == collider->gameObject)
			{
				_enemiesInRange.erase(it);
				return;
			}
		}
	}
}
