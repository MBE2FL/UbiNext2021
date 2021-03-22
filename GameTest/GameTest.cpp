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
#include "BulletCannon.h"

#include "SystemManager.h"
#include "TransformSystem.h"
#include "Physics2DSystem.h"
#include "Rendering2DSystem.h"
#include "TowerSystem.h"
#include "Input.h"

#include "ObjectPool.h"
#include "Bullet.h"
#include "Character.h"
#include "Ship.h"
#include "Tower.h"
#include "UIButton.h"
#include "Factory.h"
#include "ObjectPlacement.h"
#include "Enemy.h"
#include "Ground.h"
#include "Path.h"
#include "Map.h"

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------
//CSimpleSprite *testSprite;
//CSimpleSprite *testSprite2;
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
//TransformSystem* transformSystem;
Physics2DSystem* physics2DSystem;
Rendering2DSystem* rendering2DSystem;
TowerSystem* towerSystem;


//Entity* entity;
//Entity* entityTwo;
//Entity* entityThree;
//Entity* entityFour;
//
//Sprite* sprite;
//Sprite* spriteTwo;
Character* player;
Ship* ship;
Tower* testTower;
UIButton* towerOneButton;
UIButton* enemyButton;
UIButton* groundButton;
UIButton* pathButton;
GameObject* selectedGameObject = nullptr;
Factory* factory;
Map* simpleMap;


std::vector<Transform*> spawnPoints;


ObjectPool<Enemy>* enemyPool;
std::vector<GameObject*> gameObjects;

void addGameObject(GameObject* object)
{
	gameObjects.emplace_back(object);
}

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	factory = Factory::getInstance();
	factory->onObjectCreated = std::bind(&addGameObject, std::placeholders::_1);

	entManager = EntityManager::getInstance();
	compManager = ComponentManager::getInstance();
	sysManager = SystemManager::getInstance();


	//transformSystem = sysManager->registerSystem<TransformSystem>();
	rendering2DSystem = sysManager->registerSystem<Rendering2DSystem>();
	physics2DSystem = sysManager->registerSystem<Physics2DSystem>();
	towerSystem = sysManager->registerSystem<TowerSystem>();



	simpleMap = Map::getMap();


	spawnPoints.emplace_back(simpleMap->tiles[0][2]->transform);
	spawnPoints.emplace_back(simpleMap->tiles[0][3]->transform);
	spawnPoints.emplace_back(simpleMap->tiles[0][6]->transform);
	spawnPoints.emplace_back(simpleMap->tiles[0][7]->transform);


	// ************ Object One ************
	//player = factory->create<Character>();


	// ************ Object Two ************
	//ship = factory->create<Ship>();



	enemyPool = new ObjectPool<Enemy>(50);
	//Enemy* enemy = enemyPool->getObject();
	//enemy->transform->setWorldPosition(vec3(800.0f, 300.0f, -20.0f));



	//towerOneButton = new UIButton();
	towerOneButton = factory->create<UIButton>();
	towerOneButton->setImage(".\\TestData\\TowerOneTest.bmp", 1, 1);
	towerOneButton->transform->setWorldPosition(vec3(512.0f, 20.0f, 0.0f));
	gameObjects.emplace_back(towerOneButton);
	towerOneButton->onClicked.emplace_back(
		[]() 
		{
			Tower* tower = Factory::getInstance()->create<Tower>();
			tower->addComponent<BulletCannon>();
			//tower->setTexture(".\\TestData\\Ships.bmp", 2, 12);
			tower->setTexture(".\\TestData\\TowerOneTest.bmp", 1, 1);
			tower->getSprite()->SetFrame(0);
			tower->setActive(false);

			ObjectPlacement* objectPlacer = Factory::getInstance()->create<ObjectPlacement>();
			objectPlacer->setObject(tower, tower->getSprite());
		});



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
	// Update input manager.
	Input::update();

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



	// Spawn enemies on a timer, and at a random spawn point.
	static float enemyTimer = 0.0f;
	enemyTimer += scaledDeltaTime;

	if (enemyTimer >= 2.0f)
	{
		size_t index = MathUtils::randInRange<size_t>(0, 3);

		vec3 enemySpawnPos = spawnPoints[index]->getWorldPosition();

		Enemy* enemy = enemyPool->getObject();
		enemy->transform->setWorldPosition(enemySpawnPos);

		enemyTimer = 0.0f;
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


	towerSystem->update(scaledDeltaTime);

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
	//static float a = 0.0f;
	//float r = 1.0f;
	//float g = 1.0f;
	//float b = 1.0f;
	//a += 0.1f;
	//for (int i = 0; i < 20; i++)
	//{

	//	float sx = 200 + sinf(a + i * 0.1f)*60.0f;
	//	float sy = 200 + cosf(a + i * 0.1f)*60.0f;
	//	float ex = 700 - sinf(a + i * 0.1f)*60.0f;
	//	float ey = 700 - cosf(a + i * 0.1f)*60.0f;
	//	g = (float)i / 20.0f;
	//	b = (float)i / 20.0f;
	//	App::DrawLine(sx, sy, ex, ey,r,g,b);
	//}

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
	//App::Print(100, 100, "Sample Text");

	//App::Print(20, 200, std::to_string(transform->getWorldPosition().x).c_str());
	//App::Print(20, 150, std::to_string(transform->getWorldPosition().y).c_str());



	physics2DSystem->debugDraw();


	// Perform a late update to the input system.
	Input::lateUpdate();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	//delete testSprite;
	//delete testSprite2;
	//------------------------------------------------------------------------

	for (GameObject* object : gameObjects)
	{
		delete object;
	}
}
