#include "KeyboardEvent.h"

const std::string KeyboardEvent::KEY_DOWN("KEY_DOWN");
const std::string KeyboardEvent::KEY_UP("KEY_UP");
	
KeyboardEvent::KeyboardEvent( const std::string& type, const unsigned int timestamp, const SDL_Keycode keycode, const int mod, const int repeat )
	: Event( type, timestamp )
	, keycode_( keycode )
	, mod_( mod )
	, repeat_( repeat )
{
}

