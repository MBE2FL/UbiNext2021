#include "stdafx.h"
#include "TowerSystem.h"
#include "BulletCannon.h"
#include "ComponentManager.h"
#include "GameObject.h"



TowerSystem::TowerSystem()
{
}

TowerSystem::~TowerSystem()
{
}

void TowerSystem::update(float deltaTime)
{
	ComponentManager* compManager = ComponentManager::getInstance();

	ComponentArray<BulletCannon>* bulletCannonArray = nullptr;
	if (!compManager->getAllComponentsOfType<BulletCannon>(&bulletCannonArray))
	{
		return;
	}


	for (BulletCannon* cannon : *bulletCannonArray)
	{
		if (!cannon->gameObject->getIsActive())
		{
			continue;
		}

		cannon->update(deltaTime);
		cannon->shoot();
	}
}
