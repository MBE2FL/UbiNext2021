#pragma once
#include "stdafx.h"
#include "ComponentArray.h"
#include <iostream>


class Entity;


class ComponentManager
{
public:


	//void registerComponent(const Entity& entity);
	/// <summary>
	/// Adds a component to an entity.
	/// </summary>
	/// <typeparam name="T">Component Type</typeparam>
	/// <param name="entity">The entity to add to.</param>
	/// <param name="component">The component to add.</param>
	template<typename T>
	void addComponent(Entity* entity, T* component);

	/// <summary>
	/// Adds a component to an entity.
	/// </summary>
	/// <typeparam name="T">Component Type</typeparam>
	/// <typeparam name="...Args">The constructor parameters for the new component.</typeparam>
	/// <param name="entity">The entity to add to.</param>
	/// <param name="...args">The constructor parameters for the new component.</param>
	/// <returns>The newly added component.</returns>
	template<typename T, typename... Args>
	T* addComponent(Entity* entity, Args&&... args);

	/// <summary>
	/// Removes a component from an entity.
	/// </summary>
	/// <typeparam name="T">Component Type</typeparam>
	/// <param name="entity">The entity to remove from.</param>
	template<typename T>
	void removeComponent(Entity* entity);

	/// <summary>
	/// Gets a component from an entity.
	/// </summary>
	/// <typeparam name="T">Component Type</typeparam>
	/// <param name="entity">The entity attached to the component.</param>
	/// <returns>The component attached to the entity, or nullptr if no such component exists.</returns>
	template<typename T>
	T* getComponent(Entity* entity) const;

	/// <summary>
	/// </summary>
	/// <typeparam name="T">Component Type</typeparam>
	/// <returns>All components of the specified type.</returns>
	
	/// <summary>
	///	Gets an array of specified components.
	/// </summary>
	/// <typeparam name="T">Comonent Type</typeparam>
	/// <param name="outCompArray">The array of components, or nullptr.</param>
	/// <returns>True iff an array of specified components exists, false otherwise.</returns>
	template<typename T>
	bool getAllComponentsOfType(ComponentArray<T>** outCompArray) const;

	/// <summary>
	/// Callback for when an entity is destroyed.
	/// </summary>
	/// <param name="entity">The entity that was destroyed.</param>
	void onEntityDestroyed(Entity* entity);

	static ComponentManager* getInstance();

private:
	std::unordered_map<const char*, IComponentArray*> _componentArrays;

	static ComponentManager* _instance;

};



template<typename T>
inline void ComponentManager::addComponent(Entity* entity, T* component)
{
	const char* typeName = typeid(T).name();

	std::unordered_map<const char*, IComponentArray*>::iterator it = _componentArrays.find(typeName);

	// Check if the component type already exists.
	if (it != _componentArrays.end())
	{
		static_cast<ComponentArray<T>*>(it->second)->addComponent(entity, component);
	}
	// Add a component array for the new component type.
	else
	{
		ComponentArray<T>* compArray = new ComponentArray<T>();
		_componentArrays[typeName] = compArray;

		compArray->addComponent(entity, component);
	}
}

template<typename T, typename ...Args>
inline T* ComponentManager::addComponent(Entity* entity, Args &&... args)
{
	//const char* typeName = typeid(T).name();
	const char* typeName = T::getBaseTypeName();

	std::unordered_map<const char*, IComponentArray*>::iterator it = _componentArrays.find(typeName);

	// Check if the component type already exists.
	if (it != _componentArrays.end())
	{
		return static_cast<ComponentArray<T>*>(it->second)->addComponent(entity, std::forward<Args>(args)...);
	}
	// Add a component array for the new component type.
	else
	{
		ComponentArray<T>* compArray = new ComponentArray<T>();
		_componentArrays[typeName] = compArray;

		return compArray->addComponent(entity, std::forward<Args>(args)...);
	}
}

template<typename T>
inline void ComponentManager::removeComponent(Entity* entity)
{
	//const char* typeName = typeid(T).name();
	const char* typeName = T::getBaseTypeName();

	std::unordered_map<const char*, IComponentArray*>::iterator it = _componentArrays.find(typeName);

	// Check if the component type exists.
	if (it == _componentArrays.end())
	{
		std::cout << "Component type does not exist!" << std::endl;
		return;
	}
	// Remove the component from the entity.
	else
	{
		static_cast<ComponentArray<T>*>(it->second)->removeComponent(entity);	// TO-DO Delete old component.
	}
}

template<typename T>
inline T* ComponentManager::getComponent(Entity* entity) const
{
	//const char* typeName = typeid(T).name();
	const char* typeName = T::getBaseTypeName();

	std::unordered_map<const char*, IComponentArray*>::const_iterator it = _componentArrays.find(typeName);

	// Check if the component type exists.
	if (it == _componentArrays.cend())
	{
		std::cout << "Component type does not exist!" << std::endl;
		//return static_cast<ComponentArray<T>*>(it->second)->getComponent(entity);
		return nullptr;
	}
	// Retrieve the component from the entity.
	else
	{
		return static_cast<ComponentArray<T>*>(it->second)->getComponent(entity);
	}
}

template<typename T>
inline bool ComponentManager::getAllComponentsOfType(ComponentArray<T>** outCompArray) const
{
	//const char* typeName = typeid(T).name();
	const char* typeName = T::getBaseTypeName();

	std::unordered_map<const char*, IComponentArray*>::const_iterator it = _componentArrays.find(typeName);

	// Check if the component type exists.
	if (it == _componentArrays.cend())
	{
		std::cout << "Component type does not exist!" << std::endl;
		*outCompArray = nullptr;
		return false;
	}
	// Retrieve the component from the entity.
	else
	{
		//return static_cast<ComponentArray<T>&>(*it->second);
		*outCompArray = static_cast<ComponentArray<T>*>(it->second);
		return true;
	}
}
