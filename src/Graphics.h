#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "Eigen/Dense"
#include <vector>
#include "Object.h"
#include "DisplayObjectBase.h"
#include "Primitive.h"

class Graphics : public DisplayObjectBase
{
private:
	typedef std::vector<Primitive*> PrimitiveVec;
	typedef PrimitiveVec::iterator PrimitiveIter;
	
public:
	Graphics();
	~Graphics();	
	
public:
	void setColor(const Uint32 color);
	void setColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);
	void setAlpha(const Uint8 a);
	void setLineThickness(const int thickness);
	SDL_Texture* createTexture();
	void clear();
	void lineTo( const int x, const int y );
	void aalineTo( const int x, const int y );	
	void moveTo( const int x, const int y);
	void drawPixel(const int x, const int y);
	void drawSolidRect(const int x, const int y, const int width, const int height);
	void drawFrameRect(const int x, const int y, const int width, const int height);
	void drawRoundSolidRect( const int x, const int y, const int width, const int height, const float radius );
	void drawRoundFrameRect( const int x, const int y, const int width, const int height, const float radius );
	void render();

protected:
	float lineThickness_;
	Uint32 color_;
	Eigen::Vector2i cursor_;
	PrimitiveVec primitives_;
};

#endif






