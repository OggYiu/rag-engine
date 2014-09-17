#include "DebugConsole.h"

#include <sstream>
#include "GUI_Label.h"

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

	fpsLabel_ = new GUI_Label(0, 0, "AVG FPS: 9999", "pf_ronda_seven", 12, 0, 0, 0 );
//	std::cout << "fps: " << fpsLabel_->getWidth() << ", " << fpsLabel_->getHeight() << std::endl;
//	fpsLabel_->setPosition( fpsLabel_->getWidth() / 2.0f, fpsLabel_->getHeight() / 2.0f );
	fpsLabel_->setAnchor( 0.0f, 0.0f );
	this->addChild( fpsLabel_ );

	timer_.start();
	
	return true;
}

DebugConsole& DebugConsole::getInstance()
{
	static DebugConsole s_instance;
	return s_instance;
}
