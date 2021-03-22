#include "stdafx.h"
#include "TransformSystem.h"
#include "ComponentManager.h"
#include "Transform.h"



TransformSystem::TransformSystem()
{
}

TransformSystem::~TransformSystem()
{
}

void TransformSystem::update(float deltaTime)
{
	//ComponentManager* compManager = ComponentManager::getInstance();

	//ComponentArray<Transform>& transformArray = compManager->getAllComponentsOfType<Transform>();

	//for (Transform* transform : transformArray)
	//{
	//	if (transform->isRoot())
	//	{
	//		transform->update(deltaTime);
	//	}
	//}
}
