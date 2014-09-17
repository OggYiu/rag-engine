#ifndef __PAGE_H__
#define __PAGE_H__

#include "DisplayObjectContainer.h"

class Page : public DisplayObjectContainer
{
public:
	Page();
	virtual ~Page();
	
public:
	virtual void enter();

private:
	
	// void update(double dt);
	// void render();
};
#endif
