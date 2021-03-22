#pragma once
#include "GameObject.h"

class Sprite;


class Path : public GameObject
{
public:
	Path();
	~Path();


	virtual void start() override;

	virtual void update(float deltaTime) override;

	virtual void fixedUpdate(float fixedDeltaTime) override;


	inline Sprite* getSprite() const
	{
		return _sprite;
	}

	inline bool getIsOccupied() const
	{
		return true;
	}


private:
	Sprite* _sprite;
};