#include "stdafx.h"
#include "Character.h"
#include "ComponentManager.h"
#include "Transform.h"
#include "BoxCollider2D.h"
#include "Rigidbody2D.h"
#include "Sprite.h"
#include "App/app.h"



enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};



Character::Character()
	: GameObject()
{
	_transform->setLocalPosition(vec3(500.0f, 300.0f, 0.0f));

	//CircleCollider2D* collider = new CircleCollider2D(transform, vec2(transform->getWorldPosition()), 50.0f);
	BoxCollider2D* collider = new BoxCollider2D(this, _transform, vec2(0.0f, 0.0f), vec2(100.0f, 100.0f));
	//collider->onCollisionEnter = [](const CollisionInfo2D& info) { info.otherCollider->getTransform()->getName(); system("pause"); };
	//collider->onCollisionExit = [](const CollisionInfo2D& info) { info.otherCollider->getTransform()->getName(); system("pause"); };

	_rigidbody = new Rigidbody2D(this, _transform, 10.0f, 1.0f, 0.0f, false);
	collider->attachRigidbody(_rigidbody);
	//rbOne->setIsKinematic(true);
	//_rigidbody->addForce(vec2(0.0f, 1000.0f), ForceType::IMPULSE);

	_sprite = new Sprite(this, _transform, ".\\TestData\\Test.bmp", 8, 4);
	float speed = 1.0f / 15.0f;
	_sprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	_sprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	_sprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	_sprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });


	ComponentManager* compManager = ComponentManager::getInstance();
	compManager->addComponent(_entity, _transform);
	compManager->addComponent<Collider2D>(_entity, collider);
	compManager->addComponent<Rigidbody2D>(_entity, _rigidbody);
	compManager->addComponent<Sprite>(_entity, _sprite);
}

Character::~Character()
{
}

void Character::start()
{
}

void Character::update(float deltaTime)
{
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		_sprite->SetAnimation(ANIM_RIGHT);

		vec3 pos = _transform->getLocalPosition();
		pos.x += 1.0f;
		_transform->setLocalPosition(pos);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		_sprite->SetAnimation(ANIM_RIGHT);

		vec3 pos = _transform->getLocalPosition();
		pos.x -= 1.0f;
		_transform->setLocalPosition(pos);
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		_sprite->SetAnimation(ANIM_RIGHT);

		vec3 pos = _transform->getLocalPosition();
		pos.y += 1.0f;
		_transform->setLocalPosition(pos);
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		_sprite->SetAnimation(ANIM_RIGHT);

		vec3 pos = _transform->getLocalPosition();
		pos.y -= 1.0f;
		_transform->setLocalPosition(pos);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		vec3 scale = _transform->getScale();
		scale.x += 0.1f;
		scale.y += 0.1f;
		_transform->setScale(scale);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		vec3 scale = _transform->getScale();
		scale.x -= 0.1f;
		scale.y -= 0.1f;
		_transform->setScale(scale);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		vec3 rot = _transform->getLocalRotation();
		rot.z += 0.1f;
		_transform->setLocalRotation(rot);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		vec3 rot = _transform->getLocalRotation();
		rot.z -= 0.1f;
		_transform->setLocalRotation(rot);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		_sprite->SetAnimation(-1);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		vec2 vertex = _sprite->GetVertex(0);
		vertex.x += 5.0f;
		vertex.y += 5.0f;
		_sprite->SetVertex(0, vertex);
	}
}

void Character::fixedUpdate(float fixedDeltaTime)
{
}
