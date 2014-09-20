#include "DisplayObjectBase.h"

#include <iostream>
#include "Helper.h"

DisplayObjectBase::DisplayObjectBase()
	: parent_( nullptr )
	, rotation_( 0.0f )
	, dirtyBoundingBox_( false )
	, visible_( true )
	, tweener_( Tweener( this ) )
{
	boundingBox_.x = boundingBox_.y = boundingBox_.w = boundingBox_.h = 0;

	localPos_[0] = localPos_[1] = 0.0f;
	stagePos_[0] = stagePos_[1] = 0.0f;	
	
	size_[0] = 0;
	size_[1] = 0;
	
	scale_[0] = 1.0f;
	scale_[1] = 1.0f;
	
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
	dirtyBoundingBox_ = true;
}

void DisplayObjectBase::update(const double dt)
{
	EventDispatcher::update( dt );

	tweener_.update( dt );
	
	if ( dirtyBoundingBox_ ) {
		// dirtyBoundingBox_ = false;
		updateBoundingBox();
	}
}

void DisplayObjectBase::refreshPos()
{
	setPos( localPos_[0], localPos_[1] );
}

void DisplayObjectBase::setPos( const float x, const float y)
{
	setX( x );
	setY( y );	
}

void DisplayObjectBase::setX( const float x )
{
	float mod = parent_ != nullptr? parent_->getX() + parent_->getWidth() * parent_->getAnchorX() : 0;
	localPos_[0] = x;
	stagePos_[0] = x + mod;
	dirtyBoundingBox_ = true;
}

void DisplayObjectBase::setY( const float y )
{
	float mod = parent_ != nullptr? parent_->getY() + parent_->getHeight() * parent_->getAnchorY() : 0;
	localPos_[1] = y;
	stagePos_[1] = y + mod;
	dirtyBoundingBox_ = true;	
}
void DisplayObjectBase::setSize( const int width, const int height )
{
	setWidth( width );
	setHeight( height );
}

void DisplayObjectBase::setWidth( const int width )
{
	size_[0] = width;
	dirtyBoundingBox_ = true;
}

int DisplayObjectBase::getWidth() const
{
	return size_[0];
}

float DisplayObjectBase::getScaledWidth() const
{
	return size_[0] * scale_[0];
}

void DisplayObjectBase::setHeight( const int height )
{
	size_[1] = height;
	dirtyBoundingBox_ = true;
}

int DisplayObjectBase::getHeight() const
{
	return size_[1];
}

float DisplayObjectBase::getScaledHeight() const
{
	return size_[1] * scale_[1];
}


void DisplayObjectBase::setScaleX( const float x )
{
	scale_[0] = x;
	dirtyBoundingBox_ = true;	
}

float DisplayObjectBase::getScaleX() const
{
	return scale_[0];
}

void DisplayObjectBase::setScaleY( const float y )
{
	scale_[1] = y;
	dirtyBoundingBox_ = true;	
}

float DisplayObjectBase::getScaleY() const
{
	return scale_[1];
}

void DisplayObjectBase::setAnchor( const float x, const float y )
{
	setAnchorX( x );
	setAnchorY( y );	
}

void DisplayObjectBase::setAnchorX( const float x )
{
	anchor_[0] = x;
	dirtyBoundingBox_ = true;		
}

float DisplayObjectBase::getAnchorX() const
{
	return anchor_[0];
}

void DisplayObjectBase::setAnchorY(const float y)
{
	anchor_[1] = y;
	dirtyBoundingBox_ = true;		
}

float DisplayObjectBase::getAnchorY() const
{
	return anchor_[1];
}

void DisplayObjectBase::setRotation(const float rotation)
{
	rotation_ = rotation;
}

float DisplayObjectBase::getRotation() const
{
	return rotation_;
}

bool DisplayObjectBase::isVisible() const
{
	return visible_;
}

void DisplayObjectBase::setVisible(const bool visible)
{
	visible_ = visible;
}

bool DisplayObjectBase::hitTest( const int x, const int y ) const
{
	// return hitTestPointVSRect( x, y,
	// 						   localPos_[0] - ( size_[0] * scale_[0] ) * anchor_[0],
	// 						   localPos_[1] - ( size_[1] * scale_[1] ) * anchor_[1],
	// 						   size_[0] * scale_[0],
	// 						   size_[1] * scale_[1] );

	return hitTestPointVSRect( x, y,
							   boundingBox_.x,
							   boundingBox_.y,
							   boundingBox_.w,
							   boundingBox_.h );
}

void DisplayObjectBase::updateBoundingBox()
{
	dirtyBoundingBox_ = false;
	
	int modWidth = round( getScaledWidth() );
	int modHeight = round( getScaledHeight() );
	int offsetX = floor( modWidth * anchor_[0] );
	int offsetY = floor( modHeight * anchor_[1] );
 	boundingBox_.x = stagePos_[0] - offsetX - ( offsetX % 2 );
	boundingBox_.y = stagePos_[1] - offsetY - ( offsetY % 2 );
	boundingBox_.w = modWidth;
	boundingBox_.h = modHeight;
//	setRenderRect( renderX, renderY, renderW, renderH );
}
