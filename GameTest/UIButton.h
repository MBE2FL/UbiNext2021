#pragma once
#include "GameObject.h"
#include <functional>


class Sprite;


typedef std::function<void()> OnClickedSignature;


class UIButton : public GameObject
{
public:
	UIButton();
	~UIButton();


	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void fixedUpdate(float fixedDeltaTime) override;


	void click();
	void setImage(const char* fileName, size_t numColumns = 1, size_t numRows = 1);
	inline bool getIsInteractable() const
	{
		return _isInteractable;
	}
	void setIsInteractable(bool isInteractable);

	inline Sprite* getSprite() const
	{
		return _sprite;
	}


	std::vector<OnClickedSignature> onClicked;

private:
	bool _isInteractable = true;
	Sprite* _sprite;
};