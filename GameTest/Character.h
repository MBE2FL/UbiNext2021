#pragma once
#include "GameObject.h"


class Rigidbody2D;
class Sprite;


class Character : public GameObject
{
public:
	Character();
	~Character();


	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void fixedUpdate(float fixedDeltaTime) override;


private:
	Rigidbody2D* _rigidbody;
	Sprite* _sprite;
};