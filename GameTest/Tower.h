#pragma once
#include "GameObject.h"


class Sprite;


class Tower : public GameObject
{
public:
	Tower();
	~Tower();


	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void fixedUpdate(float fixedDeltaTime) override;

	void setTexture(const char* fileName);


//protected:
private:
	Sprite* _sprite;
	
};