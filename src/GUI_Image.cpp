#include "GUI_Image.h"

#include "SDL.h"
#include "SDL_image.h"
#include "Kernel.h"
#include "Helper.h"
#include "Texture.h"
#include "TextureMgr.h"

GUI_Image::GUI_Image( const float x, const float y, const std::string& path )
{
//	int width = 0;
//	int height = 0;
	Texture* texture = Texture::createImageTexture( path );
	setTexture( texture );
	setPosition( x, y );
	// setSize( texture->getWidth(), texture->getHeight() );
	// setTexture( texture );
}

GUI_Image::GUI_Image( const float x, const float y, Texture* const texture )
{
	setTexture( texture );
	setPosition( x, y );
}

GUI_Image::~GUI_Image()
{
}



