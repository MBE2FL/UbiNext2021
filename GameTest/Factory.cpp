#include "stdafx.h"
#include "Factory.h"


Factory* Factory::_instance = nullptr;


Factory* Factory::getInstance()
{
    if (!_instance)
    {
        _instance = new Factory();
    }

    return _instance;
}
