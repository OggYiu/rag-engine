#include "Page_TestUI.h"

#include "GUI_Label.h"
#include "GUI_Image.h"
#include "GUI_Window.h"
#include "GUI_Button.h"
#include "Kernel.h"
#include "Graphics.h"
#include "Primitive.h"
#include "Helper.h"
#include "Texture.h"

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
		DisplayObjectContainer* container = new DisplayObjectContainer();
		container->transform().setPos( kernel.getScreenWidth() / 2, kernel.getScreenHeight() / 2 );
		this->addChild( container );

		{
			GUI_Image* image = new GUI_Image( 0, 0, "assets/alex.png" );
			container->addChild( image );
			image->transform().setPos( -image->getWidth() / 2.0f, -image->getHeight() / 2.0f );
		}

		{
			GUI_Image* image = new GUI_Image( 0, 0, "assets/girl.png" );
			container->addChild( image );
			image->transform().setPos( 0.0f, 0.0f );
		}

		Graphics* graphics = new Graphics();
		graphics->setDrawColor( 255, 0, 0, 255 );
		container->updateBoundingBox();
		SDL_Rect* bbox = &container->getBBox();		
		std::cout << "container bounding: " << bbox->x << ", " << bbox->y << ", " << bbox->w << ", " << bbox->h << std::endl;
		graphics->drawFrameRect( 0, 0, bbox->w, bbox->h );
		this->addChild( graphics );
		graphics->transform().setPos( bbox->x, bbox->y );
	}
	
	return true;
}










