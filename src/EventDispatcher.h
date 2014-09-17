#ifndef __EVENT_DISPATCHER_H__
#define __EVENT_DISPATCHER_H__

#include <functional>
#include <string>
#include <vector>
// #include <map>
#include <memory>

#include "Object.h"

//class EventListener;
#include "EventListener.h"

class Event;

class EventDispatcher : public Object
{
public:
//	typedef std::map<const std::string, std::function<void(const Event*)>> EventListeners;
	typedef std::vector<EventListener> EventListeners;

public:
	EventDispatcher();
	virtual ~EventDispatcher();

public:
	//Registers an event listener object with an EventDispatcher object so that the listener receives notification of an event.
	// void addEventListener(const std::string& type, const std::function<void(const Event*)>& callback, const Object* invoker);
	void addEventListener( const std::string& type, const EventListener::EventHandler& handler, const Object* invoker );
	// void addEventListener(const std::string& type, bool (T::*handler)(const Event&), T* invoker)
	// 	{
	// 		// std::string mapId = generateId(type, invoker);
	// 		// listeners_[mapId] = callback;
	// 		listeners_.push_back(EventListener<T>(type, handler, invoker));
	// 	}

	
//	void addEventListener(const std::string type, listener:Function, useCapture:Boolean = false, priority:int = 0, useWeakReference:Boolean = false);

	bool dispatchEvent( const Event& event );
//	bool dispatchEvent(std::unique_ptr<Event> event);
// Dispatches an event into the event flow.
// 	EventDispatcher
 	 	
// hasEventListener(type:String):Boolean
// Checks whether the EventDispatcher object has any listeners registered for a specific type of event.
// 	EventDispatcher
 	 	
// removeEventListener(type:String, listener:Function, useCapture:Boolean = false):void
// Removes a listener from the EventDispatcher object.
// 	EventDispatcher
 	 	
// willTrigger(type:String):Boolean
// Checks whether an event listener is registered with this EventDispatcher object or any of its ancestors for the specified event type.

private:
	// std::string generateId(const std::string& str, const Object* invoker);
	
private:
	EventListeners listeners_;
};
#endif
