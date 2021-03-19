#include "stdafx.h"
#include "Component.h"

Component::Component(GameObject* _gameObject, Transform* _transform)
	: gameObject(_gameObject), transform(_transform)
{
}

Component::Component(const Component& other)
	: gameObject(other.gameObject), transform(other.transform)
{
}

Component::Component(Component&& other) noexcept
	: gameObject(std::move(other.gameObject)), transform(std::move(other.transform))
{
}

Component::~Component()
{
}
