#include "DisplayObject.h"

#include <iostream>
#include "Kernel.h"
#include "Helper.h"
#include "Texture.h"

DisplayObject::DisplayObject()
	: texture_( nullptr )
	, center_( nullptr )
	, clipRect_( nullptr )
	, renderRect_( nullptr )
	, flip_( SDL_FLIP_NONE )
	, blending_( SDL_BLENDMODE_NONE )
	, alpha_( 255 )
	, red_( 255 )
	, green_( 255 )
	, blue_( 255 )
	, tweener_( Tweener( this ) )
{
}

DisplayObject:: ~DisplayObject()
{
	releaseTexture();
	SAFE_RELEASE( center_ );
	SAFE_RELEASE( clipRect_ );
	SAFE_RELEASE( renderRect_ );
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
//float counter = 0;

void DisplayObject::update(const double dt)
{
	DisplayObjectBase::update( dt );

	tweener_.update( dt );
	
	if ( dirtyRenderPos_ ) {
		dirtyRenderPos_ = false;
		updateRenderPos_();
	}
}

void DisplayObject::render()
{
	if ( texture_ == nullptr ) {
		return;
	}

	texture_->render( clipRect_, renderRect_, rotation_, center_, flip_ );
}
	
void DisplayObject::setTexture( Texture* texture )
{
	releaseTexture();
	texture_ = texture;
	setSize( texture_->getWidth(), texture->getHeight() );
}
	
void DisplayObject::setRenderRect( const int x, const int y, const int w, const int h )
{
	if ( renderRect_ == nullptr ) {
		renderRect_ = new SDL_Rect();
	}
	
	renderRect_->x = x;
	renderRect_->y = y;
	renderRect_->w = w;
	renderRect_->h = h;
}

void DisplayObject::updateRenderPos_()
{
	int modWidth = round( getScaledWidth() );
	int modHeight = round( getScaledHeight() );
	int offsetX = floor( modWidth * anchor_[0] );
	int offsetY = floor( modHeight * anchor_[1] );
 	int renderX = position_[0] - offsetX - ( offsetX % 2 );
	int renderY = position_[1] - offsetY - ( offsetY % 2 );
	int renderW = modWidth;
	int renderH = modHeight;

	setRenderRect( renderX, renderY, renderW, renderH );
}
