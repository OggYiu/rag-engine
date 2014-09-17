#ifndef __TYPES_H__
#define __TYPES_H__

struct BBox
{
	BBox()
		: x( 0 )
		, y( 0 )
		, w( 0 )
		, h( 0 )
		{
		}

	BBox( const int p_x, const int p_y, const int p_width, const int p_height )
		: x( p_x )
		, y( p_y )
		, w( p_width )
		, h( p_height )
		{
		}
	
	inline int x1() { return x; }
	inline int y1() { return y; }
	inline int x2() { return x + w; }
	inline int y2() { return y + h; }
	inline int width() { return w; }
	inline int height() { return h; }
		
	int x;
	int y;
	int w;
	int h;
};

#endif
