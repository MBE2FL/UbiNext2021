#include "stdafx.h"
#include "Ground.h"
#include "Sprite.h"

Ground::Ground()
	: GameObject()
{
	_sprite = addComponent<Sprite>(".\\TestData\\Ground.bmp", 1, 1);
}

Ground::~Ground()
{
}
