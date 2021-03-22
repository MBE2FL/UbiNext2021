#include "stdafx.h"
#include "Map.h"
#include "Factory.h"
#include "vec3.h"
#include "App/app.h"
#include "Ground.h"
#include "Path.h"
#include "Transform.h"




Map::Map()
{
	// Creates a simple map.
	for (size_t x = 0; x < 15; ++x)
	{
		std::vector<GameObject*> row;
		for (size_t y = 0; y < 10; ++y)
		{
			vec3 pos;
			pos.x = 64 + (x * 64);
			pos.y = (APP_VIRTUAL_HEIGHT - 64) - (y * 64);
			pos.z = -20.0f;

			size_t mod = y % 4;
			if ((mod == 0) || (mod == 1))
			{
				Ground* ground = Factory::getInstance()->create<Ground>();
				ground->transform->setWorldPosition(pos);
				row.emplace_back(ground);
			}
			else
			{
				Path* path = Factory::getInstance()->create<Path>();
				path->transform->setWorldPosition(pos);
				row.emplace_back(path);
			}
		}

		tiles.emplace_back(row);
	}
}

Map::~Map()
{
}

Map* Map::getMap()
{
	static Map* map = new Map();
	return map;
}

bool Map::isTileOccupied(const vec3& pos) const
{
	if (pos.x < 63.0f || pos.x > 961.0f ||
		pos.y < 127.0f || pos.y > 705.0f)
	{
		return true;
	}

	size_t xIndex = (-64 + pos.x) / 64;
	size_t yIndex = ((APP_VIRTUAL_HEIGHT - 64) - pos.y) / 64;

	GameObject* object = tiles[xIndex][yIndex];

	if (Ground* ground = dynamic_cast<Ground*>(object))
	{
		return ground->getIsOccupied();
	}
	else if (Path* path = dynamic_cast<Path*>(object))
	{
		return path->getIsOccupied();
	}

    return true;
}

void Map::setIsTileOccupied(bool isOccupied, const vec3& pos)
{
	if (pos.x < 63.0f || pos.x > 961.0f ||
		pos.y < 127.0f || pos.y > 705.0f)
	{
		return;
	}

	size_t xIndex = (-64 + pos.x) / 64;
	size_t yIndex = ((APP_VIRTUAL_HEIGHT - 64) - pos.y) / 64;

	GameObject* object = tiles[xIndex][yIndex];

	if (Ground* ground = dynamic_cast<Ground*>(object))
	{
		ground->setIsOccupied(isOccupied);
	}
}
