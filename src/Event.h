#ifndef __EVENT_H__
#define __EVENT_H__

#include <memory>
#include <string>

#include "SDL.h"

class EventDispatcher;

class Event
{
public:
	typedef std::unique_ptr<Event> EventPointer;
	
public:
	Event( const std::string& type );
    virtual ~Event();

public:
	// getter and setter
	const std::string& getType() const;

	void setSender( EventDispatcher* sender );
	EventDispatcher const* getSender() const { return sender_; }
	Uint32 getTimestamp() const;
	bool isEqual( const std::string& type ) const;
	
public:
	const EventDispatcher* sender_;
	const std::string type_;
	Uint32 timestamp_;
};

#endif
