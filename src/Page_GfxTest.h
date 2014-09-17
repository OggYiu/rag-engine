#ifndef __PAGE_GFXTEST_H__
#define __PAGE_GFXTEST_H__

#include "Page.h"

class Page_GfxTest : public Page
{
public:
	Page_GfxTest();
	~Page_GfxTest();
	
public:
   	virtual void enter();
	virtual void update(const double dt);

protected:
	virtual bool resolved();

protected:
};

#endif
