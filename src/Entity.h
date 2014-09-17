#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "DisplayObject.h"

class Texture;
class DisplayObjectContainer;

class Entity : public DisplayObject
{
public:
	Entity();
	virtual ~Entity();
	
public:
	bool needReleased();
	void setRelease(const bool release);
	
protected:
	bool needReleased_;
};
#endif
