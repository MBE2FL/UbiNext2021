#pragma once


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


protected:
	Entity* _entity;
	Transform* _transform;
	bool _isActive;
	bool _isActiveSelf;
};