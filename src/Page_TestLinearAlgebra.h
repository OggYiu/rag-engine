#ifndef __PAGE_TEST_LINEAR_ALGEBRA_H__
#define __PAGE_TEST_LINEAR_ALGEBRA_H__

#include "Page.h"

class Page_TestLinearAlgebra : public Page
{
public:
	Page_TestLinearAlgebra();
	virtual ~Page_TestLinearAlgebra();

public:	
	virtual void update(const double dt);
	virtual void render();
	
protected:
	virtual void resolved();
};

#endif
