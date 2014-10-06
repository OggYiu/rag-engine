#include "DisplayObject.h"

#include <iostream>
#include "Kernel.h"
#include "Helper.h"
#include "Texture.h"

DisplayObject::DisplayObject()
	: texture_( nullptr )
	, center_( nullptr )
	, flip_( SDL_FLIP_NONE )
	, blending_( SDL_BLENDMODE_NONE )
	, alpha_( 255 )
	, red_( 255 )
	, green_( 255 )
	, blue_( 255 )
{
}

DisplayObject:: ~DisplayObject()
{
	releaseTexture();
	SAFE_RELEASE( center_ );
}

void DisplayObject::releaseTexture()
{
	if (texture_ != nullptr) {
		SAFE_RELEASE( texture_ );
	}
}

void DisplayObject::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	red_ = red;
	green_ = green;
	blue_ = blue;
	
	if ( texture_ == nullptr ) {
		assert( false && "invalid texture" );
		return;
	}
	
	texture_->setColor( red, green, blue );
}

void DisplayObject::setBlendMode(SDL_BlendMode blending)
{
	blending_ = blending;
	
	if ( texture_ == nullptr ) {
		assert( false && "invalid texture" );
		return;
	}
	texture_->setBlendMode( blending_ );
}

void DisplayObject::setAlpha(Uint8 alpha)
{
	if ( texture_ == nullptr ) {
		assert( false && "invalid texture" );
		return;
	}
	texture_->setAlpha( alpha );
}

void DisplayObject::render()
{
	if ( !isVisible() ) {
		return;
	}
	
	if ( texture_ == nullptr ) {
		return;
	}

	// updateBoundingBox();
	updateBoundingBox_();

	// std::cout << "display obect render: " << std::endl;
	// std::cout << "bouding box: " << boundingBox_.x << ", " << boundingBox_.y << ", " << boundingBox_.w << ", " << boundingBox_.h << std::endl; 
	
	float rotation = transform_.getRot();
	// texture_->render( clipRect_, &boundingBox_, rotation, center_, flip_ );
	texture_->render( nullptr, &boundingBox_, rotation, center_, flip_ );	
}
	
void DisplayObject::setTexture( Texture* texture )
{
	releaseTexture();
	texture_ = texture;
	setSize( texture_->getWidth(), texture->getHeight() );
}

void DisplayObject::updateBoundingBox_()
{
	if ( !dirtyBoundingBox_ ) {
		return;
	}

	DisplayObjectBase::updateBoundingBox_();

	setClipRect( 0, 0, getWidth(), getHeight() );
}
