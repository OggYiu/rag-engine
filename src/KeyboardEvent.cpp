#include "KeyboardEvent.h"

const std::string KeyboardEvent::KEY_DOWN("KEY_DOWN");
const std::string KeyboardEvent::KEY_UP("KEY_UP");
	
KeyboardEvent::KeyboardEvent( const std::string& type, const SDL_Keycode keycode, const int mod, const int repeat )
	: Event( type )
	, keycode_( keycode )
	, mod_( mod )
	, repeat_( repeat )
{
}

