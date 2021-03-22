#pragma once
#include "GameObject.h"


class Sprite;
class Collider2D;


typedef std::function<void(Collider2D*)> OnEnterRadiusSignature;
typedef std::function<void(Collider2D*)> OnExitRadiusSignature;


class Tower : public GameObject
{
public:
	Tower();
	~Tower();


	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void fixedUpdate(float fixedDeltaTime) override;

	void setTexture(const char* fileName, size_t numColumns = 1, size_t numRows = 1);

	inline Sprite* getSprite() const
	{
		return _sprite;
	}


	OnEnterRadiusSignature onEnterRadius;
	OnExitRadiusSignature onExitRadius;


private:
	Sprite* _sprite;


	void onTriggerEnter(Collider2D* other);
	void onTriggerExit(Collider2D* other);
};