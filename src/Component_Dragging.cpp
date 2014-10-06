#include "Component_Dragging.h"

#include "Kernel.h"
#include "MouseEvent.h"
#include "Helper.h"
#include "DragEvent.h"
#include "DisplayObjectBase.h"

const std::string Component_Dragging::NAME = "Drag";

Component_Dragging::Component_Dragging( DisplayObjectBase* owner, const int boundX, const int boundY, const int boundWidth, const int boundHeight )
	: Component_Base( Component_Dragging::NAME, owner )
	, isDragging_( false )
{
	mouseOffsetPos_[0] = mouseOffsetPos_[1] = 0;
	
	kernel.getStage().addEventListener( MouseEvent::MOUSE_DOWN, bindEventHandler( &Component_Dragging::mouseEventHandler, this ), this );
	kernel.getStage().addEventListener( MouseEvent::MOUSE_UP, bindEventHandler( &Component_Dragging::mouseEventHandler, this ), this );
	kernel.getStage().addEventListener( MouseEvent::MOUSE_MOVE, bindEventHandler( &Component_Dragging::mouseEventHandler, this ), this );

	this->addEventListener( DragEvent::DRAG_BEGAN, bindEventHandler( &DisplayObjectBase::dragEventHandler, owner_ ), owner_ );
	this->addEventListener( DragEvent::DRAG_MOVE, bindEventHandler( &DisplayObjectBase::dragEventHandler, owner_ ), owner_ );	
	this->addEventListener( DragEvent::DRAG_ENDED, bindEventHandler( &DisplayObjectBase::dragEventHandler, owner_ ), owner_ );
	
	bound_ = { boundX, boundY, boundWidth, boundHeight };
}

Component_Dragging::~Component_Dragging()
{
	kernel.getStage().removeEventListener( MouseEvent::MOUSE_DOWN, this );
	kernel.getStage().removeEventListener( MouseEvent::MOUSE_UP, this );
	kernel.getStage().removeEventListener( MouseEvent::MOUSE_MOVE, this );
	
	this->removeEventListener( DragEvent::DRAG_BEGAN, this );
	this->removeEventListener( DragEvent::DRAG_MOVE, this );
	this->removeEventListener( DragEvent::DRAG_ENDED, this );
}

bool Component_Dragging::mouseEventHandler( const Event& event )
{
	bool isMoveObj = false;
	
	MouseEvent* mouseEvent = (MouseEvent*)&event;
	float mouseX = mouseEvent->getMouseX();
	float mouseY = mouseEvent->getMouseY();

	if ( event.isEqual( MouseEvent::MOUSE_DOWN ) && owner_->hitTest( mouseX, mouseY ) ) {
		DragEvent e( DragEvent::DRAG_BEGAN );
	    this->dispatchEvent( e );
		isDragging_ = true;
		isMoveObj = true;
		owner_->transform().worldToLocalPos( mouseX, mouseY, mouseOffsetPos_[0], mouseOffsetPos_[1] );
		// std::cout << "mouse offset pos: " << mouseOffsetPos_[0] << ", " << mouseOffsetPos_[1] << std::endl;
	} else if ( event.isEqual( MouseEvent::MOUSE_UP ) ) {
		DragEvent e( DragEvent::DRAG_ENDED );
	    this->dispatchEvent( e );
		isDragging_ = false;
	} else if ( event.isEqual( MouseEvent::MOUSE_MOVE ) ) {
		isMoveObj = isDragging_;
	}

	if ( isMoveObj ) {
		float localX, localY;
		owner_->transform().worldToLocalPos( mouseX, mouseY, localX, localY );
			
		float oldX, oldY, newX, newY;
		oldX = localX;
		oldY = localY;
		newX = localX - mouseOffsetPos_[0];
		newY = localY - mouseOffsetPos_[1];

		if ( newX < bound_.x1() ) {
			newX = bound_.x1();
		}
			
		if ( newY < bound_.y1() ) {
			newY = bound_.y1();
		}
			
		if ( newX > bound_.x2() ) {
			newX = bound_.x2();
		}
			
		if ( newY > bound_.y2() ) {
			newY = bound_.y2();
		}
			
		owner_->transform().setPos( newX, newY );

		bool equal = isEqual( oldX, newX ) && isEqual( oldY, newY );
		if ( !equal ) {
			DragEvent e( DragEvent::DRAG_MOVE );
			this->dispatchEvent( e );
		}
	}
	
	return true;
}

