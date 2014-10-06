#include "DebugConsole.h"

#include <sstream>
#include "GUI_Label.h"
#include "GUI_VBox.h"
#include "MouseEvent.h"
#include "Kernel.h"
#include "Helper.h"
#include "Logger.h"

static int countedFrames = 0;

DebugConsole::DebugConsole()
{
}

DebugConsole::~DebugConsole()
{
}

void DebugConsole::update(const double dt)
{
	DisplayObjectContainer::update(dt);

	//Calculate and correct fps
	float avgFPS = countedFrames / ( timer_.getTicks() / 1000.f );
	if ( avgFPS > 2000000 )	{
		avgFPS = 0;
	}

	std::stringstream ss;
	ss << "AVG FPS: " << avgFPS;
	std::string tickStr = ss.str();
	
	fpsLabel_->setText( tickStr );

	++countedFrames;
}

void DebugConsole::addDebugMsg( const std::string& msg, const Uint32 color )
{
	GUI_Label* label = new GUI_Label( 4, 0, msg.c_str(), "pf_ronda_seven", 12, color );
	vbox_->addItem( label );

	// if ( vbox_->getHeight() > kernel.getScreenHeight() ) {
	// 	std::cout << vbox_->getHeight() << ", " << kernel.getScreenHeight() << ", result: " << ( vbox_->getHeight() > kernel.getScreenHeight() ) << std::endl;
	// 	vbox_->releaseChildAt( 0 );
	// 	vbox_->rearrangeChildren();
	// }

	// std::stringstream ss;
	// ss << vbox_->getHeight();
	// std::string str = ss.str();
	// logger.d( "debug console", str );
}

bool DebugConsole::resolved()
{
	DisplayObjectContainer::resolved();

	fpsLabel_ = new GUI_Label( 0, 0, "AVG FPS: 9999", "pf_ronda_seven", 12, 0xFF000000 );
	fpsLabel_->transform().setX( kernel.getScreenWidth() - fpsLabel_->getWidth() - 32 );
	this->addChild( fpsLabel_ );
	
	mousePosLabel_ = new GUI_Label( 0, fpsLabel_->getHeight(), "mouse, x: 000, y: 000", "pf_ronda_seven", 12, 0xAA0000FF );
	mousePosLabel_->transform().setX( kernel.getScreenWidth() - 160 );
	this->addChild( mousePosLabel_ );
	
	timer_.start();

	kernel.getStage().addEventListener( MouseEvent::MOUSE_MOVE, bindEventHandler( &DebugConsole::eventHandler, this ), this );

	vbox_ = new GUI_VBox( 0.0f, 0.0f, kernel.getScreenWidth(), kernel.getScreenHeight() );
	this->addChild( vbox_ );
	
	return true;
}

DebugConsole& DebugConsole::getInstance()
{
	static DebugConsole s_instance;
	return s_instance;
}

bool DebugConsole::eventHandler( const Event& event )
{
	MouseEvent* mouseEvent = (MouseEvent*)(&event);
	int mouseX = mouseEvent->getMouseX();
	int mouseY = mouseEvent->getMouseY();

	std::stringstream ss;
	ss << "mouse, x: " << mouseX << ", y: " << mouseY;
	std::string str = ss.str();
	mousePosLabel_->setText( str );
	
	return true;
}
