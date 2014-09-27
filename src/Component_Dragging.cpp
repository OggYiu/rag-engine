#include "Component_Dragging.h"

#include "Kernel.h"
#include "MouseEvent.h"
#include "Helper.h"

const std::string Component_Dragging::NAME = "Drag";

Component_Dragging::Component_Dragging( DisplayObjectBase* owner )
	: Component_Base( Component_Dragging::NAME, owner )
	, isDragging_( false )
{
	mouseOffsetPos_[0] = mouseOffsetPos_[1] = 0;
	
	kernel.getStage().addEventListener( MouseEvent::MOUSE_DOWN, bindEventHandler( &Component_Dragging::mouseEventHandler, this ), this );
	kernel.getStage().addEventListener( MouseEvent::MOUSE_UP, bindEventHandler( &Component_Dragging::mouseEventHandler, this ), this );
	kernel.getStage().addEventListener( MouseEvent::MOUSE_MOVE, bindEventHandler( &Component_Dragging::mouseEventHandler, this ), this );
}

Component_Dragging::~Component_Dragging()
{
	kernel.getStage().removeEventListener( MouseEvent::MOUSE_DOWN, this );
	kernel.getStage().removeEventListener( MouseEvent::MOUSE_UP, this );
	kernel.getStage().removeEventListener( MouseEvent::MOUSE_MOVE, this );
}

bool Component_Dragging::mouseEventHandler( const Event& event )
{
	if ( event.isEqual( MouseEvent::MOUSE_DOWN ) ) {
		isDragging_ = true;
	} else if ( event.isEqual( MouseEvent::MOUSE_UP ) ) {
		isDragging_ = false;
	} else if ( event.isEqual( MouseEvent::MOUSE_MOVE ) ) {
		if ( isDragging_ ) {
			MouseEvent* e = (MouseEvent*)&event;
			float x = e->getMouseX();
			float y = e->getMouseY();
			owner_->transform().setPos( x, y );
		}
	}

	return true;
}

