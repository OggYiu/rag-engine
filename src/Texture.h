#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>
#include "SDL.h"

class TextureRef;

class Texture
{
public:
	Texture( SDL_Texture* texture );
	Texture( SDL_Texture* texture, const int width, const int height );	
	~Texture();
	
public:
	static Texture* createImageTexture( const std::string& path );
	static Texture* createEmptyTexture( const int width, const int height, const Uint8 red = 255, const Uint8 green = 255, const Uint8 blue = 255, const Uint8 alpha = 255 );
	
public:
	void setColor( const Uint8 red, const Uint8 green, const Uint8 blue );
	void setBlendMode( const SDL_BlendMode blending );
	void setAlpha( const Uint8 alpha );
	int getWidth() { return width_; }
	int getHeight() { return height_; }
	void render( SDL_Rect* clipRect = nullptr, SDL_Rect* renderRect = nullptr, const double angle = 0, SDL_Point* center = nullptr, const SDL_RendererFlip flip = SDL_FLIP_NONE );

private:
	SDL_Texture* sdlTexture_;
	int width_;
	int height_;
};

#endif
