#pragma once
#include "stdafx.h"
#include "Entity.h"




class IComponentArray
{
public:
	virtual ~IComponentArray() = default;

	virtual void onEntityDestroyed(Entity* entity) = 0;
};



template<typename T>
class ComponentArray : public IComponentArray
{
public:
	ComponentArray();
	~ComponentArray();


	///// <summary>
	///// Adds a component to an entity.
	///// </summary>
	///// <param name="entity">The entity to add to.</param>
	///// <param name="component">The component to add.</param>
	//void addComponent(Entity* entity, T* component);
	/// <summary>
	/// Adds a component to an entity.
	/// </summary>
	/// <typeparam name="...Args">The constructor parameters for the new component.</typeparam>
	/// <param name="entity">The entity to add to.</param>
	/// <param name="...args">The constructor parameters for the new component.</param>
	/// <returns>The newly added component.</returns>
	template<typename... Args>
	T* addComponent(Entity* entity, Args&&... args);
	/// <summary>
	/// Removes a component from an entity.
	/// </summary>
	/// <param name="entity">The entity to remove from.</param>
	void removeComponent(Entity* entity);
	/// <summary>
	/// Gets a component from an entity.
	/// </summary>
	/// <param name="entity">The entity attached to the component.</param>
	/// <returns>The component attached to the entity, or nullptr if no such component exists.</returns>
	T* getComponent(Entity* entity);
	/// <summary>
	/// Callback for when an entity is destroyed.
	/// </summary>
	/// <param name="entity">The entity that was destroyed.</param>
	virtual void onEntityDestroyed(Entity* entity) override;
	/// <summary>
	/// Clears this component array.
	/// </summary>
	void clear();
	/// <summary>
	/// Checks if an entity has a component attached to it.
	/// </summary>
	/// <param name="entity">The entity to examine.</param>
	/// <returns>True iff the entity has a component attached to it, false otherwise.</returns>
	bool hasComponent(Entity* entity) const;
	/// <summary>
	/// </summary>
	/// <returns>The size of this component array.</returns>
	size_t getSize() const;
	/// <summary>
	/// </summary>
	/// <returns>True iff this component array does not have any components, false otherwise.</returns>
	bool isEmpty() const;
	/// <summary>
	/// Resizes this component array to the specified size.
	/// </summary>
	/// <param name="newSize">The new size.</param>
	void resize(size_t newSize);


	typedef typename std::vector<T*> vector_type;
	typedef typename vector_type::iterator iterator;
	typedef typename vector_type::const_iterator const_iterator;

	inline iterator begin() noexcept
	{
		return _compArray.begin();
	}

	inline const_iterator cbegin() noexcept
	{
		return _compArray.cbegin();
	}

	inline iterator end() noexcept
	{
		return _compArray.end();
	}

	inline const_iterator cend() noexcept
	{
		return _compArray.cend();
	}


private:
	std::vector<T*> _compArray;				// Array of components.

	std::vector<size_t> _denseIndices;		// Dense indices to component array indices.
	std::vector<size_t> _sparseIndices;		// Entity ids to dense indices.

	size_t _size = 0;						// Current size, not capacity, of the dense indices array.
};



template<typename T>
inline ComponentArray<T>::ComponentArray()
{
	//_compArray.resize(1000);
	//_denseIndices.reserve(1000);
	_sparseIndices.resize(1000, 0);		//TO-DO Match with entity manager.
}

template<typename T>
inline ComponentArray<T>::~ComponentArray()
{
	_compArray.clear();
	_denseIndices.clear();
	
	//for (size_t* denseIndex : _sparseIndices)
	//{
	//	delete denseIndex;
	//	denseIndex = nullptr;
	//}

	_denseIndices.clear();
}

//template<typename T>
//inline void ComponentArray<T>::addComponent(Entity* entity, T* component)
//{
//	// Check if the entity doesn't already have a component of type T.
//	if (!hasComponent(entity))
//	{
//		// Check if sparse set needs to be resized to accommodate the entity.
//		if (entity->getEid() > _sparseIndices.size())
//		{
//			resize(_sparseIndices.size() + 1);
//		}
//
//
//		// Construct a new component for the entity.
//		_compArray.push_back(component);
//
//
//		// Create the link between the entites id and the index of it's component in the sparse set.
//		//_denseIndices[_size] = entity.getEid();
//		_denseIndices.push_back(entity->getEid());
//		_sparseIndices[entity->getEid()] = _size;
//		
//
//		// Increment the size of the tightly packed component pool.
//		++_size;
//	}
//}

template<typename T>
template<typename ...Args>
inline T* ComponentArray<T>::addComponent(Entity* entity, Args&&... args)
{
	// Check if the entity doesn't already have a component of type T.
	if (!hasComponent(entity))
	{
		// Check if sparse set needs to be resized to accommodate the entity.
		if (entity->getEid() > _sparseIndices.size())
		{
			resize(_sparseIndices.size() + 1);
		}


		// Construct a new component for the entity.
		T* component = new T(std::forward<Args>(args)...);
		_compArray.push_back(component);


		// Create the link between the entites id and the index of it's component in the sparse set.
		//_denseIndices[_size] = entity.getEid();
		_denseIndices.push_back(entity->getEid());
		_sparseIndices[entity->getEid()] = _size;


		// Increment the size of the tightly packed component pool.
		++_size;


		// Return the newly constructed component.
		return component;
	}
}

template<typename T>
inline void ComponentArray<T>::removeComponent(Entity* entity)
{
	size_t eid = entity->getEid();

	//bool match = _denseIndices[_sparseIndices[eid]] == eid;

	// Remove component.
	if (hasComponent(entity))
	{
		// Remove the entity's component from the component pool.
		_compArray[_sparseIndices[eid]] = _compArray.back();
		_compArray.erase(_compArray.end() - 1);						// TO-DO Delete component.

		// Remove the link between the entity and it's component in the sparse set.
		_denseIndices[_sparseIndices[eid]] = _denseIndices[_size - 1];
		_sparseIndices[_denseIndices[_size - 1]] = _sparseIndices[eid];

		_denseIndices.erase(_denseIndices.end() - 1);

		// Decrement the size of the tightly packed component pool.
		--_size;
	}
}

template<typename T>
inline T* ComponentArray<T>::getComponent(Entity* entity)
{
	//bool match = _denseIndices[_sparseIndices[entity.getEid()]] == entity.getEid();

	// Entity has component of type T.
	if (hasComponent(entity))
	{
		return _compArray[_sparseIndices[entity->getEid()]];
	}
	// Entity does not have a component of type T.
	else
	{
		return nullptr;
	}
}

template<typename T>
inline void ComponentArray<T>::onEntityDestroyed(Entity* entity)
{
	removeComponent(entity);
}

template<typename T>
inline void ComponentArray<T>::clear()
{
	_size = 0;
}

template<typename T>
inline bool ComponentArray<T>::hasComponent(Entity* entity) const
{
	//return (entity < _sparseIndices.capacity) && 
	//	(_sparseIndices[entity.getEid()] < _size) && 
	//	(_denseIndices[_sparseIndices[entity.getEid()]] == entity.getEid());

	return (entity->getEid() < _sparseIndices.size()) &&
		(_sparseIndices[entity->getEid()] < _size) &&
		(_denseIndices[_sparseIndices[entity->getEid()]] == entity->getEid());
}

template<typename T>
inline size_t ComponentArray<T>::getSize() const
{
	return _size;
}

template<typename T>
inline bool ComponentArray<T>::isEmpty() const
{
	return _size == 0;
}

template<typename T>
inline void ComponentArray<T>::resize(size_t newSize)
{
	if (newSize > _sparseIndices.size())
	{
		_sparseIndices.resize(newSize, 0);
	}
}
