#include "Page_TestBtn.h"

#include "GUI_Button.h"
#include "GUI_Label.h"

Page_TestBtn::Page_TestBtn()
{
}

Page_TestBtn::~Page_TestBtn()
{
}

void Page_TestBtn::update(const double dt)
{
	Page::update( dt );
}

void Page_TestBtn::render()
{
	Page::render();
}

bool Page_TestBtn::resolved()
{
	Page::resolved();

	{
		// GUI_Button* btn = new GUI_Button( 50, 50, 64, 24, "test" );
		GUI_Button* btn = new GUI_Button( 50, 50, 128, 48, "test" );		
		this->addChild( btn );
	}
	
	// {
	// 	GUI_Label* label = new GUI_Label( 0, 0, "test2" );
	// 	this->addChild( label );
	// }

	return true;
}

