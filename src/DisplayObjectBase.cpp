#include "DisplayObjectBase.h"

#include <iostream>
#include "Helper.h"
#include "TransformEvent.h"
#include "MouseEvent.h"
#include "DragEvent.h"
#include "Component_Base.h"
#include "Component_Dragging.h"

DisplayObjectBase::DisplayObjectBase()
	: parent_( nullptr )
	, needReleased_( false )
	, clipRect_( nullptr )
	, visible_( true )
	, tweener_( Tweener( this ) )
	, transform_( this )
	, dirtyBoundingBox_( false )	  

{
	transform_.addEventListener( TransformEvent::TRANSFORM_POSITION_CHANGED, bindEventHandler( &DisplayObjectBase::transformEventHandler, this ), this );
	transform_.addEventListener( TransformEvent::TRANSFORM_ROTATION_CHANGED, bindEventHandler( &DisplayObjectBase::transformEventHandler, this ), this );
	transform_.addEventListener( TransformEvent::TRANSFORM_SCALE_CHANGED, bindEventHandler( &DisplayObjectBase::transformEventHandler, this ), this );	
	
	boundingBox_.x = boundingBox_.y = boundingBox_.w = boundingBox_.h = 0;

	transform_.setPos( 0.0f, 0.0f );
	
	size_[0] = 0;
	size_[1] = 0;
	
	anchor_[0] = 0.0f;
	anchor_[1] = 0.0f;

	// setClipRect( 0, 0, 0, 0 );
}

DisplayObjectBase::~DisplayObjectBase()
{
	transform_.removeEventListener( TransformEvent::TRANSFORM_POSITION_CHANGED, this );
	transform_.removeEventListener( TransformEvent::TRANSFORM_ROTATION_CHANGED, this );	
	transform_.removeEventListener( TransformEvent::TRANSFORM_SCALE_CHANGED, this );
}

void DisplayObjectBase::update(const double dt)
{
	EventDispatcher::update( dt );
	tweener_.update( dt );
}

void DisplayObjectBase::handleAddedToParent( DisplayObjectContainer* container )
{
	if ( container == nullptr ||
		 container == parent_ ) {
		logger.getInstance().e( "tag", "invalid display container" );
		return;
	}

	parent_ = container;
	transform_.updateWorldTrans();
	updateBoundingBox();
}

void DisplayObjectBase::handleRemovedFromParent( DisplayObjectContainer* container )
{
	if ( container == nullptr ||
		 container != parent_ ) {
		logger.getInstance().e( "tag", "invalid display container" );
		return;
	}

	parent_ = nullptr;
	transform_.updateWorldTrans();
	updateBoundingBox();
}

void DisplayObjectBase::detachFromParent()
{
	if ( parent_ == nullptr ) {
		logger.getInstance().e( "tag", "nothing to detact from" );
		return;
	}

	parent_->removeChild( this );
}

void DisplayObjectBase::release()
{
	if ( needReleased_ ) {
		logger.w( "display object base", "already released" );
	}
	needReleased_ = true;
}

void DisplayObjectBase::setClipRect( const int x, const int y, const int w, const int h )
{
	clearClipRect();
	// clipRect_ = new SDL_Rect( x, y, width, height );
	clipRect_ = new SDL_Rect();
	clipRect_->x = x;
	clipRect_->y = y;
	clipRect_->w = w;
	clipRect_->h = h;
	// std::cout << "DisplayObjectBase::setClipRect: " << x << ", " << y << ", " << width << ", " << height << std::endl;
}

void DisplayObjectBase::setRenderRect( const int x, const int y, const int w, const int h )
{
	renderRect_.x = x;
	renderRect_.y = y;
	renderRect_.w = w;
	renderRect_.h = h;
}

void DisplayObjectBase::clearClipRect()
{
	SAFE_RELEASE( clipRect_ );
}

void DisplayObjectBase::addComponent( Component_Base* component )
{
	if ( components_[component->getComponentName()] != nullptr ) {
		logger.e( "displayobjectbase", "component already existed" );
		std::cout << "line: " << __LINE__ << ", file: " << __FILE__ << std::endl;
	}
	
	components_[component->getComponentName()] = component;
}

void DisplayObjectBase::removeComponent( const std::string& name )
{
	if ( components_[name] != nullptr ) {
		return;
	}
	
	// std::stringstream ss;
	// ss << "component does not existed: " << name;
	// logger.e( "displayobjectbase", ss.str() );
	// std::cout << "line: " << __LINE__ << ", file: " << __FILE__ << std::endl;
}

void DisplayObjectBase::getSize( int& width, int& height )
{
	width = getWidth();
	height = getHeight();
}

void DisplayObjectBase::setSize( const int width, const int height )
{
	setWidth( width );
	setHeight( height );
	updateBoundingBox();
	
	// std::cout << "setSize" << std::endl;
	// std::cout << width << ", " << height << std::endl << std::endl;
	// std::cout << "updateBoundingBox" << std::endl;
	// std::cout << boundingBox_.x << ", " << boundingBox_.y << ", " << boundingBox_.w << ", " << boundingBox_.h << std::endl << std::endl;
}

void DisplayObjectBase::setWidth( const int width )
{
	size_[0] = width;
	updateBoundingBox();
}

int DisplayObjectBase::getWidth() const
{
	return size_[0];
}

float DisplayObjectBase::getScaledWidth() const
{
	// std::cout << "get scaled width, size_[0]: " << size_[0] << ", getScaleX: " << transform_.getScaleX() << std::endl;
	return size_[0] * transform_.getScaleX();
}

void DisplayObjectBase::setHeight( const int height )
{
	size_[1] = height;
	updateBoundingBox();
}

int DisplayObjectBase::getHeight() const
{
	return size_[1];
}

float DisplayObjectBase::getScaledHeight() const
{
	return size_[1] * transform_.getScaleY();
}

void DisplayObjectBase::setAnchor( const float x, const float y )
{
	setAnchorX( x );
	setAnchorY( y );	
}

void DisplayObjectBase::setAnchorX( const float x )
{
	anchor_[0] = x;
	updateBoundingBox();
}

float DisplayObjectBase::getAnchorX() const
{
	return anchor_[0];
}

void DisplayObjectBase::setAnchorY(const float y)
{
	anchor_[1] = y;
	updateBoundingBox();
}

float DisplayObjectBase::getAnchorY() const
{
	return anchor_[1];
}

bool DisplayObjectBase::isVisible() const
{
	return visible_;
}

void DisplayObjectBase::setVisible(const bool visible)
{
	visible_ = visible;
}

bool DisplayObjectBase::hitTest( const int x, const int y )
{	
	return hitTestPointVSRect( x, y,
							   boundingBox_.x,
							   boundingBox_.y,
							   boundingBox_.w,
							   boundingBox_.h );
}

SDL_Rect& DisplayObjectBase::getBBox()
{
	tryUpdateBoundingBox();
	return boundingBox_;
}
// Eigen::Matrix4f& DisplayObjectBase::getMatrix()
// {
// 	if ( dirtyMatrix_ ) {
// 		dirtyMatrix_ = false;
// 	}
// 	return transform_.getMatrix();
// }

void DisplayObjectBase::updateBoundingBox()
{
	dirtyBoundingBox_ = true;
}

void DisplayObjectBase::tryUpdateBoundingBox()
{
	// std::cout << "try update bounding box" << std::endl;
	updateBoundingBox_();
}

bool DisplayObjectBase::dragEventHandler(const Event& event ATTR_UNUSED )
{
	DragEvent* dragEvent = (DragEvent*)&event;
	DragEvent e( dragEvent->getType(), dragEvent->get_owner() );
	this->dispatchEvent( e );
	return true;
}

// void DisplayObjectBase::setDragEnable( const bool enable )
// {
// 	if ( components_[Component_Dragging::NAME] != nullptr && enable ) {
// 		logger.e( "display object base", "dragging mode already enabled" );
// 		return;
// 	}

// 	if ( enable ) {
// 		addComponent( new Component_Dragging( this, 0, 0, getWidth(), getHeight() ) );
// 	} else {
// 		removeComponent( Component_Dragging::NAME );
// 	}
// }

void DisplayObjectBase::updateBoundingBox_()
{
	if ( !dirtyBoundingBox_ ) {
		return;
	}
	
	dirtyBoundingBox_ = false;
	int modWidth = round( getScaledWidth() );
	int modHeight = round( getScaledHeight() );
	int offsetX = floor( modWidth * anchor_[0] );
	int offsetY = floor( modHeight * anchor_[1] );
	
	boundingBox_.x = transform_.getStageX() - offsetX - ( offsetX % 2 );
	boundingBox_.y = transform_.getStageY() - offsetY - ( offsetY % 2 );
	boundingBox_.w = modWidth;
	boundingBox_.h = modHeight;

	setRenderRect( boundingBox_.x, boundingBox_.y, boundingBox_.w, boundingBox_.h );
	
	// std::cout << "updateBoundingBox" << std::endl;
	// std::cout << "DisplayObjectBase::updateBoundingBox_: " << boundingBox_.x << ", " << boundingBox_.y << ", " << boundingBox_.w << ", " << boundingBox_.h << std::endl << std::endl;
}

bool DisplayObjectBase::transformEventHandler(const Event& event ATTR_UNUSED )
{
	// std::string type = event.getType();
	// if ( type.compare( TransformEvent::TRANSFORM_POSITION_CHANGED ) == 0 ) {
	// 	handleTransformPositionChanged_();
	// } else if ( type.compare( TransformEvent::TRANSFORM_ROTATION_CHANGED ) == 0 ) {
	// 	handleTransformRotationChanged_();
	// } else if ( type.compare( TransformEvent::TRANSFORM_SCALE_CHANGED ) == 0 ) {
	// 	handleTransformScaleChanged_();
	// }
	
	handleTransformEvent();
	
	return true;
}

void DisplayObjectBase::handleTransformEvent()
{
	updateBoundingBox();
}
