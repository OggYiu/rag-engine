#include "GUI_Label.h"

#include "Kernel.h"
#include "Helper.h"
//#include "FontMgr.h"
#include "TextureMgr.h"
#include "Texture.h"

GUI_Label::GUI_Label()
	: text_("")
	, fontName_("")
	, fontSize_(0)
	, isDirty_(false)
{
}

GUI_Label::GUI_Label( const float x, const float y, const std::string& text, const std::string& fontName, const int fontSize, const Uint8 red, const Uint8 green, const Uint8 blue )
	: text_( text )
	, fontName_( fontName )
	, fontSize_( fontSize )
//	, isDirty_(true)
{
	red_ = red;
	green_ = green;
	blue_ = blue;

	recreateTexture();
	setPosition(x, y);
}

GUI_Label::~GUI_Label()
{
}

void GUI_Label::setText(const std::string& text)
{
	// text_ = text;
	// recreateTexture(text_, fontName_, fontSize_);

	text_ = text;
	isDirty_ = true;
}

void GUI_Label::recreateTexture()
{
	releaseTexture();

	SDL_Texture* sdlTexture = textureMgr.createTTFTexture( text_, fontName_, fontSize_, red_, green_, blue_ );
	texture_ = new Texture( sdlTexture );
	setSize( texture_->getWidth(), texture_->getHeight() );
}

void GUI_Label::update(const double dt)
{
	// should call this before parent's update
	if ( isDirty_ )
	{
		isDirty_ = false;
		recreateTexture();
	}
	
    GUI_Base::update(dt);
}

void GUI_Label::render()
{
	GUI_Base::render();
}

bool GUI_Label::resolved()
{
	GUI_Base::resolved();

	return true;
}