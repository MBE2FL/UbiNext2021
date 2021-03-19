//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------



#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "MathUtils.h"

#include "EntityManager.h"
#include "Entity.h"

#include "ComponentManager.h"
#include "Transform.h"
#include "Rigidbody2D.h"
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"
#include "Sprite.h"

#include "SystemManager.h"
#include "TransformSystem.h"
#include "Physics2DSystem.h"
#include "Rendering2DSystem.h"

#include "ObjectPool.h"
#include "Bullet.h"
#include "Character.h"
#include "Ship.h"

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------
CSimpleSprite *testSprite;
CSimpleSprite *testSprite2;
enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};
//------------------------------------------------------------------------

//Transform* transform;
EntityManager* entManager;
ComponentManager* compManager;
SystemManager* sysManager;
TransformSystem* transformSystem;
Physics2DSystem* physics2DSystem;
Rendering2DSystem* rendering2DSystem;

//Entity* entity;
//Entity* entityTwo;
//Entity* entityThree;
//Entity* entityFour;
//
//Sprite* sprite;
//Sprite* spriteTwo;
Character* player;
Ship* ship;

ObjectPool<Bullet>* bulletPool;
std::vector<GameObject*> gameObjects;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	

	testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	//testSprite->SetPosition(400.0f, 400.0f);
	testSprite->SetPosition(512.0f, 250.0f);
	float speed = 1.0f / 15.0f;
	testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	testSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	testSprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
	testSprite->SetScale(2.0f);

	testSprite2 = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	testSprite2->SetPosition(400.0f, 400.0f);	
	testSprite2->SetFrame(2);
	testSprite2->SetScale(1.0f);
	//------------------------------------------------------------------------


	entManager = EntityManager::getInstance();
	compManager = ComponentManager::getInstance();
	sysManager = SystemManager::getInstance();


	transformSystem = sysManager->registerSystem<TransformSystem>();
	physics2DSystem = sysManager->registerSystem<Physics2DSystem>();


	//entity = entManager->createEntity();
	//entityTwo = entManager->createEntity();
	//entityThree = entManager->createEntity();
	//entityFour = entManager->createEntity();



	// ************ Object One ************
	player = new Character();
	gameObjects.push_back(player);
	//transform = new Transform(entity->getEid(), "Howdy");
	//transform->setLocalPosition(vec3(500.0f, 300.0f, 0.0f));
	//transform->setLocalRotation(vec3(0.0f, 0.0f, 0.0f));

	//BoxCollider2D* collider = new BoxCollider2D(transform, vec2(0.0f, 0.0f), vec2(100.0f, 100.0f));

	//Rigidbody2D* rbOne = new Rigidbody2D(transform, 10.0f, 1.0f, 0.0f, false);
	//collider->attachRigidbody(rbOne);
	////rbOne->setIsKinematic(true);
	//rbOne->addForce(vec2(0.0f, 1000.0f), ForceType::IMPULSE);

	//sprite = new Sprite(transform, ".\\TestData\\Test.bmp", 8, 4);
	//speed = 1.0f / 15.0f;
	//sprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	//sprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	//sprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	//sprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });



	// ************ Object Two ************
	ship = new Ship();
	gameObjects.push_back(ship);
	//Transform* transformTwo = new Transform(entityTwo->getEid(), "Doody");
	//transformTwo->setLocalPosition(vec3(500.0f, 450.0f, 0.0f));
	//transformTwo->setLocalRotation(vec3(0.0f, 0.0f, 0.0f));
	//transformTwo->setScale(vec3(0.5f, 0.5f, 0.1f));

	////BoxCollider2D* colliderTwo = new BoxCollider2D(transformTwo, vec2(transformTwo->getWorldPosition()), vec2(100.0f, 100.0f));
	//CircleCollider2D* colliderTwo = new CircleCollider2D(transformTwo, vec2(transformTwo->getWorldPosition()), 80.0f);
	////BoxCollider2D* colliderTwo = new BoxCollider2D(transformTwo, vec2(transformTwo->getWorldPosition()), vec2(100.0f, 100.0f));

	//Rigidbody2D* rbTwo = new Rigidbody2D(transformTwo, 10.0f, 1.0f, .5f, true);
	//colliderTwo->attachRigidbody(rbTwo);

	//spriteTwo = new Sprite(transformTwo, ".\\TestData\\Ships.bmp", 2, 12);
	//spriteTwo->SetFrame(2);



	// ************ Object Three ************
	//Transform* transformThree = new Transform(entityThree->getEid(), "TestThree");
	//transformThree->setLocalPosition(vec3(250.0f, 250.0f, 0.0f));
	//transformThree->setLocalRotation(vec3(0.0f, 0.0f, 0.0f));
	////transformThree->addChild(transform);

	//BoxCollider2D* colliderThree = new BoxCollider2D(transformThree, vec2(0.0f, 0.0f), vec2(50.0f, 80.0f));



	// ************ Object Four ************
	//Transform* transformFour = new Transform(entityFour->getEid(), "TestFour");
	//transformFour->setLocalPosition(vec3(700.0f, 400.0f, 0.0f));
	//transformFour->setLocalRotation(vec3(0.0f, 0.0f, 0.0f));
	//transformFour->setParent(transformThree);

	//BoxCollider2D* colliderFour = new BoxCollider2D(transformFour, vec2(0.0f, 0.0f), vec2(50.0f, 100.0f));


	
	//compManager->addComponent(entity, transform);
	//compManager->addComponent(entityTwo, transformTwo);
	//compManager->addComponent(entityThree, transformThree);
	//compManager->addComponent(entityFour, transformFour);

	//compManager->addComponent<Collider2D>(entity, collider);
	//compManager->addComponent<Collider2D>(entityTwo, colliderTwo);
	//compManager->addComponent<Collider2D>(entityThree, colliderThree);
	//compManager->addComponent<Collider2D>(entityFour, colliderFour);

	//compManager->addComponent<Rigidbody2D>(entity, rbOne);
	//compManager->addComponent<Rigidbody2D>(entityTwo, rbTwo);

	//compManager->addComponent<Sprite>(entity, sprite);
	//compManager->addComponent<Sprite>(entityTwo, spriteTwo);

	//compManager->removeComponent<TransformComponent>(entity);


	//transformSystem->update(0.0f);



	bulletPool = new ObjectPool<Bullet>(50);
	//Bullet* b = bulletPool->getObject();
	//Bullet* b2 = bulletPool->getObject();
	//Bullet* b3 = bulletPool->getObject();




	for (GameObject* gameObject : gameObjects)
	{
		gameObject->start();
	}
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	//testSprite->Update(deltaTime);
	//testSprite2->Update(deltaTime);


	//if (App::GetController().GetLeftThumbStickX() > 0.5f)
	//{
	//	//testSprite->SetAnimation(ANIM_RIGHT);
	//	//float x, y;
	//	//testSprite->GetPosition(x, y);
	//	//x += 1.0f;
	//	//testSprite->SetPosition(x, y);

	//	Transform* transform = sprite->getTransform();

	//	sprite->SetAnimation(ANIM_RIGHT);

	//	vec3 pos = transform->getLocalPosition();
	//	pos.x += 1.0f;
	//	transform->setLocalPosition(pos);
	//}
	//if (App::GetController().GetLeftThumbStickX() < -0.5f)
	//{
	//	//testSprite->SetAnimation(ANIM_LEFT);
	//	//float x, y;
	//	//testSprite->GetPosition(x, y);
	//	//x -= 1.0f;
	//	//testSprite->SetPosition(x, y);

	//	Transform* transform = sprite->getTransform();

	//	sprite->SetAnimation(ANIM_RIGHT);

	//	vec3 pos = transform->getLocalPosition();
	//	pos.x -= 1.0f;
	//	transform->setLocalPosition(pos);
	//}
	//if (App::GetController().GetLeftThumbStickY() > 0.5f)
	//{
	//	//testSprite->SetAnimation(ANIM_FORWARDS);
	//	//float x, y;
	//	//testSprite->GetPosition(x, y);
	//	//y += 1.0f;
	//	//testSprite->SetPosition(x, y);

	//	Transform* transform = sprite->getTransform();

	//	sprite->SetAnimation(ANIM_RIGHT);

	//	vec3 pos = transform->getLocalPosition();
	//	pos.y += 1.0f;
	//	transform->setLocalPosition(pos);
	//}
	//if (App::GetController().GetLeftThumbStickY() < -0.5f)
	//{
	//	//testSprite->SetAnimation(ANIM_BACKWARDS);
	//	//float x, y;
	//	//testSprite->GetPosition(x, y);
	//	//y -= 1.0f;
	//	//testSprite->SetPosition(x, y);

	//	Transform* transform = sprite->getTransform();

	//	sprite->SetAnimation(ANIM_RIGHT);

	//	vec3 pos = transform->getLocalPosition();
	//	pos.y -= 1.0f;
	//	transform->setLocalPosition(pos);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	//{
	//	//testSprite->SetScale(testSprite->GetScale() + 0.1f);

	//	Transform* transform = sprite->getTransform();
	//	vec3 scale = transform->getScale();
	//	scale.x += 0.1f;
	//	scale.y += 0.1f;
	//	transform->setScale(scale);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	//{
	//	//testSprite->SetScale(testSprite->GetScale() - 0.1f);

	//	Transform* transform = sprite->getTransform();
	//	vec3 scale = transform->getScale();
	//	scale.x -= 0.1f;
	//	scale.y -= 0.1f;
	//	transform->setScale(scale);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	//{
	//	//testSprite->SetAngle(testSprite->GetAngle() + 0.1f);

	//	Transform* transform = sprite->getTransform();
	//	vec3 rot = transform->getLocalRotation();
	//	rot.z += 0.1f;
	//	transform->setLocalRotation(rot);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	//{
	//	//testSprite->SetAngle(testSprite->GetAngle() - 0.1f);

	//	Transform* transform = sprite->getTransform();
	//	vec3 rot = transform->getLocalRotation();
	//	rot.z -= 0.1f;
	//	transform->setLocalRotation(rot);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	//{
	//	//testSprite->SetAnimation(-1);
	//	sprite->SetAnimation(-1);
	//}
	//if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	//{
	//	//testSprite->SetVertex(0, testSprite->GetVertex(0) + 5.0f);
	//	vec2 vertex = sprite->GetVertex(0);
	//	vertex.x += 5.0f;
	//	vertex.y += 5.0f;
	//	sprite->SetVertex(0, vertex);
	//}
	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\TestData\\Test.wav");
	}


	float scaledDeltaTime = deltaTime / 1000.0f;
	static float fixedDeltaTime = 1.0f / 60.0f;

	static float timer = 0.0f;
	timer += scaledDeltaTime;


	for (GameObject* gameObject : gameObjects)
	{
		gameObject->fixedUpdate(fixedDeltaTime);
		gameObject->update(scaledDeltaTime);
	}


	//Transform* transThree = compManager->getComponent<Transform>(entityThree);
	////transThree->setWorldPosition(MathUtils::lerp(vec3(250.0f, 250.0f, 0.0f), vec3(400.0f, 400.0f, 0.0f), fabsf(sinf(timer * 0.016f * 0.05f))));
	////transThree->setLocalRotation(vec3(0.0f, 0.0f, 90.0f + (90.0f * sinf(timer))));
	////transThree->setWorldRotation(vec3(0.0f, 0.0f, 45.0f));

	////transform->setWorldRotation(transform->getWorldRotation() + vec3(0.0f, 0.0f, timer));
	////transform->setWorldPosition(transform->getWorldPosition() + vec3(0.0f, 500.0f + (0.016f * 400.0f * sinf(timer)), 0.0f));
	////transform->setWorldPosition(MathUtils::lerp(vec3(300.0f, 200.0f, 0.0f), vec3(300.0f, 600.0f, 0.0f), fabsf(sinf(timer * 0.016f * 0.25f))));
	////transform->setLocalPosition(MathUtils::lerp(vec3(0.0f, 200.0f, 0.0f), vec3(0.0f, 500.0f, 0.0f), fabsf(sinf(timer * 0.016f * 0.25f))));

	//Transform* transTest = compManager->getComponent<Transform>(entity);
	////float x, y;
	////testSprite->GetPosition(x, y);
	////transTest->setLocalRotation(vec3(0.0f, 0.0f, 90.0f + (90.0f * sinf(timer))));



	//Transform* transFour = compManager->getComponent<Transform>(entityFour);
	//transFour->setLocalRotation(vec3(0.0f, 0.0f, 90.0f + (90.0f * sinf(timer))));
	////transFour->setWorldRotation(vec3(0.0f, 0.0f, 90.0f + (90.0f * sinf(timer))));
	////transFour->setWorldRotation(vec3(0.0f, 0.0f, 90.0f));
	//vec3 pos = transFour->getWorldPosition() + vec3(0.0f, 0.0f + (5.0f * sinf(timer * 3.0f)), 0.0f);
	//transFour->setWorldPosition(pos);




	physics2DSystem->update(1.0f / 60.0f);

	//transform->update(deltaTime);
	//transformSystem->update(scaledDeltaTime);
	//testSprite->SetPosition(transform->getWorldPosition().x, transform->getWorldPosition().y);
	//testSprite2->SetPosition(transThree->getWorldPosition().x, transThree->getWorldPosition().y);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	

	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	static float a = 0.0f;
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	a += 0.1f;
	for (int i = 0; i < 20; i++)
	{

		float sx = 200 + sinf(a + i * 0.1f)*60.0f;
		float sy = 200 + cosf(a + i * 0.1f)*60.0f;
		float ex = 700 - sinf(a + i * 0.1f)*60.0f;
		float ey = 700 - cosf(a + i * 0.1f)*60.0f;
		g = (float)i / 20.0f;
		b = (float)i / 20.0f;
		App::DrawLine(sx, sy, ex, ey,r,g,b);
	}

	//------------------------------------------------------------------------
	// Example Sprite Code....
	//testSprite->Draw();
	//testSprite2->Draw();

	//sprite->Draw();
	//spriteTwo->Draw();
	rendering2DSystem->draw();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	App::Print(100, 100, "Sample Text");

	//App::Print(20, 200, std::to_string(transform->getWorldPosition().x).c_str());
	//App::Print(20, 150, std::to_string(transform->getWorldPosition().y).c_str());



	physics2DSystem->debugDraw();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	delete testSprite;
	delete testSprite2;
	//------------------------------------------------------------------------
}