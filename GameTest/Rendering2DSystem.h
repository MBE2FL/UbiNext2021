#pragma once
#include "System.h"



class Rendering2DSystem : public System
{
public:
	Rendering2DSystem();
	~Rendering2DSystem();


	void draw();
};