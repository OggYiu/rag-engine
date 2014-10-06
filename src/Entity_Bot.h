#ifndef __ENTITY_BOT_H__
#define __ENTITY_BOT_H__

#include "DisplayObjectContainer.h"

class Entity_Bot : public DisplayObjectContainer
{
public:
	Entity_Bot();
	virtual ~Entity_Bot();

public:
	virtual void update(const double dt);
	
protected:
	virtual bool resolved();
};

#endif
