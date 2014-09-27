#include "GradientRect.h"
#include "Helper.h"

GradientRect::GradientRect( const int l_x, const int l_y, const int l_width, const int l_height, const Uint32 l_color1, const Uint32 l_color2 )
	: SolidRect( l_x, l_y, l_width, l_height, l_color1 )
	, color2( l_color2 )
{
	Uint8 r1, r2, r3, g1, g2, g3, b1, b2, b3, a1, a2, a3;
	int2RGBA( l_color1, r1, g1, b1, a1 );
	int2RGBA( l_color2, r2, g2, b2, a2 );
	r3 = r2 - r1;
	g3 = g2 - g1;
	b3 = b2 - b1;
	a3 = a2 - a1;
	Uint8 tmp_r, tmp_g, tmp_b, tmp_a;

	float factor = 0.0f;
	for ( int i = 0; i < height; ++i ) {
		factor = ( (float)i / (float)height );
		tmp_r = r1 + (Uint8)((float)r3 * factor);
		tmp_g = g1 + (Uint8)((float)g3 * factor);
		tmp_b = b1 + (Uint8)((float)b3 * factor);
		tmp_a = a1 + (Uint8)((float)a3 * factor);		
		lines_.push_back( Line( x, i + y, x + width, i + y, RGBA2Int( tmp_r, tmp_g, tmp_b, tmp_a ) ) );
	}
}
	
void GradientRect::render( const float offsetX, const float offsetY )
{
	std::vector<Line>::iterator iter = lines_.begin();
	std::vector<Line>::iterator endIter = lines_.end();
	while ( iter != endIter ) {
		(*iter).render( offsetX, offsetY );
		++iter;
	}
	// boxColor(kernel.getRenderer(), offsetX + x, offsetY + y, offsetX + x + width, offsetY + y + height, color);		
}
