#ifndef __KEYBOARD_EVENT_H__
#define __KEYBOARD_EVENT_H__

#include <string>
#include <iostream>
#include "SDL.h"
#include "Event.h"

class KeyboardEvent : public Event
{
public:
	static const std::string KEY_DOWN;
	static const std::string KEY_UP;

public:
	KeyboardEvent( const std::string& type, const unsigned int timestamp, const SDL_Keycode keycode, const int mod, const int repeat );

	SDL_Keycode getKeycode() const { return keycode_; }
	int getMod() const { return mod_; }
	int getRepeat() const { return repeat_; }

	friend std::ostream &operator<<( std::ostream &out, const KeyboardEvent& obj )
		{
			out << "<KeyboardEvent object>" << std::endl;
			out << "\tkeycode: " << obj.getKeycode() << std::endl;
			out << "\tmod: " << obj.getMod() << std::endl;
			out << "\trepeat: " << obj.getRepeat() << std::endl;
			return out;
		}
private:
	SDL_Keycode keycode_; // key code reference : https://wiki.libsdl.org/SDLKeycodeLookup
	int mod_;
	int repeat_;
};
// const std::string MouseEvent::MOUSE_MOVE("MOUSE_MOVE");
// const std::string MouseEvent::MOUSE_CLICK("MOUSE_CLICK");
#endif
