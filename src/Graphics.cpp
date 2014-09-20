#include "Graphics.h"

#include <iostream>

#include "Helper.h"
#include "Kernel.h"
#include "Texture.h"

Graphics::Graphics()
	: lineThickness_(1)
	, drawColor_(0xFFFFFFFF)
	, textureDirty_( false )
{
	cursor_[0] = cursor_[1] = 0;
}

Graphics::~Graphics()
{
	clear();
}

void Graphics::setDrawColor(const Uint32 color)
{
	drawColor_ = color;
}

void Graphics::setDrawColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
	drawColor_ = RGBA2Int(r, g, b, a);
}

void Graphics::setDrawAlpha( const Uint8 a )
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 alpha;
	int2RGBA( drawColor_, r, g, b, alpha );
	drawColor_ = RGBA2Int( r, g, b, a );
}

void Graphics::setLineThickness(const int thickness)
{
	lineThickness_ = thickness;
}

SDL_Texture* Graphics::createTexture()
{
	return createTextureFromPrimitives( primitives_ );
}

void Graphics::clear()
{
	PrimitiveIter iter = primitives_.begin();
	PrimitiveIter endIter = primitives_.end();
	while ( iter != endIter )
	{
		delete(*iter);
		++iter;
	}

	primitives_.clear();
	textureDirty_ = true;
}

// Draws a line using the current line style from the current drawing position to (x, y); the current drawing position is then set to (x, y).
// 	Graphics
void Graphics::lineTo( const int x, const int y )
{
	primitives_.push_back( new Line( round( cursor_[0] ), round( cursor_[1] ), x, y, drawColor_ ) );
	cursor_[0] = x; cursor_[1] = y;
	textureDirty_ = true;
}

void Graphics::aalineTo( const int x, const int y )
{
	primitives_.push_back( new AALine( cursor_[0], cursor_[1], x, y, drawColor_ ) );
	cursor_[0] = x; cursor_[1] = y;
	textureDirty_ = true;
}

// Moves the current drawing position to (x, y).
// 	Graphics
void Graphics::moveTo( const int x, const int y )
{
	cursor_[0] = x; cursor_[1] = y;
}

void Graphics::drawPixel(const int x, const int y)
{
	primitives_.push_back(new Pixel(x, y, drawColor_));
	textureDirty_ = true;
}

void Graphics::drawSolidRect(const int x, const int y, const int width, const int height)
{
	primitives_.push_back(new SolidRect(x, y, width, height, drawColor_));
	textureDirty_ = true;
}

void Graphics::drawFrameRect(const int x, const int y, const int width, const int height)
{
	primitives_.push_back(new FrameRect(x, y, width, height, drawColor_));
	textureDirty_ = true;
}

void Graphics::drawRoundSolidRect( const int x, const int y, const int width, const int height, const float radius )
{
	primitives_.push_back( new RoundSolidRect( x, y, width, height, radius, drawColor_ ) );
	textureDirty_ = true;
}

void Graphics::drawRoundFrameRect( const int x, const int y, const int width, const int height, const float radius )
{
	primitives_.push_back( new RoundFrameRect( x, y, width, height, radius, drawColor_ ) );
	textureDirty_ = true;
}

void Graphics::render()
{
	if ( textureDirty_ ) {
		releaseTexture();
		textureDirty_ = false;
		
		SDL_Texture* sdlTexture = nullptr;
		sdlTexture = createTextureFromPrimitives( primitives_ );
		Texture* texture = new Texture( sdlTexture );
		setTexture( texture );
		updateBoundingBox();
		// std::cout << "texture size: " << texture->getWidth() << ", " << texture->getHeight() << std::endl;

		// std::cout << "texture created" << std::endl;
			// texture_->render( clipRect_, &boundingBox_, rotation_, center_, flip_ );
		// std::cout << "bounding box: " << boundingBox_.x << ", " << boundingBox_.y << ", " << boundingBox_.w << ", " << boundingBox_.h << std::endl;
		// PrimitiveIter iter = primitives_.begin();
		// PrimitiveIter endIter = primitives_.end();
		// if ( parent_ != nullptr ) {
		// 	while ( iter != endIter )
		// 	{
		// 		(*iter)->render( parent_->getX(), parent_->getY() );
		// 		++iter;
		// 	}
		// } else {
		// 	while ( iter != endIter )
		// 	{
		// 		(*iter)->render();
		// 		++iter;
		// 	}
		// }
	}

	DisplayObject::render();
}
