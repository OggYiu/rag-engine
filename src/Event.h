#ifndef __EVENT_H__
#define __EVENT_H__

#include <memory>
#include <string>

class Event
{
public:
	typedef std::unique_ptr<Event> EventPointer;
	
public:
	Event(const std::string& type);
	virtual ~Event();

public:
	// getter and setter
	const std::string& getType() const;
	
public:
	const std::string type_;
};

#endif
