#include "Component_Dragging.h"

#include "Kernel.h"
#include "MouseEvent.h"
#include "Helper.h"
#include "DragEvent.h"
#include "DisplayObjectBase.h"

const std::string Component_Dragging::NAME = "Dragging";

Component_Dragging::Component_Dragging( DisplayObjectBase* owner, const int boundX, const int boundY, const int boundWidth, const int boundHeight )
	: Component_Base( Component_Dragging::NAME, owner )
	, isDragging_( false )
{
	mouseOffsetPos_[0] = mouseOffsetPos_[1] = 0;
	lastMousePos_[0] = lastMousePos_[1] = -1;
	
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
	
	this->removeEventListener( DragEvent::DRAG_BEGAN, owner_ );
	this->removeEventListener( DragEvent::DRAG_MOVE, owner_ );
	this->removeEventListener( DragEvent::DRAG_ENDED, owner_ );
}

bool Component_Dragging::mouseEventHandler( const Event& event )
{
	bool isMoveObj = false;
	
	MouseEvent* mouseEvent = (MouseEvent*)&event;
	float mouseX = mouseEvent->getMouseX();
	float mouseY = mouseEvent->getMouseY();

	if ( event.isEqual( MouseEvent::MOUSE_DOWN ) && owner_->hitTest( mouseX, mouseY ) ) {
		// std::cout << "dispatch drag began" << std::endl;
		DragEvent e( DragEvent::DRAG_BEGAN, owner_ );
	    this->dispatchEvent( e );
 		isDragging_ = true;
		isMoveObj = true;
		owner_->transform().worldToLocalPos( mouseX, mouseY, mouseOffsetPos_[0], mouseOffsetPos_[1] );
		// std::cout << "mouse offset pos: " << mouseOffsetPos_[0] << ", " << mouseOffsetPos_[1] << std::endl;
	} else if ( event.isEqual( MouseEvent::MOUSE_UP ) ) {
		// std::cout << "dispatch drag ended" << std::endl;		
		DragEvent e( DragEvent::DRAG_ENDED, owner_ );
	    this->dispatchEvent( e );
		isDragging_ = false;
		lastMousePos_[0] = lastMousePos_[1] = -1;		
	} else if ( event.isEqual( MouseEvent::MOUSE_MOVE ) ) {
		isMoveObj = isDragging_;
	}

	if ( isMoveObj ) {
		Eigen::Vector2f diffMousePos;
		if ( lastMousePos_[0] < 0 || lastMousePos_[1] < 0 ) {
			lastMousePos_[0] = mouseX;
			lastMousePos_[1] = mouseY;
		}
		diffMousePos[0] = mouseX - lastMousePos_[0];
		diffMousePos[1] = mouseY - lastMousePos_[1];
		
		float localX, localY;
		owner_->transform().getPos( localX, localY );
			
		float oldX, oldY, newX, newY;
		oldX = localX;
		oldY = localY;
		newX = localX + diffMousePos[0];
		newY = localY + diffMousePos[1];
		
		// std::cout << "mouse pos: " << mouseX << ", " << mouseY << ", lastMousePos: " << lastMousePos_[0] << ", " << lastMousePos_[1] << std::endl;
		// std::cout << "old pos: " << oldX << ", " << oldY << ", new pos: " << newX << ", " << newY << std::endl;

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
			DragEvent e( DragEvent::DRAG_MOVE, owner_ );
			this->dispatchEvent( e );
			// std::cout << "dispatch drag move" << std::endl;			
		}
		
		lastMousePos_[0] = mouseX;
		lastMousePos_[1] = mouseY;
	}
	
	return true;
}

