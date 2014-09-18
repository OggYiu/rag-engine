#ifndef __PAGE_TEST_FONT_H__
#define __PAGE_TEST_FONT_H__

#include "Page.h"

class GUI_Label;

class Page_TestFont : public Page
{
private:
	typedef Page Parent;
	
public:
	Page_TestFont();
	virtual ~Page_TestFont();

public:	
	virtual void update(const double dt);
	virtual void render();
	
protected:
	virtual bool resolved();
	
protected:
	std::vector<GUI_Label*> labels_;
};

#endif
