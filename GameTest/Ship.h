#pragma once
#include "GameObject.h"




class Ship : public GameObject
{
public:
	Ship();
	~Ship();


	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void fixedUpdate(float fixedDeltaTime) override;


private:
};