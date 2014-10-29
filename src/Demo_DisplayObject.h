#ifndef __DEMO_DISPLAY_OBJECT_H__
#define __DEMO_DISPLAY_OBJECT_H__

#include <vector>
#include "Demo_Base.h"

class Event;

class Demo_DisplayObject : public Demo_Base
{
public:
	Demo_DisplayObject();
	virtual ~Demo_DisplayObject();

public:
	virtual void update(const double dt);
	
protected:
	virtual bool resolved();
};

#endif
