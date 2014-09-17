#include "Entity.h"

#include <iostream>
#include "DisplayObjectContainer.h"

Entity::Entity()
{
}

Entity::~Entity()
{
//	std::cout << "entity decon" << std::endl;
}

void Entity::setRelease(const bool release)
{
	needReleased_ = release;
}
