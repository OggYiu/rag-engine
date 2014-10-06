#include "Texture.h"

#include <assert.h>
#include "TextureMgr.h"
#include "Kernel.h"

Texture::Texture( SDL_Texture* sdlTexture )
	: sdlTexture_( sdlTexture )
{
	SDL_QueryTexture( sdlTexture, nullptr, nullptr, &width_, &height_ );
}

Texture::Texture( SDL_Texture* texture, const int width, const int height )
	: sdlTexture_( texture )
	, width_( width )
	, height_( height )
{
}

Texture::~Texture()
{
	if ( sdlTexture_ != nullptr ) {
		textureMgr.releaseSDLTexture( sdlTexture_ );
		sdlTexture_ = nullptr;
	}
}

void Texture::setColor( const Uint8 red, const Uint8 green, const Uint8 blue )
{
	if ( sdlTexture_ == nullptr ) {
		assert( false && "invalid texture" );
		return;
	}

	SDL_SetTextureColorMod( sdlTexture_, red, green, blue );
}

void Texture::setBlendMode( const SDL_BlendMode blending )
{
	if ( sdlTexture_ == nullptr ) {
		assert( false && "invalid texture" );
		return;
	}

	SDL_SetTextureBlendMode( sdlTexture_, blending );
}

void Texture::setAlpha( const Uint8 alpha )
{
	if ( sdlTexture_ == nullptr ) {
		assert( false && "invalid texture" );
		return;
	}

	SDL_SetTextureAlphaMod( sdlTexture_, alpha );
}

void Texture::render( SDL_Rect* clipRect, SDL_Rect* renderRect, const double angle, SDL_Point* center, const SDL_RendererFlip flip )
{
	if ( sdlTexture_ == nullptr ) {
		assert( false && "invalid texture" );
		return;
	}

	SDL_RenderCopyEx( kernel.getRenderer(), sdlTexture_, clipRect, renderRect, angle, center, flip );
}
