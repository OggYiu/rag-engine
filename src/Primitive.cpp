#include "Primitive.h"

///////////////////////////////////
// Line

Line::	Line( const int l_x1, const int l_y1, const int l_x2, const int l_y2, const Uint32 l_color )
	: Primitive(l_x1, l_y1, l_color)
	, x2(l_x2)
	, y2(l_y2)
{
}

	
void Line::render( const float offsetX, const float offsetY )
{
	lineColor(kernel.getRenderer(), offsetX + x, offsetY + y, offsetX + x2, offsetY + y2, color);
}

BBox Line::getBoundingBox()
{
	// std::cout << "pos: " << x << ", " << y << ", " << x2 << ", " << y2 << std::endl;
	int w = x2 - x;
	if ( w <= 0 ) {
		w = 1;
	}
			
	int h = y2 - y;
	if ( h <= 0 ) {
		h = 1;
	}
	// std::cout << "result: " << x << ", " << y << ", " << w << ", " << h << std::endl;
	return BBox( x, y, w, h );
}

///////////////////////////////////
// FrameCircle
FrameCircle::FrameCircle( const int l_x, const int l_y, const Sint16 l_rad, const Uint32 l_color )
	: Primitive(l_x, l_y, l_color)
	, rad( l_rad )
{
}

void FrameCircle::render( const float offsetX, const float offsetY )
{
	circleColor( kernel.getRenderer(), offsetX + x, offsetY + y, rad, color );
}

BBox FrameCircle::getBoundingBox()
{
	// std::cout << "x: " << x << ", " << y << ", " << rad << std::endl;
	// return BBox( x, y, rad, rad );
	// return BBox( x, y, rad * 2.05f, rad * 2.05f );
	return BBox( x - rad, y - rad, rad * 2.05f, rad * 2.05f );	
	// return BBox( 0, 0, 200, 200 );
}

///////////////////////////////////
// SolidCircle
SolidCircle::SolidCircle( const int l_x, const int l_y, const Sint16 l_rad, const Uint32 l_color )
	: FrameCircle( l_x, l_y, l_rad, l_color )
{
}

void SolidCircle::render( const float offsetX, const float offsetY )
{
	filledCircleColor( kernel.getRenderer(), offsetX + x + rad, offsetY + y + rad, rad, color );
}
