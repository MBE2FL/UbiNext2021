#include "stdafx.h"
#include "Path.h"
#include "Sprite.h"



Path::Path()
	: GameObject()
{
	_sprite = addComponent<Sprite>(".\\TestData\\Path.bmp", 1, 1);
}

Path::~Path()
{
}

void Path::start()
{
}

void Path::update(float deltaTime)
{
}

void Path::fixedUpdate(float fixedDeltaTime)
{
}
