#include "stdafx.h"
#include "SystemManager.h"

#include "System.h"


SystemManager* SystemManager::_instance = nullptr;


SystemManager::SystemManager()
{
}

SystemManager::~SystemManager()
{
	for (auto& pair : _systems)
	{
		delete pair.second;
	}

	_systems.clear();
}

void SystemManager::onEntityDestroyed(const Entity& entity)
{
}

SystemManager* SystemManager::getInstance()
{
	if (!_instance)
	{
		_instance = new SystemManager();
	}

	return _instance;
}
