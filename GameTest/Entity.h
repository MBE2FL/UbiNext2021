#pragma once



class Entity
{
public:
	Entity() = default;
	/// <summary>
	/// Creates an entity with the specified id.
	/// </summary>
	/// <param name="eid">The id to assign to this entity.</param>
	Entity(size_t eid);
	~Entity();


	/// <summary>
	/// </summary>
	/// <returns>The id of this entity.</returns>
	size_t getEid() const;


	bool operator==(const Entity& rhs) const;


private:
	size_t _eid;
};