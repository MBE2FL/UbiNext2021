#pragma once
#include "ComponentManager.h"


class Entity;
class Transform;



class GameObject
{
public:
	GameObject();
	GameObject(const GameObject& other) = delete;
	virtual ~GameObject();


	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void fixedUpdate(float fixedDeltaTime) = 0;


	bool getIsActive() const;
	bool getIsActiveSelf() const;
	void setActive(bool isActive);


	template<typename T, typename... Args>
	T* addComponent(Args&&... args);
	template<typename T>
	void removeComponent();
	template<typename T>
	T* getComponent() const;


protected:
	Entity* _entity;
	Transform* _transform;
	bool _isActive;
	bool _isActiveSelf;
};



template<typename T, typename... Args>
inline T* GameObject::addComponent(Args&&... args)
{
	return ComponentManager::getInstance()->addComponent<T>(_entity, this, _transform, std::forward<Args>(args)...);
}

template<typename T>
inline void GameObject::removeComponent()
{
	ComponentManager::getInstance()->removeComponent<T>(_entity);
}

template<typename T>
inline T* GameObject::getComponent() const
{
	return ComponentManager::getInstance()->getComponent<T>(_entity);
}