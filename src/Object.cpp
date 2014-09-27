#include "Object.h"

#include <iostream>
#include <assert.h>

int Object::s_nextId = 0;

Object::Object()
	: id_( s_nextId++ )
	, updated_(false)
{
}

Object::~Object()
{
//	std::cout << "object decon" << std::endl;	
}

void Object::update( const double dt __attribute__((unused)) )
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
}

