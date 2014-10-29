#ifndef __DEMO_DISPLAY_CONTAINER_H__
#define __DEMO_DISPLAY_CONTAINER_H__

#include <vector>
#include "Demo_Base.h"

class Event;

class Demo_DisplayContainer : public Demo_Base
{
public:
	Demo_DisplayContainer();
	virtual ~Demo_DisplayContainer();

protected:
	virtual bool resolved();
};

#endif
