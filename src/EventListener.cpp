#include "EventListener.h"

EventListener::EventListener(const std::string& type, const EventHandler& handler, const Object* invoker):
	type_(type),
	handler_(handler),
	invoker_(invoker)
{
}

EventListener::~EventListener()
{
}

bool EventListener::isEqual(const std::string& type, const Object* invoker) const
{
	return type.compare( type_ ) == 0 && invoker_ == invoker;
}

bool EventListener::exec(const Event& event)
{
	return handler_(event);
//	return true;
}

const std::string& EventListener::getType() const
{
	return type_;
}
