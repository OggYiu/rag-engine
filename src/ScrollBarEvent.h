#ifndef __SCROLL_BAR_EVENT_H__
#define __SCROLL_BAR_EVENT_H__

#include "Event.h"

class GUI_VScrollBar;

class ScrollBarEvent : public Event
{
public:
	static const std::string SCROLL_BAR_VALUE_CHANGED;

public:
	ScrollBarEvent( const std::string& type, GUI_VScrollBar* scrollBar );
	virtual ~ScrollBarEvent();
	
public:
	GUI_VScrollBar* getScrollBar() { return scrollBar_; }

protected:
	GUI_VScrollBar* scrollBar_;
};

#endif
