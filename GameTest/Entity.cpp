#include "stdafx.h"
#include "Entity.h"




Entity::Entity(size_t eid)
{
    _eid = eid;
}

Entity::~Entity()
{
}

size_t Entity::getEid() const
{
    return _eid;
}

bool Entity::operator==(const Entity& rhs) const
{
    return _eid == rhs._eid;
}
