#include "stdafx.h"
#include "ComponentManager.h"


ComponentManager* ComponentManager::_instance = nullptr;


void ComponentManager::onEntityDestroyed(Entity* entity)
{
	// Remove the entity and all of it's components from all of the component arrays.
	for (auto const& pair : _componentArrays)
	{
		pair.second->onEntityDestroyed(entity);
	}
}

ComponentManager* ComponentManager::getInstance()
{
	if (!_instance)
	{
		_instance = new ComponentManager();
	}

	return _instance;
}
