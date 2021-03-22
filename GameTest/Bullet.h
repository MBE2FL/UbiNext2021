#pragma once
#include "GameObject.h"

#include <functional>


class Entity;
class Transform;
struct CollisionInfo2D;
class Collider2D;
class Bullet;


//typedef std::function<void(Bullet*)> OnRecycleSignature;
//typedef std::function<void(Bullet*)> OnObjectResetSignature;


class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void fixedUpdate(float fixedDeltaTime) override;
	virtual void reset() override;


	//OnRecycleSignature onRecycle;
	//OnObjectResetSignature onObjectReset;


private:
	size_t _damage = 50.0f;


	void onCollisionEnter(const CollisionInfo2D&);
	void onTriggerEnter(Collider2D* collider);
};