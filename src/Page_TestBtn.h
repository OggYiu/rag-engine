#ifndef __PAGE_TEST_BTN_H__
#define __PAGE_TEST_BTN_H__

#include "Page.h"

class Page_TestBtn : public Page
{
public:
	Page_TestBtn();
	virtual ~Page_TestBtn();
	
public:	
	virtual void update(const double dt);
	virtual void render();

protected:
	virtual bool resolved();
};

#endif
