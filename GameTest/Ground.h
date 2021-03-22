#pragma once
#include "GameObject.h"


class Sprite;



class Ground : public GameObject
{
public:
	Ground();
	~Ground();

	inline Sprite* getSprite() const
	{
		return _sprite;
	}

	inline bool getIsOccupied() const
	{
		return _isOccupied;
	}

	inline void setIsOccupied(bool isOccupied)
	{
		_isOccupied = true;
	}

private:
	bool _isOccupied = false;
	Sprite* _sprite;
};