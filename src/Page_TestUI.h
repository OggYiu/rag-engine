#ifndef __PAGE_TEST_UI_H__
#define __PAGE_TEST_UI_H__

#include "Page.h"

class GUI_Label;

class Page_TestUI : public Page
{
public:
	Page_TestUI();
	virtual ~Page_TestUI();
	
public:	
	virtual void update(const double dt);
	virtual void render();

protected:
	virtual bool resolved();
	void here();
};

#endif
