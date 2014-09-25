#include "DisplayObjectBase.h"

#include <iostream>
#include "Helper.h"
#include "TransformEvent.h"

DisplayObjectBase::DisplayObjectBase()
	: parent_( nullptr )
	  // , rotation_( 0.0f )
	, dirtyBoundingBox_( false )
	, visible_( true )
	, tweener_( Tweener( this ) )
	, transform_( this )
{
	transform_.addEventListener( TransformEvent::TRANSFORM_POSITION_CHANGED, bindEventHandler( &DisplayObjectBase::transformEventHandler, this ), this );
	transform_.addEventListener( TransformEvent::TRANSFORM_ROTATION_CHANGED, bindEventHandler( &DisplayObjectBase::transformEventHandler, this ), this );
	transform_.addEventListener( TransformEvent::TRANSFORM_SCALE_CHANGED, bindEventHandler( &DisplayObjectBase::transformEventHandler, this ), this );	
	
	boundingBox_.x = boundingBox_.y = boundingBox_.w = boundingBox_.h = 0;

	transform_.setPos( 0.0f, 0.0f );
	// localPos_[0] = localPos_[1] = 0.0f;
	// stagePos_[0] = stagePos_[1] = 0.0f;	
	
	size_[0] = 0;
	size_[1] = 0;
	
	// scale_[0] = 1.0f;
	// scale_[1] = 1.0f;
	
	anchor_[0] = 0.0f;
	anchor_[1] = 0.0f;
}

DisplayObjectBase::~DisplayObjectBase()
{
//	std::cout << "displayobjectbase decon" << std::endl;
}

void DisplayObjectBase::setParent( DisplayObjectContainer* parent )
{
	parent_ = parent;
	transform_.updateWorldTrans();
	updateBoundingBox();
}

void DisplayObjectBase::update(const double dt)
{
	EventDispatcher::update( dt );
	tweener_.update( dt );
}

// void DisplayObjectBase::setPos( const float x, const float y)
// {
// 	setX( x );
// 	setY( y );	
// }

// void DisplayObjectBase::setX( const float x )
// {
// 	transform_.setX( x );
// 	updateBoundingBox();
// }

// void DisplayObjectBase::setY( const float y )
// {
// 	float mod = parent_ != nullptr? parent_->transform().getY() + parent_->getHeight() * parent_->getAnchorY() : 0;
// 	localPos_[1] = y;
// 	stagePos_[1] = y + mod;
// 	dirtyBoundingBox_ = true;	
// }

void DisplayObjectBase::setSize( const int width, const int height )
{
	setWidth( width );
	setHeight( height );
	
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
	updateBoundingBox_();
}

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

	// std::cout << "updateBoundingBox" << std::endl;
	// std::cout << boundingBox_.x << ", " << boundingBox_.y << ", " << boundingBox_.w << ", " << boundingBox_.h << std::endl << std::endl;
}

bool DisplayObjectBase::transformEventHandler( const Event& event )
{
	std::string type = event.getType();
	// TransformEvent* e = (TransformEvent*)(&event);

	// std::cout << "type got : " << type << std::endl;
	if ( type.compare( TransformEvent::TRANSFORM_POSITION_CHANGED ) == 0 ) {
		handleTransformPositionChanged_();
	} else if ( type.compare( TransformEvent::TRANSFORM_ROTATION_CHANGED ) == 0 ) {
		handleTransformRotationChanged_();
	} else if ( type.compare( TransformEvent::TRANSFORM_SCALE_CHANGED ) == 0 ) {
		handleTransformScaleChanged_();
	}

	return true;
}

void DisplayObjectBase::handleTransformPositionChanged_()
{
	updateBoundingBox();
}

void DisplayObjectBase::handleTransformRotationChanged_()
{
	updateBoundingBox();
}

void DisplayObjectBase::handleTransformScaleChanged_()
{
	updateBoundingBox();
}
