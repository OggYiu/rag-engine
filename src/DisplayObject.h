#ifndef __DISPLAYOBJECT_H__
#define __DISPLAYOBJECT_H__

#include <memory>
#include "SDL.h"
#include "SDL_image.h"

#include "Tweener.h"

#include "DisplayObjectBase.h"

class DisplayObjectContainer;
class Texture;

class DisplayObject : public DisplayObjectBase
{
public:
	DisplayObject();
	virtual ~DisplayObject();

public:
	virtual void update(const double dt);
	virtual void render();
	void setTexture( Texture* texture ) { texture_ = texture; }
	void setColor( const Uint8 red, const Uint8 green, const Uint8 blue );
	void setBlendMode( const SDL_BlendMode blending );
	SDL_BlendMode getBlendMode() const { return blending_; }
	
	void setAlpha( const Uint8 alpha );
	Uint8 getAlpha() const { return alpha_; }

	void setRenderRect( const int x, const int y, const int w, const int h );
	
	bool hitTest( const int x, const int y ) const;

public:
	Tweener& tweener() { return tweener_; }

protected:
	void releaseTexture();
	virtual void updateRenderPos_();

protected:
	Texture* texture_;
	SDL_Point* center_;
	SDL_Rect* clipRect_;
	SDL_Rect* renderRect_;
	SDL_RendererFlip flip_;
	SDL_BlendMode blending_;
	Uint8 alpha_;
	Uint8 red_;
	Uint8 green_;
	Uint8 blue_;
	Tweener tweener_;
};

#endif
