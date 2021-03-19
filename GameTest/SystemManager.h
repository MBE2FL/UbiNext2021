#pragma once
#include "stdafx.h"


class System;
class Entity;


class SystemManager
{
public:
	SystemManager();
	~SystemManager();


	/// <summary>
	/// Registers a system with this system manager.
	/// </summary>
	/// <typeparam name="T">System Type</typeparam>
	/// <returns>The newly registered system.</returns>
	template<typename T>
	T* registerSystem();

	/// <summary>
	/// Unregisters a system from this system manager.
	/// </summary>
	/// <typeparam name="T">System Type</typeparam>
	template<typename T>
	void unregisterSystem();

	/// <summary>
	/// Callback for when an entity is destroyed.
	/// </summary>
	/// <param name="entity">The entity that was destroyed.</param>
	void onEntityDestroyed(const Entity& entity);


	static SystemManager* getInstance();


private:
	std::unordered_map<const char*, System*> _systems;

	static SystemManager* _instance;
};

template<typename T>
inline T* SystemManager::registerSystem()
{
	const char* typeName = typeid(T).name();

	std::unordered_map<const char*, System*>::iterator it = _systems.find(typeName);

	// System has not already been registered.
	if (it == _systems.end())
	{
		T* newSystem = new T();
		_systems[typeName] = newSystem;
		return newSystem;
	}
	// System has already been registered.
	else
	{
		return static_cast<T*>(it->second);
	}
}

template<typename T>
inline void SystemManager::unregisterSystem()
{
	const char* typeName = typeid(T).name();

	std::unordered_map<const char*, System*>::iterator it = _systems.find(typeName);

	// System has not been registered.
	if (it == _systems.end())
	{
		return;
	}
	// System has been registered.
	else
	{
		_systems.erase(it);
	}
}
