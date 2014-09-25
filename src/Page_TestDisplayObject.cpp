#include "Page_TestDisplayObject.h"

#include <functional>
#include "GUI_Label.h"
#include "GUI_Image.h"
#include "GUI_Window.h"
#include "GUI_Button.h"
#include "Kernel.h"
#include "Graphics.h"
#include "Primitive.h"
#include "Helper.h"
#include "Texture.h"
#include "KeyboardEvent.h"
#include "Logger.h"


Page_TestDisplayObject::Page_TestDisplayObject()
{
}

Page_TestDisplayObject::~Page_TestDisplayObject()
{
}

void Page_TestDisplayObject::update(const double dt)
{
	Page::update( dt );
}
	
void Page_TestDisplayObject::render()
{
	Page::render();
}

bool Page_TestDisplayObject::resolved()
{
	Page::resolved();

	kernel.getStage().addEventListener( KeyboardEvent::KEY_DOWN, bindEventHandler( &Page_TestDisplayObject::eventHandler, this ), this );
	// {
	// 	DisplayObjectContainer* container = new DisplayObjectContainer();
	// 	container->transform().setPos( kernel.getScreenWidth() / 2, kernel.getScreenHeight() / 2 );
	// 	this->addChild( container );

	// 	{
	// 		GUI_Image* image = new GUI_Image( 0, 0, "assets/alex.png" );
	// 		container->addChild( image );
	// 		image->transform().setPos( -image->getWidth() / 2.0f, -image->getHeight() / 2.0f );
	// 	}

	// 	{
	// 		GUI_Image* image = new GUI_Image( 0, 0, "assets/girl.png" );
	// 		container->addChild( image );
	// 		image->transform().setPos( 0.0f, 0.0f );
	// 	}
	// }
	
	{
		DisplayObjectContainer* container = this;
		// DisplayObjectContainer* container = new DisplayObjectContainer();		
		// container->transform().setPos( kernel.getScreenWidth() / 2, kernel.getScreenHeight() / 2 );
		// this->addChild( container );

		{
			GUI_Image* image = new GUI_Image( 0, 0, "assets/alex.png" );
			container->addChild( image );
			image->transform().setPos( -image->getWidth() / 2.0f, -image->getHeight() / 2.0f );
			image->transform().print();
		}

		// {
		// 	GUI_Image* image = new GUI_Image( 0, 0, "assets/girl.png" );
		// 	container->addChild( image );
		// 	image->transform().setPos( 0.0f, 0.0f );
		// }
	}

	return true;
}

void Page_TestDisplayObject::startDemo( const int num )
{
	std::cout << "num: " << num << std::endl;
}

bool Page_TestDisplayObject::eventHandler( const Event& event )
{
	// if ( event->isEqual( KeyboardEvent::KEY_DOWN ) ) {
	// }

	KeyboardEvent* e = (KeyboardEvent*)&event;
	std::cout << *e << std::endl;
	std::cout << "type: " << event.getType() << std::endl;

	if ( e->isEqual( KeyboardEvent::KEY_DOWN ) ) {
		if ( e->getKeycode() == SDLK_RIGHT ) {
			logger.d( "xxxx", "sdk right" );
		} else if ( e->getKeycode() == SDLK_LEFT ) {
			logger.d( "xxxx", "sdk left" );
		}
	}
	return true;
}
