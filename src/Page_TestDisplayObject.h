#ifndef __PAGE_DISPLAY_OBJECT_CONTAINER_TEST_H__
#define __PAGE_DISPLAY_OBJECT_CONTAINER_TEST_H__

#include <iostream>
#include "Page.h"


class Page_TestDisplayObject : public Page
{
public:
	Page_TestDisplayObject();
	virtual ~Page_TestDisplayObject();
	
public:
	virtual void update(const double dt);
	virtual void render();
	void startDemo( const int num );
	
protected:
	virtual bool resolved();
	bool eventHandler( const Event& event );
};

#endif
