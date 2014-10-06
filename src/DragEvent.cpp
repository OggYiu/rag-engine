#include "DragEvent.h"

const std::string DragEvent::DRAG_BEGAN( "DRAG_BEGAN" );
const std::string DragEvent::DRAG_MOVE( "DRAG_MOVE" );
const std::string DragEvent::DRAG_ENDED( "DRAG_ENDED" );

DragEvent::DragEvent( const std::string& type )
	: Event( type )
{
}

DragEvent::~DragEvent()
{
}
