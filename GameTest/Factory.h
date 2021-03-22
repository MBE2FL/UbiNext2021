#pragma once
#include <functional>


class GameObject;


typedef std::function<void(GameObject* object)> OnObjectCreatedSignature;


class Factory
{
public:
	~Factory() = default;


	static Factory* getInstance();


	template<typename T, typename... Args>
	T* create(Args&&... args);


	OnObjectCreatedSignature onObjectCreated;


private:
	Factory() = default;
	static Factory* _instance;


	
};



template<typename T, typename ...Args>
inline T* Factory::create(Args&&... args)
{
	T* object = new T(std::forward<Args>(args)...);

	if (onObjectCreated)
	{
		onObjectCreated(object);
	}

	return object;
}
