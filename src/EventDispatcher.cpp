#include "EventDispatcher.h"

#include <iostream>
#include <sstream>

#include "Event.h"
#include "EventListener.h"

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
//	std::cout << "eventdispatcher decon" << std::endl;
}

void EventDispatcher::addEventListener( const std::string& type, const EventListener::EventHandler& handler, const Object* invoker )
{
	// std::string mapId = generateId(type, invoker);
	// listeners_[mapId] = callback;
	listeners_.push_back( EventListener( type, handler, invoker ) );
}

bool EventDispatcher::dispatchEvent(const Event& event)

{
	EventDispatcher::EventListeners::iterator iter = listeners_.begin();
	EventDispatcher::EventListeners::iterator endIter = listeners_.end();
	EventListener* el;
	// std::cout << "event dispatched: " << event.getType() << std::endl;
	while (iter != endIter)
	{
		el = &(*iter);
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

// std::string EventDispatcher::generateId(const std::string& str, const Object* invoker)
// {
// 	std::stringstream id;
// 	id << invoker->getId() << ":" << str.c_str();
// 	std::string mapId = "";
// 	id >> mapId;
// 	return mapId;
// }
