#include "Object.h"

#include <iostream>
#include <assert.h>

int Object::s_nextObjectId = 1;
Object::Object():
	released_(false),
	updated_(false),
	age_(0),
	id_(Object::s_nextObjectId++)
{
}

Object::~Object()
{
//	std::cout << "object decon" << std::endl;	
}

void Object::update(const double dt)
{
	if (!updated_)
	{
		// std::cout << "crate" << std::endl;
		if (!resolved())
		{
			assert(false && "creation failed");
		}
		updated_ = true;
	}
	age_ += dt;
}

int Object::getId() const
{
	return id_;
}


