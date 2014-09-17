#ifndef __EVENTLISTENER_H__
#define __EVENTLISTENER_H__

#include <string>
#include <functional>
#include <memory>
#include "Event.h"

class Object;

class EventListener
{
public:
	// typedef std::function<bool(Event::EventPointer)> EventListenerCallback;
	typedef std::function<bool(const Event&)> EventHandler;
	
public:
	EventListener(const std::string& type, const EventHandler& handler, const Object* invoker);
	virtual ~EventListener();

public:
	bool isEqual(const std::string& type, const Object* invoker) const;
	bool exec(const Event& event);
	
	// getter and setter
	const std::string& getType() const;
	
private:
	const std::string type_;
	const EventHandler handler_;
	const Object* invoker_;
};
#endif
