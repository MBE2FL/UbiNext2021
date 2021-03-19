#include "stdafx.h"
#include "GameObject.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "Transform.h"




GameObject::GameObject()
	: _isActive(true), _isActiveSelf(true)
{
	// Create an entity.
	EntityManager* entManager = EntityManager::getInstance();
	_entity = entManager->createEntity();
	
	// Assign a transform component.
	_transform = new Transform(this, _entity->getEid(), "GameObject" + std::to_string(_entity->getEid()));

	ComponentManager* compManager = ComponentManager::getInstance();
	compManager->addComponent(_entity, _transform);
}

GameObject::~GameObject()
{
}

bool GameObject::getIsActive() const
{
    return _isActive;
}

bool GameObject::getIsActiveSelf() const
{
	return _isActiveSelf;
}

void GameObject::setActive(bool isActive)
{
	// This object has a parent.
	if (_transform->getParent())
	{
		_isActiveSelf = isActive;
	}
	// This object has no parent.
	else
	{
		_isActive = isActive;
		_isActiveSelf = isActive;
	}
}
