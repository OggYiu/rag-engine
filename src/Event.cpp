#include "Event.h"

Event::	Event(const std::string& type):
	type_(type)
{
}

Event::~Event()
{
	
}

const std::string& Event::getType() const
{
	return type_;
}
