#include "DisplayObjectBase.h"

#include <iostream>
#include "Helper.h"
#include "TransformEvent.h"
#include "MouseEvent.h"
#include "DragEvent.h"
#include "Component_Base.h"
#include "Component_Dragging.h"

const std::string DisplayObjectBase::LOG_TAG = "DisplayObjectBase";

DisplayObjectBase::DisplayObjectBase()
	: parent_( nullptr )
	, needReleased_( false )
	// , clipRect_( nullptr )
	// , center_( nullptr )
	, visible_( true )
	, tweener_( Tweener( this ) )
	, transform_( this )
	// , dirtyBoundingBox_( false )	  

{
	transform_.addEventListener( TransformEvent::TRANSFORM_POSITION_CHANGED, bindEventHandler( &DisplayObjectBase::transformEventHandler, this ), this );
	transform_.addEventListener( TransformEvent::TRANSFORM_ROTATION_CHANGED, bindEventHandler( &DisplayObjectBase::transformEventHandler, this ), this );
	transform_.addEventListener( TransformEvent::TRANSFORM_SCALE_CHANGED, bindEventHandler( &DisplayObjectBase::transformEventHandler, this ), this );	
	
	boundingBox_.x = boundingBox_.y = boundingBox_.w = boundingBox_.h = 0;

	transform_.setPos( 0.0f, 0.0f );
	
	// size_[0] = 0;
	// size_[1] = 0;

	setCenter( 0.5f, 0.5f );
	setAnchor( 0.0f, 0.0f );
	// anchor_[0] = 0.0f;
	// anchor_[1] = 0.0f;

	setClipRect( 0, 0, 0, 0 );
}

DisplayObjectBase::~DisplayObjectBase()
{
	transform_.removeEventListener( TransformEvent::TRANSFORM_POSITION_CHANGED, this );
	transform_.removeEventListener( TransformEvent::TRANSFORM_ROTATION_CHANGED, this );	
	transform_.removeEventListener( TransformEvent::TRANSFORM_SCALE_CHANGED, this );
	// SAFE_RELEASE( clipRect_ );
	// SAFE_RELEASE( center_ );
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
	updateBoundingBox_();
}

void DisplayObjectBase::handleRemovedFromParent( DisplayObjectContainer* container )
{
	if ( container == nullptr ||
		 container != parent_ ) {
		logger.getInstance().e( "tag", "invalid display container" );
		return;
	}

	parent_ = nullptr;
	updateBoundingBox_();
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

void DisplayObjectBase::setRenderRect( const int x, const int y, const int w, const int h )
{
	renderRect_.x = x;
	renderRect_.y = y;
	renderRect_.w = w;
	renderRect_.h = h;
}

void DisplayObjectBase::setCenter( const float x, const float y )
{
	// SAFE_RELEASE( center_ );
	// center_ = new SDL_Point();
	centerPoint_.x() = x;
	centerPoint_.y() = y;
	sdlCenter_.x = round( getWidth() * getCenterPointX() );
	sdlCenter_.y = round( getHeight() * getCenterPointY() );
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
}

void DisplayObjectBase::setWidth( int width )
{
	if ( width < 0 ) {
		width = 0;
		logger.e( DisplayObjectBase::LOG_TAG, "trying to set width to small than 0" );
	}
	setClipRect( 0, 0, width, getHeight() );
	updateBoundingBox_();
}

int DisplayObjectBase::getWidth() const
{
	return clipRect_.w * transform_.getScaleX();;
}

// float DisplayObjectBase::getScaledWidth() const
// {
// 	return getWidth() * transform_.getScaleX();
// }

void DisplayObjectBase::setHeight( int height )
{
	if ( height < 0 ) {
		height = 0;
		logger.e( DisplayObjectBase::LOG_TAG, "trying to set height to small than 0" );
	}
	setClipRect( 0, 0, getWidth(), height );
	updateBoundingBox_();
}

int DisplayObjectBase::getHeight() const
{
	return clipRect_.h * transform_.getScaleY();
}

// float DisplayObjectBase::getScaledHeight() const
// {
// 	return getHeight() * transform_.getScaleY();
// }

void DisplayObjectBase::setClipRect( const int x, const int y, const int w, const int h )
{
	clipRect_.x = x;
	clipRect_.y = y;
	clipRect_.w = w;
	clipRect_.h = h;
}

void DisplayObjectBase::setAnchor( const float x, const float y )
{
	setAnchorX( x );
	setAnchorY( y );	
}

void DisplayObjectBase::setAnchorX( const float x )
{
	anchor_[0] = x;
	
	updateBoundingBox_();
}

float DisplayObjectBase::getAnchorX() const
{
	return anchor_[0];
}

void DisplayObjectBase::setAnchorY(const float y)
{
	anchor_[1] = y;
	updateBoundingBox_();
}

float DisplayObjectBase::getAnchorY() const
{
	return anchor_[1];
}

float DisplayObjectBase::getCenterPointX()
{
	return centerPoint_.x();
}

float DisplayObjectBase::getCenterPointY()
{
	return centerPoint_.y();
}

void DisplayObjectBase::getCenterPoint( float& x, float& y )
{
	x = getCenterPointX();
	y = getCenterPointY();
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

// void DisplayObjectBase::updateBoundingBox()
// {
// 	dirtyBoundingBox_ = true;
// }

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

void DisplayObjectBase::updateBoundingBox_()
{
	// if ( !dirtyBoundingBox_ ) {
	// 	return;
	// }
	
	// dirtyBoundingBox_ = false;
	
	int modWidth, modHeight, offsetX, offsetY;
	modWidth = round( getWidth() );
	modHeight = round( getHeight() );
	offsetX = floor( modWidth * anchor_[0] );
	offsetY = floor( modHeight * anchor_[1] );
	
	boundingBox_.x = transform_.getStageX() + offsetX + ( offsetX % 2 );
	boundingBox_.y = transform_.getStageY() + offsetY + ( offsetY % 2 );
	boundingBox_.w = modWidth;
	boundingBox_.h = modHeight;

	setRenderRect( boundingBox_.x, boundingBox_.y, boundingBox_.w, boundingBox_.h );
}

void DisplayObjectBase::handleScaleChanged_()
{
	// std::cout << "handle scale changed" << std::endl;
	setCenter( getCenterPointX(), getCenterPointY() );
}

bool DisplayObjectBase::transformEventHandler(const Event& event ATTR_UNUSED )
{
	std::string type = event.getType();
	if ( type.compare( TransformEvent::TRANSFORM_POSITION_CHANGED ) == 0 ) {
		// handleTransformPositionChanged_();
	} else if ( type.compare( TransformEvent::TRANSFORM_ROTATION_CHANGED ) == 0 ) {
		// handleTransformRotationChanged_();
	} else if ( type.compare( TransformEvent::TRANSFORM_SCALE_CHANGED ) == 0 ) {
		// handleTransformScaleChanged_();
		handleScaleChanged_();
	}
	
	handleTransformEvent();
	
	return true;
}

void DisplayObjectBase::handleTransformEvent()
{
	updateBoundingBox_();
}
