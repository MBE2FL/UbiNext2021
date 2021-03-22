#include "stdafx.h"
#include "UIButton.h"
#include "Sprite.h"
#include "vec4.h"


UIButton::UIButton()
    : GameObject()
{
    _sprite = addComponent<Sprite>();
    _sprite->setTexture(".\\TestData\\Ships.bmp", 2, 12);


    // Assign callback function.
    onMouseClick.emplace_back(std::bind(&UIButton::click, this));
}

UIButton::~UIButton()
{
}

void UIButton::start()
{
}

void UIButton::update(float deltaTime)
{
}

void UIButton::fixedUpdate(float fixedDeltaTime)
{
}

void UIButton::click()
{
    // This button is not interactable.
    if (!_isInteractable || !getIsActive())
    {
        return;
    }

    // Notify any listeners of the button click.
    for (const OnClickedSignature& callback : onClicked)
    {
        callback();
    }

    //setIsInteractable(false);
}

void UIButton::setImage(const char* fileName, size_t numColumns, size_t numRows)
{
    _sprite->setTexture(fileName, numColumns, numRows);
}

void UIButton::setIsInteractable(bool isInteractable)
{
    _isInteractable = isInteractable;

    float alpha = _isInteractable ? 1.0f: 0.25f;

    _sprite->setAlpha(alpha);
}
