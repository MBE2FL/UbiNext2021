#pragma once


enum class MouseButton : uint8_t
{
	LEFT = 1,
	RIGHT = 2,
	MIDDLE = 4,
};

struct MouseEventInfo
{
	MouseEventInfo()
		: leftButtonState(-1), rightButtonState(-1), middleButtonState(-1)
	{

	}

	bool leftButtonState;
	bool rightButtonState;
	bool middleButtonState;
};


class Input
{
public:
	static void update();
	static void lateUpdate();


	static bool getMouseButton(MouseButton button);
	static bool getMouseButtonDown(MouseButton button);
	static bool getMouseButtonUp(MouseButton button);


private:
	static MouseEventInfo _mouseEventInfo;
	static MouseEventInfo _prevMouseEventInfo;


	static bool getMouseButtonInternal(MouseButton button);
};