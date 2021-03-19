#pragma once
#include "stdafx.h"


class Entity;


class EntityManager
{
public:
	EntityManager();
	~EntityManager();


	/// <summary>
	/// Creates an entity.
	/// </summary>
	/// <returns>The newly created entity.</returns>
	Entity* createEntity();
	/// <summary>
	/// Destroys the specified entity.
	/// </summary>
	/// <param name="entity">The entity to destroy.</param>
	void destroyEntity(Entity* entity);


	static EntityManager* getInstance();


private:
	std::unordered_map<size_t, Entity*> _entityRegistry;
	size_t _nextEID = 0;


	static EntityManager* _instance;
};