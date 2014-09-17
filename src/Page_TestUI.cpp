#include "Page_TestUI.h"

#include "GUI_Window.h"
#include "GUI_Button.h"
#include "Kernel.h"

Page_TestUI::Page_TestUI()
{
}

Page_TestUI::~Page_TestUI()
{
}

void Page_TestUI::update(const double dt)
{
	Page::update(dt);
}

void Page_TestUI::render()
{
	Page::render();
}

bool Page_TestUI::resolved()
{
	Page::resolved();

	{
//		GUI_Window* window = new GUI_Window( 0.0f, 0.0f, 300.0f, 300.0f );
//		this->addChild( window );

		// GUI_Button* button1 = GUI_Button::createSimpleButton("click me", 0, 0, 64, 48 );
		// window->addChild( button1 );
	}
	
	{
		GUI_Button* button = GUI_Button::createSimpleButton( "click me", 100, 100, 64, 32, 255, 255, 255, 100 );
		this->addChild( button );
	}
	
	return true;
}










