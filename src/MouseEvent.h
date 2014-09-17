#ifndef __MOUSE_EVENT_H__
#define __MOUSE_EVENT_H__

#include <string>

#include "Event.h"

class MouseEvent : public Event
{
public:
	static const std::string MOUSE_MOVE;
	static const std::string MOUSE_DOWN;
	static const std::string MOUSE_UP;
	static const std::string MOUSE_HOVER;
	static const std::string MOUSE_LOSE_HOVER;

public:
	MouseEvent(const std::string& type, const int x, const int y);

	// getter and setter
	int getMouseX() { return mouseX_; }
	int getMouseY() { return mouseY_; }
	
private:
	int mouseX_;
	int mouseY_;
};
// const std::string MouseEvent::MOUSE_MOVE("MOUSE_MOVE");
// const std::string MouseEvent::MOUSE_CLICK("MOUSE_CLICK");
#endif
