#pragma once
#include "GameObject.h"


class Sprite;


class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();


	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void fixedUpdate(float fixedDeltaTime) override;
	virtual void reset() override;


	inline Sprite* getSprite() const
	{
		return _sprite;
	}

	void applyDamage(size_t amount);


private:
	Sprite* _sprite;
	size_t _health = 100.0f;
};