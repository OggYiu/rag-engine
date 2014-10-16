#include "DragEvent.h"

const std::string DragEvent::DRAG_BEGAN( "DRAG_BEGAN" );
const std::string DragEvent::DRAG_MOVE( "DRAG_MOVE" );
const std::string DragEvent::DRAG_ENDED( "DRAG_ENDED" );

DragEvent::DragEvent( const std::string& type, DisplayObjectBase* owner )
	: Event( type )
	, owner_( owner )
{
}

DragEvent::~DragEvent()
{
}

DisplayObjectBase* DragEvent::get_owner()
{
	return owner_;
}
