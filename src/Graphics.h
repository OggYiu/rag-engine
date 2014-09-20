#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "Eigen/Dense"
#include <vector>
#include "Object.h"
#include "DisplayObject.h"
#include "Primitive.h"

class Texture;

class Graphics : public DisplayObject
{
private:
	typedef std::vector<Primitive*> PrimitiveVec;
	typedef PrimitiveVec::iterator PrimitiveIter;
	
public:
	Graphics();
	~Graphics();	
	
public:
	void setDrawColor( const Uint32 color );
	void setDrawColor( const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a );
	void setDrawAlpha( const Uint8 a );
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
	virtual void render();

protected:
	float lineThickness_;
	Uint32 drawColor_;
	Eigen::Vector2i cursor_;
	PrimitiveVec primitives_;
	bool textureDirty_;
};

#endif






