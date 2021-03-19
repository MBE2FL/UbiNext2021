#pragma once


class GameObject;
class Transform;


class Component
{
public:
	Component() = delete;
	Component(GameObject* _gameObject, Transform* _transform);
	Component(const Component& other);
	Component(Component&& other) noexcept;
	virtual ~Component();



	GameObject* gameObject;
	Transform* transform;
};