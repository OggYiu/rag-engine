#ifndef __DEBUGCONSOLE_H__
#define __DEBUGCONSOLE_H__

#include <unistd.h>
#include "DisplayObjectContainer.h"
#include "Timer.h"

class GUI_Label;

class DebugConsole : public DisplayObjectContainer
{
private:
	typedef DisplayObjectContainer Parent;
	
public:
	DebugConsole();
	virtual ~DebugConsole();
	static DebugConsole& getInstance();
	
public:
	virtual void update(const double dt);
	int getId() const;
	bool isReleased() const { return released_; }
	
protected:
	virtual bool resolved();

private:
	Timer timer_;
	GUI_Label* fpsLabel_;
};

#define debugConsole DebugConsole::getInstance();

#endif