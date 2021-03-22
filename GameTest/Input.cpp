#include "stdafx.h"
#include "Input.h"
#include "App/app.h"


MouseEventInfo Input::_mouseEventInfo = MouseEventInfo();
MouseEventInfo Input::_prevMouseEventInfo = MouseEventInfo();


void Input::update()
{
	_mouseEventInfo.leftButtonState = getMouseButtonInternal(MouseButton::LEFT);
	_mouseEventInfo.rightButtonState = getMouseButtonInternal(MouseButton::RIGHT);
	_mouseEventInfo.middleButtonState = getMouseButtonInternal(MouseButton::MIDDLE);
}

void Input::lateUpdate()
{
	_prevMouseEventInfo.leftButtonState = _mouseEventInfo.leftButtonState;
	_prevMouseEventInfo.rightButtonState = _mouseEventInfo.rightButtonState;
	_prevMouseEventInfo.middleButtonState = _mouseEventInfo.middleButtonState;
}

bool Input::getMouseButton(MouseButton button)
{
	switch (button)
	{
	case MouseButton::LEFT:
		return _mouseEventInfo.leftButtonState;
		break;
	case MouseButton::RIGHT:
		return _mouseEventInfo.rightButtonState;
		break;
	case MouseButton::MIDDLE:
		return _mouseEventInfo.middleButtonState;
		break;
	default:
		return false;
		break;
	}
}

bool Input::getMouseButtonDown(MouseButton button)
{
	switch (button)
	{
	case MouseButton::LEFT:
		return _mouseEventInfo.leftButtonState && !_prevMouseEventInfo.leftButtonState;
		break;
	case MouseButton::RIGHT:
		return _mouseEventInfo.rightButtonState && !_prevMouseEventInfo.rightButtonState;
		break;
	case MouseButton::MIDDLE:
		return _mouseEventInfo.middleButtonState && !_prevMouseEventInfo.middleButtonState;
		break;
	default:
		return false;
		break;
	}
}

bool Input::getMouseButtonUp(MouseButton button)
{
	switch (button)
	{
	case MouseButton::LEFT:
		return !_mouseEventInfo.leftButtonState && _prevMouseEventInfo.leftButtonState;
		break;
	case MouseButton::RIGHT:
		return !_mouseEventInfo.rightButtonState && _prevMouseEventInfo.rightButtonState;
		break;
	case MouseButton::MIDDLE:
		return !_mouseEventInfo.middleButtonState && _prevMouseEventInfo.middleButtonState;
		break;
	default:
		return false;
		break;
	}
}

bool Input::getMouseButtonInternal(MouseButton button)
{
	switch (button)
	{
	case MouseButton::LEFT:
		return App::IsKeyPressed(VK_LBUTTON);
		break;
	case MouseButton::RIGHT:
		return App::IsKeyPressed(VK_RBUTTON);
		break;
	case MouseButton::MIDDLE:
		return App::IsKeyPressed(VK_MBUTTON);
		break;
	default:
		return false;
		break;
	}
}
