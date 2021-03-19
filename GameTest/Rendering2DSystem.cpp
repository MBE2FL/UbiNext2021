#include "stdafx.h"
#include "Rendering2DSystem.h"
#include "Sprite.h"
#include "ComponentManager.h"
#include "GameObject.h"



Rendering2DSystem::Rendering2DSystem()
{
}

Rendering2DSystem::~Rendering2DSystem()
{
}

void Rendering2DSystem::draw()
{
	ComponentManager* compManager = ComponentManager::getInstance();

	ComponentArray<Sprite>& spriteArray = compManager->getAllComponentsOfType<Sprite>();


	for (Sprite* sprite : spriteArray)
	{
		if (sprite->gameObject->getIsActive())
		{
			sprite->Draw();
		}
	}
}
