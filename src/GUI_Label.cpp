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

GUI_Label::GUI_Label( const float x, const float y, const std::string& text, const int fontSize, const std::string& fontName, const Uint32 color )
	: text_( text )
	, fontName_( fontName )
	, fontSize_( fontSize )
	, color_( color )
//	, isDirty_(true)
{
	// std::cout << "gui_label: " << x << ", " << y << ", text: " << text.c_str() << ", font name: " << fontName << ",font size; " << fontSize << std::endl;
	if ( text_.length() > 0 ) {
		recreateTexture();
	}
	
	transform().setPos( x, y );
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

	// std::cout << "1" << std::endl;
	Texture* texture = textureMgr.createTTFTexture( text_, fontName_, fontSize_, color_ );
	setTexture( texture );
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

void GUI_Label::resolved()
{
	GUI_Base::resolved();
}
