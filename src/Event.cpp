#include "Event.h"

#include <iostream>

#include "Logger.h"

Event::Event( const std::string& type )
	: sender_( nullptr )
	, type_( type )
	, timestamp_( SDL_GetTicks() )
{
}

Event::~Event()
{
}

void Event::setSender( EventDispatcher* sender )
{
	if ( sender_ != nullptr ) {
		logger.getInstance().w( "Event", "sender already set" );
		return;
	}
	sender_ = sender;
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
