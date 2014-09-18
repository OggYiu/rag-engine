#include "GUI_Window.h"

#include <iostream>
#include <functional>
#include "Graphics.h"
#include "MouseEvent.h"
#include "Kernel.h"
#include "Helper.h"
#include "GUI_Button.h"

GUI_Window::GUI_Window()
	: bgContainer_( nullptr )
	, itemsContainer_( nullptr )
	, overlayContainer_( nullptr )
	, isDragging_( false )
{
	lastMouseX_ = 0;
	lastMouseY_ = 0;
}

GUI_Window::GUI_Window( const float x, const float y, const float width, const float height )
	: bgContainer_( nullptr )
	, itemsContainer_( nullptr )
	, overlayContainer_( nullptr )
	, isDragging_( false )	  
{
	lastMouseX_ = 0;
	lastMouseY_ = 0;
	
	setPosition( x, y );
	setSize( width, height );
}

GUI_Window::~GUI_Window()
{
}

void GUI_Window::update(const double dt)
{
	GUI_BaseContainer::update( dt );
}

void GUI_Window::render()
{
	GUI_BaseContainer::render();
}

bool GUI_Window::resolved()
{
	GUI_BaseContainer::resolved();

	kernel.getStage().addEventListener(MouseEvent::MOUSE_MOVE, bindEventHandler(&GUI_Window::eventHandler, this), this);
	kernel.getStage().addEventListener(MouseEvent::MOUSE_DOWN, bindEventHandler(&GUI_Window::eventHandler, this), this);
	kernel.getStage().addEventListener(MouseEvent::MOUSE_UP, bindEventHandler(&GUI_Window::eventHandler, this), this);

	// bgContainer_ = new DisplayObjectContainer();
	// this->addChild( bgContainer_ );
	
	// itemsContainer_ = new DisplayObjectContainer();
	// this->addChild( itemsContainer_ );
	
	// overlayContainer_ = new DisplayObjectContainer();
	// this->addChild( overlayContainer_ );
	
	// frame_ = new Graphics();
	// frame_->clear();
	// frame_->drawSolidRect(0, 0, getWidth(), getHeight());
	// bgContainer_->addChild( frame_ );

	Graphics* graphics = new Graphics();

	// draw border
	graphics->setColor( 0, 0, 0, 255 );
	graphics->drawFrameRect( 0, 0, getWidth(), getHeight() );
	graphics->setColor( 255, 255, 255, 50 );
	graphics->drawSolidRect( 0, 0, getWidth(), getHeight() );

	// draw title bar
	{
		const int uiHeight = 30;
		const int marginX = 6;
		const int marginY = 6;
		graphics->setColor( 255, 255, 255, 50 );
		graphics->drawSolidRect( marginX, marginY, getWidth() - marginX * 2, uiHeight );
		this->addChild( graphics );
	}

	{
		const int uiWidth = 26;
		const int uiHeight = 26;
		const int marginX = 8;
		const int marginY = 8;
		GUI_Button* button = GUI_Button::createSimpleButton( "", getWidth() - marginX - uiWidth / 2, marginY + uiHeight / 2, uiWidth, uiHeight, 100, 100, 255, 100 );
		this->addChild( button );
	}
	
	return true;
}

bool GUI_Window::eventHandler(const Event& event)
{
	MouseEvent* mouseEvent = (MouseEvent*)(&event);
	int mouseX = mouseEvent->getMouseX();
	int mouseY = mouseEvent->getMouseY();
	if ( lastMouseX_ < 0 ) {
		lastMouseX_ = mouseX;
	}
	if ( lastMouseY_ < 0 ) {
		lastMouseY_ = mouseY;
	}
	int diffMouseX = mouseX - lastMouseX_;
	int diffMouseY = mouseY - lastMouseY_;
	
	if ( event.getType().compare( MouseEvent::MOUSE_DOWN ) == 0 ) {
		isDragging_ = true;
	} else if ( event.getType().compare( MouseEvent::MOUSE_UP ) == 0 ) {
		isDragging_ = false;
	} else if ( event.getType().compare( MouseEvent::MOUSE_MOVE ) == 0 ) {
		if ( isDragging_ ) {
			// static int x = 0;
			// static int y = 0;
			this->setX( this->getX() + diffMouseX );
			this->setY( this->getY() + diffMouseY );
			// this->setX( x++ );
			// this->setY( y++ );

//			std::cout << "pos: " << this->getX() << ", " << this->getY() << std::endl;
		}
	}
	lastMouseX_ = mouseX;
	lastMouseY_ = mouseY;

	return true;
}
