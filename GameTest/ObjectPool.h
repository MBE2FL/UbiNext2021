//https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c/
//https://kevinushey.github.io/blog/2016/01/27/introduction-to-c++-variadic-templates/

#pragma once
#include "stdafx.h"
#include <functional>
#include "Factory.h"


#define POOL_SIZE_INCREASE 20



template<typename T>
class ObjectPool
{
public:
	ObjectPool() = delete;
	//ObjectPool(size_t initialSize);
	template<typename... Args>
	ObjectPool(size_t initialSize = 20, Args&&... defaultObjectArgs);
	~ObjectPool();


	T* getObject();


private:
	std::vector<T*> _pool;
	std::vector<T*> _activePool;
	T* _prototype;


	void recycleObject(GameObject* object);
	void resetObject(T* object);
	void addObjectsToPool(size_t numObjects);
};



//template<typename T>
//inline ObjectPool<T>::ObjectPool(size_t initialSize)
//{
//	// Add the specified number of objects to this pool.
//	_pool.reserve(initialSize);
//	_activePool.reserve(initialSize);
//
//	_prototype = new T();
//	_prototype->onRecycle = std::bind(&ObjectPool<T>::recycleObject, this, std::placeholders::_1);
//
//	for (size_t i = 0; i < initialSize; ++i)
//	{
//		T* object = new T(*_prototype);
//		_pool.emplace_back(object);
//
//		// Deactivate the object.
//		object->setActive(false);
//	}
//}

template<typename T>
template<typename ...Args>
inline ObjectPool<T>::ObjectPool(size_t initialSize, Args&&... defaultObjectArgs)
{
	// Add the specified number of objects to this pool.
	_pool.reserve(initialSize);
	_activePool.reserve(initialSize);

	//_prototype = new T(std::forward<Args>(defaultObjectArgs)...);
	//_prototype->onRecycle = std::bind(&ObjectPool<T>::recycleObject, this, std::placeholders::_1);

	for (size_t i = 0; i < initialSize; ++i)
	{
		//T* object = new T(*_prototype);
		//T* object = new T(std::forward<Args>(defaultObjectArgs)...);
		T* object = Factory::getInstance()->create<T>(std::forward<Args>(defaultObjectArgs)...);
		_pool.emplace_back(object);

		// Deactivate the object.
		object->setActive(false);

		object->onRecycle = std::bind(&ObjectPool<T>::recycleObject, this, std::placeholders::_1);

		object->start();
	}
}

template<typename T>
inline ObjectPool<T>::~ObjectPool()
{
	// Delete all of this pool's objects.
	for (T* object : _pool)
	{
		delete object;
	}

	for (T* object : _activePool)
	{
		delete object;
	}
}

template<typename T>
inline T* ObjectPool<T>::getObject()
{
	// This pool needs to be resized in order to provide an object.
	if (_pool.size() <= 0)
	{
		addObjectsToPool(POOL_SIZE_INCREASE);
	}


	// Return an object from this pool.
	T* object = _pool.back();
	_pool.pop_back();
	_activePool.emplace_back(object);

	// Activate the object.
	object->setActive(true);

	return object;
}

template<typename T>
inline void ObjectPool<T>::recycleObject(GameObject* object)
{
	T* castObject = static_cast<T*>(object);

	// Recycle the object back into this pool.
	_pool.emplace_back(castObject);

	// Remove object from the active pool.
	for (size_t i = 0; i < _activePool.size(); ++i)
	{
		if (castObject == _activePool[i])
		{
			T* temp = _activePool.back();
			_activePool[i] = temp;
			_activePool.pop_back();
		}
	}

	// Reset the object.
	resetObject(castObject);

	// Deactivate the object.
	castObject->setActive(false);
}

template<typename T>
inline void ObjectPool<T>::resetObject(T* object)
{
	//object = *_prototype;

	object->reset();

	// TO-DO Deactivate object
}

template<typename T>
inline void ObjectPool<T>::addObjectsToPool(size_t numObjects)
{
	// Add the specified number of objects to this pool.
	_pool.reserve(_pool.capacity() + numObjects);

	for (size_t i = 0; i < numObjects; ++i)
	{
		//_pool.emplace_back(new T(*_prototype));
		//T* object = new T();
		T* object = Factory::getInstance()->create<T>();
		_pool.emplace_back(object);

		object->start();
	}
}
