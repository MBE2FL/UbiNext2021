#pragma once
#include "GameObject.h"


class Sprite;
class Map;



class ObjectPlacement : public GameObject
{
public:
	ObjectPlacement();
	~ObjectPlacement();


	virtual void start() override;

	virtual void update(float deltaTime) override;

	virtual void fixedUpdate(float fixedDeltaTime) override;


	void setObject(GameObject* object, Sprite* sprite);

	void placeObject();


private:
	Map* _map;
	Sprite* _sprite;
	Sprite* _childSprite;
	GameObject* _child;
	GameObject* _targetObject;
};