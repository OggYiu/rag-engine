#include "DebugConsole.h"

#include <sstream>
#include "GUI_Label.h"
#include "MouseEvent.h"
#include "Kernel.h"
#include "Helper.h"

static int countedFrames = 0;

DebugConsole::DebugConsole()
{
}

DebugConsole::~DebugConsole()
{
}

void DebugConsole::update(const double dt)
{
	Parent::update(dt);

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

bool DebugConsole::resolved()
{
	Parent::resolved();

	fpsLabel_ = new GUI_Label( 4, 0, "AVG FPS: 9999", "pf_ronda_seven", 12, 0, 0, 0 );

//	std::cout << "fps: " << fpsLabel_->getWidth() << ", " << fpsLabel_->getHeight() << std::endl;
//	fpsLabel_->setPos( fpsLabel_->getWidth() / 2.0f, fpsLabel_->getHeight() / 2.0f );
	fpsLabel_->setAnchor( 0.0f, 0.0f );
	this->addChild( fpsLabel_ );
	
	mousePosLabel_ = new GUI_Label( 4, fpsLabel_->getHeight(), "hello", "pf_ronda_seven", 12, 0, 0, 255, 200 );
	this->addChild( mousePosLabel_ );
	
	timer_.start();

	kernel.getStage().addEventListener( MouseEvent::MOUSE_MOVE, bindEventHandler( &DebugConsole::eventHandler, this ), this );
	
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
