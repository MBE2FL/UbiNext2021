#pragma once
#include "ComponentManager.h"
#include <functional>


class Entity;
class Transform;
class GameObject;


typedef std::function<void()> OnMouseClickSignature;
typedef std::function<void(GameObject*)> OnRecycleSignature;



class GameObject
{
public:
	GameObject();
	GameObject(const GameObject& other) = delete;
	virtual ~GameObject();


	virtual void start() {};
	virtual void update(float deltaTime) {};
	virtual void fixedUpdate(float fixedDeltaTime) {};
	virtual void reset() {};


	bool getIsActive() const;
	bool getIsActiveSelf() const;
	void setActive(bool isActive);


	template<typename T, typename... Args>
	T* addComponent(Args&&... args);
	template<typename T>
	void removeComponent();
	template<typename T>
	T* getComponent() const;


	Transform* transform;

	// Callbacks
	std::vector<OnMouseClickSignature> onMouseClick;
	OnRecycleSignature onRecycle;


protected:
	Entity* _entity;
	bool _isActive;
	bool _isActiveSelf;
};



template<typename T, typename... Args>
inline T* GameObject::addComponent(Args&&... args)
{
	return ComponentManager::getInstance()->addComponent<T>(_entity, this, transform, std::forward<Args>(args)...);
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