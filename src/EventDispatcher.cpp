#include "EventDispatcher.h"

#include <iostream>
#include <sstream>

#include "Event.h"
#include "Helper.h"

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
//	std::cout << "eventdispatcher decon" << std::endl;
	removeAllEventListener();
}

void EventDispatcher::removeAllEventListener()
{
	EventDispatcher::EventListeners::iterator iter = listeners_.begin();
	EventDispatcher::EventListeners::iterator endIter = listeners_.end();
	while (iter != endIter)
	{
		SAFE_RELEASE( *iter );
		++iter;
	}

	listeners_.clear();
}

void EventDispatcher::addEventListener( const std::string& type, const EventListener::EventHandler& handler, const Object* invoker )
{
	// std::string mapId = generateId(type, invoker);
	// listeners_[mapId] = callback;
	listeners_.push_back( new EventListener( type, handler, invoker ) );
}

void EventDispatcher::removeEventListener( const std::string& type, const Object* invoker )
{
	EventDispatcher::EventListeners::iterator iter = listeners_.begin();
	EventDispatcher::EventListeners::iterator endIter = listeners_.end();
	EventListener* el;
	while (iter != endIter)
	{
		el = (*iter);
		if ( el->isEqual( type, invoker ) ) {
			SAFE_RELEASE( *iter );
			listeners_.erase( iter );
			break;
		}
		++iter;
	}
}

bool EventDispatcher::dispatchEvent( Event& event )
{
	event.setSender( this );

	EventDispatcher::EventListeners::iterator iter = listeners_.begin();
	EventDispatcher::EventListeners::iterator endIter = listeners_.end();
	EventListener* el;
	// std::cout << "event dispatched: " << event.getType() << std::endl;
	while (iter != endIter)
	{
		el = (*iter);
		// std::cout << "listener of " << el->getType() << std::endl;
		// std::cout << "comparsion result: " << (el->getType().compare(event.getType()) == 1) << std::endl;
		if (el->getType().compare(event.getType()) == 0)
		{
			if (!el->exec(event))
			{
				return false;
			}
		}
		
		++iter;
	}

	return true;
}
