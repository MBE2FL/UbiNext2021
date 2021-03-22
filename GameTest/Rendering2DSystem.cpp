#include "stdafx.h"
#include "Rendering2DSystem.h"
#include "Sprite.h"
#include "ComponentManager.h"
#include "GameObject.h"
#include "App/app.h"
#include "Input.h"
#include "Transform.h"



Rendering2DSystem::Rendering2DSystem()
	: System()
{
	_selectedObject = nullptr;
}

Rendering2DSystem::~Rendering2DSystem()
{
}

void Rendering2DSystem::draw()
{
	// Reset last selected game object which was clicked on by the mouse.
	_selectedObject = nullptr;


	ComponentManager* compManager = ComponentManager::getInstance();

	ComponentArray<Sprite>* spriteArray = nullptr;
	if (!compManager->getAllComponentsOfType<Sprite>(&spriteArray))
	{
		return;
	}


	// User clicked left mouse button.
	//bool isMousePressed = App::IsKeyPressed(VK_LBUTTON);
	bool isMousePressed = Input::getMouseButtonDown(MouseButton::LEFT);
	vec2 mousePos;
	App::GetMousePos(mousePos.x, mousePos.y);
	bool isMouseOverSprite = false;


	for (Sprite* sprite : *spriteArray)
	{
		if (sprite->gameObject->getIsActive())
		{
			sprite->Update(1.0f / 60.0f);
			sprite->Draw();


			// Check if the user clicked on any object with their mouse.
			if (isMousePressed)
			{
				bool clickedOnSprite = sprite->isMouseOverSprite(mousePos);

				if (clickedOnSprite)
				{
					// Selected a sprite for the first time this frame.
					if (!_selectedObject)
					{
						_selectedObject = sprite->gameObject;
					}
					// Another sprite was found when clicking the mouse.
					else
					{
						// Use the z-axis and pick the one closest to the screen.
						if (_selectedObject->transform->getWorldPosition().z < sprite->transform->getWorldPosition().z)
						{
							_selectedObject = sprite->gameObject;
						}
					}

					isMouseOverSprite = true;
				}
			}
		}
	}


	// Call any assigned on mouse click callbacks for the selected object.
	if (isMousePressed && _selectedObject && isMouseOverSprite)
	{
		for (const OnMouseClickSignature& callback : _selectedObject->onMouseClick)
		{
			callback();
		}
	}
}
