#ifndef __GRADIENT_RECT_H__
#define __GRADIENT_RECT_H__

#include "Primitive.h"

struct GradientRect : public SolidRect
{
	GradientRect( const int l_x, const int l_y, const int l_width, const int l_height, const Uint32 l_color1, const Uint32 l_color2 );
	virtual void render( const float offsetX = 0, const float offsetY = 0 );
	
	Uint32 color2;
	std::vector<Line> lines_;
};

#endif
