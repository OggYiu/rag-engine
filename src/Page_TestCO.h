#ifndef __PAGE_TESTCO_H__
#define __PAGE_TESTCO_H__

#include "Page.h"

#include <vector>

class Entity_Bot;

class Page_TestCO : public Page
{
public:
	Page_TestCO();
	~Page_TestCO();
	
public:
	virtual void update(const double dt);
	
protected:
	virtual bool resolved();

protected:
	std::vector<Entity_Bot*> bots_;
};
#endif
