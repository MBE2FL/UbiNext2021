#pragma once
#include "Component.h"
#include "GameObject.h"
//#include "Bullet.h"
//#include "ObjectPool.h"

class Enemy;
class Collider2D;
class Bullet;
template<typename T> class ObjectPool;



class BulletCannon : public Component
{
public:
	BulletCannon(GameObject* gameObject, Transform* transform);
	~BulletCannon();


	static inline const char* getBaseTypeName()
	{
		static const char* baseTypeName = "BulletCannon";
		return baseTypeName;
	}


	void update(float deltaTime);
	void shoot();



private:
	float _reloadTime = 0.8f;
	float _reloadTimer = 0.0f;
	size_t _fireRate = 1;

	std::vector<Enemy*> _enemiesInRange;

	ObjectPool<Bullet>* _bulletPool;


	void onEnterRadius(Collider2D* collider);
	void onExitRadius(Collider2D* collider);
};