#pragma once
#include "Component.h"



class BulletCanon : public Component
{
public:
	BulletCanon();
	~BulletCanon();


	void shoot();


private:
	float _reloadTime;
	size_t _bulletsPerShot;
};