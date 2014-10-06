#ifndef __DRAG_EVENT_H__
#define __DRAG_EVENT_H__

#include <string>
#include "Event.h"

class DragEvent : public Event
{
public:
	static const std::string DRAG_BEGAN;
	static const std::string DRAG_MOVE;
	static const std::string DRAG_ENDED;	

public:
	DragEvent( const std::string& type );
	virtual ~DragEvent();
};

#endif
