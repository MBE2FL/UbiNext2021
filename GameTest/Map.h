#pragma once
#include <vector>


class GameObject;
class vec3;


class Map
{
public:
	Map();
	~Map();


	static Map* getMap();


	bool isTileOccupied(const vec3& pos) const;
	void setIsTileOccupied(bool isOccupied, const vec3& pos);


	std::vector<std::vector<GameObject*>> tiles;
};