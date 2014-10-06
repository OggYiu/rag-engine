#include "ScrollBarEvent.h"

const std::string ScrollBarEvent::SCROLL_BAR_VALUE_CHANGED( "SCROLL_BAR_VALUE_CHANGED" );

ScrollBarEvent::ScrollBarEvent( const std::string& type, GUI_VScrollBar* scrollBar )
	: Event( type )
	, scrollBar_( scrollBar )
{
}

ScrollBarEvent::~ScrollBarEvent()
{
}
