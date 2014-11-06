#ifndef __DEMO_TWEEN_H__
#define __DEMO_TWEEN_H__

#include "Demo_Base.h"

class Event;

class Demo_Tween : public Demo_Base
{
public:
	Demo_Tween();
	virtual ~Demo_Tween();

public:
	virtual void update(const double dt);
	
protected:
	virtual void resolved();
};

#endif
