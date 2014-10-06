#include "Entity_Bot.h"

Entity_Bot::Entity_Bot()
{
}

Entity_Bot::~Entity_Bot()
{
}

void Entity_Bot::update(const double dt)
{
	DisplayObjectContainer::update( dt );
}

bool Entity_Bot::resolved()
{
	DisplayObjectContainer::resolved();

	return true;
}
