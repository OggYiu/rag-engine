#include "GUI_Image.h"
#include "TextureMgr.h"

GUI_Image::GUI_Image( const int x, const int y, const std::string& imagePath )
{
	transform().setPos( x, y );
	setTexture( textureMgr.getInstance().createImageTexture( imagePath ) );
}

GUI_Image::GUI_Image( const int x, const int y, Texture* const texture )
{
	transform().setPos( x, y );
	setTexture( texture );
}

GUI_Image::GUI_Image( const int x, const int y, std::vector<Primitive*>& primitives )
{
	transform().setPos( x, y );
	setTexture( textureMgr.createPrimitivesTexture( primitives ) );
}

GUI_Image::~GUI_Image()
{
}



