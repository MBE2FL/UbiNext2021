#include "stdafx.h"
#include "ObjectPlacement.h"
#include "Sprite.h"
#include "Transform.h"
#include "App/app.h"
#include "Factory.h"
#include "Map.h"



ObjectPlacement::ObjectPlacement()
	: GameObject(), _targetObject(nullptr)
{
	_map = Map::getMap();

	_sprite = addComponent<Sprite>();

	onMouseClick.emplace_back(std::bind(&ObjectPlacement::placeObject, this));


	_child = Factory::getInstance()->create<GameObject>();
	transform->addChild(_child->transform);
	_childSprite = _child->addComponent<Sprite>();
	vec3 pos = _child->transform->getWorldPosition();
	pos.z = -10.0f;
	_childSprite->transform->setWorldPosition(pos);
}

ObjectPlacement::~ObjectPlacement()
{
}

void ObjectPlacement::start()
{
}

void ObjectPlacement::update(float deltaTime)
{
	vec3 mousePos;
	App::GetMousePos(mousePos.x, mousePos.y);


	transform->setWorldPosition(mousePos);


	mousePos.x /= 64.0f;
	mousePos.x = std::floorf(mousePos.x);
	mousePos.x *= 64.0f;

	mousePos.y /= 64.0f;
	mousePos.y = std::floorf(mousePos.y);
	mousePos.y *= 64.0f;

	_child->transform->setWorldPosition(mousePos);
}

void ObjectPlacement::fixedUpdate(float fixedDeltaTime)
{
}

void ObjectPlacement::setObject(GameObject* object, Sprite* sprite)
{
	_targetObject = object;
	transform->setScale(_targetObject->transform->getScale());
	_sprite->setTexture(sprite->getTexFileName(), sprite->getNumColumns(), sprite->getNumRows());
	_sprite->SetFrame(sprite->GetFrame());


	//_child->transform->setScale(transform->getScale());
	_childSprite->setTexture(sprite->getTexFileName(), sprite->getNumColumns(), sprite->getNumRows());
	_childSprite->SetFrame(sprite->GetFrame());
	_childSprite->SetColor(0.6f, 0.6f, 1.0f, 0.5f);
}

void ObjectPlacement::placeObject()
{
	// Position to place new object.
	vec3 pos = _child->transform->getWorldPosition();
	pos.z = _targetObject->transform->getWorldPosition().z;


	// Check if the tile is already occupied.
	if (!_map->isTileOccupied(pos))
	{
		_map->setIsTileOccupied(true, pos);

		// Set the position of the new object.
		_targetObject->transform->setWorldPosition(pos);
		_targetObject->setActive(true);


		// TO-DO Remove object and it's components.
		setActive(false);
	}
}
