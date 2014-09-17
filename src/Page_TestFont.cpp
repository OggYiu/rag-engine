#include "Page_TestFont.h"

#include "GUI_Label.h"
#include "GUI_Window.h"
#include "GUI_Button.h"
#include "Kernel.h"

Page_TestFont::Page_TestFont()
{
}

Page_TestFont::~Page_TestFont()
{
}

void Page_TestFont::update(const double dt)
{
	Parent::update(dt);
}

void Page_TestFont::render()
{
	Parent::render();
}

bool Page_TestFont::resolved()
{
	Parent::resolved();

	{
		GUI_Label* label = new GUI_Label(kernel.getScreenWidth() / 2.0f, kernel.getScreenHeight() / 2.0f, "hello world");
		this->addChild(label);
	}

	{
		GUI_Label* label = new GUI_Label(kernel.getScreenWidth() / 2.0f, kernel.getScreenHeight() / 2.0f, "do you love me?");
		this->addChild(label);
	}

	{
		GUI_Label* label = new GUI_Label(100.0f, 100.0f / 2.0f, "pf_seven text", "pf_ronda_seven", 16, 255, 255, 0 );
		this->addChild(label);
	}
	
	return true;
}










