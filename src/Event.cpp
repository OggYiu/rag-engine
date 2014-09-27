#include "Event.h"

Event::Event( const std::string& type, const unsigned int timestamp )
	: type_( type )
	, timestamp_( timestamp )
{
}

Event::~Event()
{
}

const std::string& Event::getType() const
{
	return type_;
}

unsigned int Event::getTimestamp() const
{
	return timestamp_;
}

bool Event::isEqual( const std::string& type ) const
{
	return type_.compare( type ) == 0;
}
