#ifndef __EVENT_H__
#define __EVENT_H__

#include <memory>
#include <string>

class Event
{
public:
	typedef std::unique_ptr<Event> EventPointer;
	
public:
	Event( const std::string& type, const unsigned int timestamp = 0 );
	virtual ~Event();

public:
	// getter and setter
	const std::string& getType() const;
	unsigned int getTimestamp() const;
	bool isEqual( const std::string& type );
	
public:
	const std::string type_;
	const unsigned int timestamp_;
};

#endif
