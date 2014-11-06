#ifndef __DEBUGCONSOLE_H__
#define __DEBUGCONSOLE_H__

#include "Event.h"
#include "DisplayObjectContainer.h"
#include "Timer.h"

class GUI_Label;
class GUI_VBox;

class DebugConsole : public DisplayObjectContainer
{
public:
	DebugConsole();
	virtual ~DebugConsole();
	static DebugConsole& getInstance();
	
public:
	virtual void update(const double dt);
	void addDebugMsg( const std::string& msg, const Uint32 color = 0xFF000000 );
	
protected:
	virtual void resolved();
	bool eventHandler( const Event& event );
		
private:
	Timer timer_;
	GUI_Label* fpsLabel_;
	GUI_Label* mousePosLabel_;
	GUI_VBox* vbox_;
};

#define debugConsole DebugConsole::getInstance();

#endif
