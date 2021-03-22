#pragma once
#include "System.h"


class GameObject;



class Rendering2DSystem : public System
{
public:
	Rendering2DSystem();
	~Rendering2DSystem();


	void draw();


private:
	GameObject* _selectedObject;
};