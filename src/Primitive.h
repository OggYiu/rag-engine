#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include <iostream>
#include "SDL2_gfxPrimitives.h"
#include "Kernel.h"
#include "Types.h"

struct Primitive
{
	Primitive() {}
	Primitive(const int l_x, const int l_y, const Uint32 l_color)
		: x(l_x)
		, y(l_y)
		, color(l_color)
		{
		}
	
	virtual ~Primitive() {}
	virtual void render( const float offsetX = 0, const float offsetY = 0 ) = 0;

	virtual void getBoundingBox( BBox& box ) = 0;
	
	int x;
	int y;
	Uint32 color;
};

struct Pixel : public Primitive
{
	Pixel(const int l_x, const int l_y, const Uint32 l_color)
		: Primitive(l_x, l_y, l_color)
		{
		}
	
	virtual void render( const float offsetX = 0, const float offsetY = 0 )
		{
			pixelColor(kernel.getRenderer(), offsetX + x, offsetY + y, color);
		}

	virtual void getBoundingBox( BBox& box )
		{
			box.x = x;
			box.y = y;
			box.w = 1;
			box.h = 1;
		}
};

struct Line : public Primitive
{
	Line( const int l_x1, const int l_y1, const int l_x2, const int l_y2, const Uint32 l_color )
		: Primitive(l_x1, l_y1, l_color)
		, x2(l_x2)
		, y2(l_y2)
		{
		}
		  
	int x2;
	int y2;
	
	virtual void render( const float offsetX = 0, const float offsetY = 0 )
		{
			lineColor(kernel.getRenderer(), offsetX + x, offsetY + y, offsetX + x2, offsetY + y2, color);
		}

	virtual void getBoundingBox( BBox& box )
		{
			box.x = x;
			box.y = y;
			box.w = x2 - x;
			box.h = y2 - y;
		}
};

struct AALine : public Line
{
	AALine( const int l_x1, const int l_y1, const int l_x2, const int l_y2, const Uint32 l_color )
		: Line(l_x1, l_y1, l_x2, l_y2, l_color)
		{
		}
	
	virtual void render( const float offsetX = 0, const float offsetY = 0 )
		{
			aalineColor(kernel.getRenderer(), offsetX + x, offsetY + y, offsetX + x2, offsetY + y2, color);
		}
};

struct SolidRect : public Primitive
{
	SolidRect(const int l_x, const int l_y, const int l_width, const int l_height, const Uint32 l_color)
		: Primitive(l_x, l_y, l_color)
		, width(l_width)

		, height(l_height)
		{
		}
	
	virtual void render( const float offsetX = 0, const float offsetY = 0 )
		{
			boxColor(kernel.getRenderer(), offsetX + x, offsetY + y, offsetX + x + width, offsetY + y + height, color);		
		}

	virtual void getBoundingBox( BBox& box )
		{
			box.x = x;
			box.y = y;
			box.w = width;
			box.h = height;
		}

	int width;
	int height;
};

struct FrameRect : public SolidRect
{
	FrameRect(const int l_x, const int l_y, const int l_width, const int l_height, const Uint32 l_color)
		: SolidRect(l_x, l_y, l_width, l_height, l_color)
		{
		}
	
	virtual void render( const float offsetX = 0, const float offsetY = 0 )
		{
			rectangleColor(kernel.getRenderer(), offsetX + x, offsetY + y, offsetX + x + width, offsetY + y + height, color);		
		}
};

struct RoundFrameRect : public SolidRect
{
	RoundFrameRect(const int l_x, const int l_y, const int l_width, const int l_height, const Sint16 l_rad, const Uint32 l_color)
		: SolidRect(l_x, l_y, l_width, l_height, l_color)
		, rad(l_rad)
		{
		}
	
	virtual void render( const float offsetX = 0, const float offsetY = 0 )
		{
			roundedRectangleColor(kernel.getRenderer(), offsetX + x, offsetY + y, offsetX + x + width, offsetY + y + height, rad, color);		
		}

	Sint16 rad;
};

struct RoundSolidRect : public RoundFrameRect
{
	RoundSolidRect(const int l_x, const int l_y, const int l_width, const int l_height, const Sint16 l_rad, const Uint32 l_color)
		: RoundFrameRect(l_x, l_y, l_width, l_height, l_rad, l_color)
		{
		}
	
	virtual void render( const float offsetX = 0, const float offsetY = 0 )
		{
			roundedBoxColor(kernel.getRenderer(), offsetX + x, offsetY + y, offsetX + x + width, offsetY + y + height, rad, color);		
		}
};

#endif
