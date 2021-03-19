#include "stdafx.h"
#include "EntityManager.h"
#include "Entity.h"


EntityManager* EntityManager::_instance = nullptr;


EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

Entity* EntityManager::createEntity()
{
	//std::unordered_map<size_t, Entity> _entityRegistry;
	//size_t _nextEID = 0;

	Entity* entity = new Entity(_nextEID);
	_entityRegistry[_nextEID] = entity;

	++_nextEID;

	return entity;
}

void EntityManager::destroyEntity(Entity* entity)
{
}

EntityManager* EntityManager::getInstance()
{
	if (!_instance)
	{
		_instance = new EntityManager();
	}

	return _instance;
}
