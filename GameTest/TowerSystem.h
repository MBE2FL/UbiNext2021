#pragma once
#include "System.h"



class TowerSystem : public System
{
public:
	TowerSystem();
	~TowerSystem();


	void update(float deltaTime);
};