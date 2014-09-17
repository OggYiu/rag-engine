#include "Graphics.h"

#include <iostream>

#include "Helper.h"
#include "Kernel.h"

Graphics::Graphics()
	: lineThickness_(1)
	, color_(0xFFFFFFFF)
{
//	std::cout << "i am graphics and my id is " << this->getId() << std::endl;
}

Graphics::~Graphics()
{
	clear();
}

void Graphics::setColor(const Uint32 color)
{
	color_ = color;
}

void Graphics::setColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
	color_ = RGBA2Int(r, g, b, a);
}

void Graphics::setAlpha(const Uint8 a)
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 alpha;
	int2RGBA(color_, r, g, b, alpha);
	color_ = RGBA2Int(r, g, b, a);
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
}

// Draws a line using the current line style from the current drawing position to (x, y); the current drawing position is then set to (x, y).
// 	Graphics
void Graphics::lineTo( const int x, const int y )
{
	primitives_.push_back( new Line( round( cursor_[0] ), round( cursor_[1] ), x, y, color_ ) );
	cursor_[0] = x; cursor_[1] = y;
}

void Graphics::aalineTo( const int x, const int y )
{
	primitives_.push_back( new AALine( cursor_[0], cursor_[1], x, y, color_ ) );
	cursor_[0] = x; cursor_[1] = y;
}

// Moves the current drawing position to (x, y).
// 	Graphics
void Graphics::moveTo( const int x, const int y )
{
	cursor_[0] = x; cursor_[1] = y;
}

void Graphics::drawPixel(const int x, const int y)
{
	primitives_.push_back(new Pixel(x, y, color_));
}

void Graphics::drawSolidRect(const int x, const int y, const int width, const int height)
{
	primitives_.push_back(new SolidRect(x, y, width, height, color_));
}

void Graphics::drawFrameRect(const int x, const int y, const int width, const int height)
{
	primitives_.push_back(new FrameRect(x, y, width, height, color_));
}

void Graphics::drawRoundSolidRect( const int x, const int y, const int width, const int height, const float radius )
{
	primitives_.push_back( new RoundSolidRect( x, y, width, height, radius, color_ ) );
}

void Graphics::drawRoundFrameRect( const int x, const int y, const int width, const int height, const float radius )
{
	primitives_.push_back( new RoundFrameRect( x, y, width, height, radius, color_ ) );
}

void Graphics::render()
{
//	SDL_RenderCopyEx(kernel.getRenderer(), texture_, clipRect_, renderRect_, rotation_, center_, flip_);

//	std::cout << "graphics::redner" << std::endl;
	PrimitiveIter iter = primitives_.begin();
	PrimitiveIter endIter = primitives_.end();

	if ( parent_ != nullptr ) {
//		std::cout << "parent: " << parent_ << std::endl;
//		std::cout << "parent pos: " << parent_->getX() << ", " << parent_->getY() << std::endl;
		while ( iter != endIter )
		{
			(*iter)->render( parent_->getX(), parent_->getY() );
			++iter;
		}
	} else {
		while ( iter != endIter )
		{
			(*iter)->render();
			++iter;
		}
	}
}
