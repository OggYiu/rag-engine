#include "DisplayObjectBase.h"

#include <iostream>
#include "Helper.h"

DisplayObjectBase::DisplayObjectBase():
	parent_(nullptr),
	rotation_(0.0f),	
	dirtyRenderPos_(false),
	visible_(true)

{
	position_[0] = 0.0f;
	position_[1] = 0.0f;
	
	size_[0] = 0;
	size_[1] = 0;
	
	scale_[0] = 1.0f;
	scale_[1] = 1.0f;
	
	anchor_[0] = 0.5f;
	anchor_[1] = 0.5f;
}

DisplayObjectBase::~DisplayObjectBase()
{
//	std::cout << "displayobjectbase decon" << std::endl;
}

void DisplayObjectBase::setParent( DisplayObjectContainer* parent )
{
	parent_ = parent;
	dirtyRenderPos_ = true;
}

void DisplayObjectBase::setPosition( const float x, const float y)
{
	setX( x );
	setY( y );	
}

void DisplayObjectBase::setX( const float x )
{
	position_[0] = x;
	dirtyRenderPos_ = true;
}

float DisplayObjectBase::getX() const
{
	return position_[0];
}

void DisplayObjectBase::setY( const float y )
{
	position_[1] = y;
	dirtyRenderPos_ = true;	
}

float DisplayObjectBase::getY() const
{
	return position_[1];
}

void DisplayObjectBase::setSize( const int width, const int height )
{
	setWidth( width );
	setHeight( height );
}

void DisplayObjectBase::setWidth( const int width )
{
	size_[0] = width;
	dirtyRenderPos_ = true;
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
	dirtyRenderPos_ = true;
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
	dirtyRenderPos_ = true;	
}

float DisplayObjectBase::getScaleX() const
{
	return scale_[0];
}

void DisplayObjectBase::setScaleY( const float y )
{
	scale_[1] = y;
	dirtyRenderPos_ = true;	
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
	dirtyRenderPos_ = true;		
}

float DisplayObjectBase::getAnchorX() const
{
	return anchor_[0];
}

void DisplayObjectBase::setAnchorY(const float y)
{
	anchor_[1] = y;
	dirtyRenderPos_ = true;		
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
	return hitTestPointVSRect(x, y, position_[0] - (size_[0] * scale_[0]) * anchor_[0], position_[1] - (size_[1] * scale_[1]) * anchor_[1], size_[0] * scale_[0], size_[1] * scale_[1]);
}
